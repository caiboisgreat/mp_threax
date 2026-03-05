/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020-2021 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "py/nlr.h"
#include "py/objlist.h"
#include "py/objstr.h"
#include "py/runtime.h"
#include "py/mperrno.h"
#include "py/mphal.h"
#include "py/stream.h"
#include "py/obj.h"

#ifndef STATIC
#define STATIC static
#endif

#if MICROPY_QPY_MODULE_OSTIMER

#include "tx_api.h"

/* ThreadX timer tick configuration */
#ifndef TX_TIMER_TICKS_PER_SECOND
#define TX_TIMER_TICKS_PER_SECOND 100  /* Default 100 ticks/sec = 10ms per tick */
#endif

/* Convert milliseconds to ThreadX timer ticks */
#define MS_TO_TICKS(ms)     (((ms) * TX_TIMER_TICKS_PER_SECOND + 999) / 1000)
#define TICKS_TO_MS(ticks)  (((ticks) * 1000) / TX_TIMER_TICKS_PER_SECOND)

#define OSTIMER_LOG(msg, ...)      mp_printf(&mp_plat_print, "osTimer: " msg "\n", ##__VA_ARGS__)


typedef struct _mod_ostimer_obj_t 
{
	mp_obj_base_t base;
	TX_TIMER timer;                  /* ThreadX timer control block */
	unsigned int initialTime;        /* initial expiration time in ms (for reference) */
	bool cyclicalEn;                 /* whether to enable the cyclical mode or not */
	mp_obj_t callback;               /* timer call-back routine (MicroPython function) */
	bool deleteFlagh;                /* delete flag */
	bool is_created;                 /* track if timer is created */
	char name[16];                   /* timer name for debugging */
} mod_ostimer_obj_t;

const mp_obj_type_t mp_ostimer_type;

/* ThreadX timer expiration function - called from timer context */
STATIC void mod_ostimer_expiration_func(ULONG param) {
    mod_ostimer_obj_t *self = (mod_ostimer_obj_t *)param;
	if (self != NULL && self->callback != mp_const_none) {
		#if MICROPY_ENABLE_SCHEDULER
    	mp_sched_schedule(self->callback, MP_OBJ_FROM_PTR(self));
		#endif
	}
}


STATIC mp_obj_t mod_ostimer_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args)
{
	mod_ostimer_obj_t *self = mp_obj_malloc_with_finaliser(mod_ostimer_obj_t, type);

	self->base.type = &mp_ostimer_type;
	self->deleteFlagh = 0;
	self->is_created = false;
	self->initialTime = 0;
	self->cyclicalEn = false;
	self->callback = mp_const_none;
	
	/* Generate unique timer name */
	snprintf(self->name, sizeof(self->name), "MPTimer%p", self);

	return MP_OBJ_FROM_PTR(self);
}


