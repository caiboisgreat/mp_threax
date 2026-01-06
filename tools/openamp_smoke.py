# OpenAMP smoke test (build/import only)
# Note: STM32F405 is single-core; without a real remote endpoint, endpoints may not become ready.

import openamp

print("openamp imported")
print("ENDPOINT_ADDR_ANY=", openamp.ENDPOINT_ADDR_ANY)

def on_ns(dest, name):
    print("ns:", dest, name)

openamp.new_service_callback(on_ns)
print("new_service_callback set")
