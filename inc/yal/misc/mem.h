#ifndef __yal_misc_mem_H__
#define __yal_misc_mem_H__

#ifdef __cplusplus
extern "C" {
#endif

#define YAL_NEW(T, V) T* V = malloc(sizeof(T));
#define YAL_DELETE(V) \
    free(V); \
    V = NULL;

#ifdef __cplusplus
}
#endif

#endif