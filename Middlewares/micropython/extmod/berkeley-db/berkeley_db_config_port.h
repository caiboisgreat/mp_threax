// Berkeley-db configuration.

#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

// Forward declarations to avoid pulling in MicroPython headers here.
// These symbols are provided by the MicroPython core.
void *m_malloc_maybe(size_t num_bytes);
void *m_realloc_maybe(void *ptr, size_t new_num_bytes, bool allow_move);
void m_free(void *ptr);

#define __DBINTERFACE_PRIVATE 1
#define mpool_error printf
#define abort abort_
#define virt_fd_t void*

static inline void *bdb_malloc(size_t n) {
	void *p = m_malloc_maybe(n);
	if (p == NULL && n != 0) {
		errno = ENOMEM;
	}
	return p;
}

static inline void *bdb_calloc(size_t n, size_t m) {
	size_t total = n * m;
	void *p = m_malloc_maybe(total);
	if (p == NULL && total != 0) {
		errno = ENOMEM;
		return NULL;
	}
	if (total != 0) {
		memset(p, 0, total);
	}
	return p;
}

static inline void *bdb_realloc(void *ptr, size_t n) {
	void *p = m_realloc_maybe(ptr, n, true);
	if (p == NULL && n != 0) {
		errno = ENOMEM;
	}
	return p;
}

static inline void bdb_free(void *ptr) {
	if (ptr != NULL) {
		m_free(ptr);
	}
}

#define malloc(n) bdb_malloc((n))
#define calloc(n, m) bdb_calloc((n), (m))
#define realloc(p, n) bdb_realloc((p), (n))
#define free(p) bdb_free((p))

// berkeley-db internal panic hook (implemented by MicroPython's modbtree).
// Forward declare the DB type to avoid pulling in db.h here.
struct __db;
void __dbpanic(struct __db *db);

#ifdef MICROPY_BERKELEY_DB_DEFPSIZE
#define DEFPSIZE MICROPY_BERKELEY_DB_DEFPSIZE
#endif

#ifdef MICROPY_BERKELEY_DB_MINCACHE
#define MINCACHE MICROPY_BERKELEY_DB_MINCACHE
#endif

__attribute__((noreturn)) void abort_(void);