STATIC mp_obj_t mod_ostimer_start(uint n_args, const mp_obj_t *args)
{
	UINT ret = TX_SUCCESS;
	
	mod_ostimer_obj_t *self = MP_OBJ_TO_PTR(args[0]);

    if (!(self->deleteFlagh))
    {
    	self->initialTime = mp_obj_get_int(args[1]);
    	self->cyclicalEn = !!mp_obj_get_int(args[2]);
    	
    	/* Store callback */
    	self->callback = args[3];

		/* Convert milliseconds to ThreadX ticks */
		ULONG initial_ticks = MS_TO_TICKS(self->initialTime);
		ULONG reschedule_ticks = self->cyclicalEn ? initial_ticks : 0;

		/* If timer was already created, delete it first */
		if (self->is_created) {
			tx_timer_deactivate(&self->timer);
			tx_timer_delete(&self->timer);
			self->is_created = false;
		}

		/* Create new timer with ThreadX */
		ret = tx_timer_create(
			&self->timer,                      /* Timer control block */
			self->name,                        /* Timer name */
			mod_ostimer_expiration_func,       /* Expiration function */
			(ULONG)self,                       /* Parameter: pointer to self */
			initial_ticks,                     /* Initial ticks */
			reschedule_ticks,                  /* Reschedule ticks (0=one-shot, >0=periodic) */
			TX_NO_ACTIVATE                     /* Don't activate automatically */
		);

		if (ret == TX_SUCCESS) {
			self->is_created = true;
			/* Activate the timer */
			ret = tx_timer_activate(&self->timer);
		}
    }
    else
    {
        ret = -1;
    }
	return mp_obj_new_int(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(mod_ostimer_start_obj, 3, 5, mod_ostimer_start);

STATIC mp_obj_t mod_ostimer_stop(mp_obj_t arg0)
{
	UINT ret = TX_SUCCESS;
	
	mod_ostimer_obj_t *self = MP_OBJ_TO_PTR(arg0);
    if (!(self->deleteFlagh) && self->is_created)
    {
	    ret = tx_timer_deactivate(&self->timer);
	}
	else
	{
        ret = -1;
	}
	return mp_obj_new_int(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_ostimer_stop_obj, mod_ostimer_stop);



STATIC mp_obj_t mod_ostimer_delete(mp_obj_t arg0)
{
	UINT ret = TX_SUCCESS;
	
	mod_ostimer_obj_t *self = MP_OBJ_TO_PTR(arg0);

	if (!(self->deleteFlagh))
	{
		self->deleteFlagh = 1;
		if (self->is_created) {
			/* Stop and delete the ThreadX timer */
			tx_timer_deactivate(&self->timer);
			ret = tx_timer_delete(&self->timer);
			self->is_created = false;
		}
        OSTIMER_LOG("[osTimer] ostimer delete");
	}

	return mp_obj_new_int(ret);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_ostimer_delete_obj, mod_ostimer_delete);


STATIC const mp_rom_map_elem_t mod_ostimer_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_osTimer) },
	{ MP_ROM_QSTR(MP_QSTR___class__), MP_ROM_PTR(&mp_type_type) },
	{ MP_ROM_QSTR(MP_QSTR___del__), MP_ROM_PTR(&mod_ostimer_delete_obj) },
	{ MP_ROM_QSTR(MP_QSTR_start), MP_ROM_PTR(&mod_ostimer_start_obj) },
	{ MP_ROM_QSTR(MP_QSTR_stop), MP_ROM_PTR(&mod_ostimer_stop_obj) },
	{ MP_ROM_QSTR(MP_QSTR_delete_timer), MP_ROM_PTR(&mod_ostimer_delete_obj) },
};
// Avoid sizeof on possibly incomplete array types in some toolchains.
STATIC MP_DEFINE_CONST_DICT_WITH_SIZE(mod_ostimer_locals_dict, mod_ostimer_locals_dict_table, 6);

MP_DEFINE_CONST_OBJ_TYPE(
    mp_ostimer_type,
    MP_QSTR_osTimer,
    MP_TYPE_FLAG_NONE,
    make_new, mod_ostimer_make_new,
    locals_dict, &mod_ostimer_locals_dict,
    parent, &mp_type_object
);

// Make the module an exact alias of the type so "import osTimer" returns the class itself
// This uses memory layout compatibility between module and type structures
#if defined(__GNUC__) || defined(__clang__)
// Use weak alias for GCC/Clang - makes mp_module_osTimer an alias of mp_ostimer_type
extern const mp_obj_module_t mp_module_osTimer __attribute__((alias("mp_ostimer_type")));
#else
// Fallback: create a module structure that references the type
const mp_obj_module_t mp_module_osTimer = {
    .base = { &mp_type_type },
    .globals = (mp_obj_dict_t *)&mod_ostimer_locals_dict,
};
#endif

// Register for import
MP_REGISTER_MODULE(MP_QSTR_osTimer, mp_module_osTimer);

#endif /* MICROPY_QPY_MODULE_OSTIMER */
