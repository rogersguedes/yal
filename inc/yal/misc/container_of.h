#ifndef __yal_misc_container_of_H__
#define __yal_misc_container_of_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#ifndef offsetof
#    define offsetof(__type_name, __member_name) ((size_t)(&((__type_name*)0)->(__member_name)))
#endif

#ifndef container_of
#    define container_of(__member_ptr, __type_name, __member_name) \
        ((__type_name*)((uint8_t*)__member_ptr - offsetof(__type_name, __member_name)))
#endif

#ifdef __cplusplus
}
#endif

#endif