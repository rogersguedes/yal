#ifndef __yal_misc_array_H__
#define __yal_misc_array_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ARRAY_ITEMS(a) (sizeof(a) / sizeof((a)[0]))

#define ARRAY_SIZEOF(a) (sizeof(a))

#define ARRAY_LEN(__type, __num) (sizeof(__type) * (__num))

#ifdef __cplusplus
}
#endif

#endif