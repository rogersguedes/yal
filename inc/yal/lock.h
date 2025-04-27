#ifndef __yal_lock_H__
#define __yal_lock_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(YAL_LOCK_POSIX)
#elif defined(YAL_LOCK_FREERTOS)
#else
#error "Locking mechanism is not set. Please specify it. Available options: YAL_LOCK_POSIX, YAL_LOCK_FREERTOS"
#endif

#ifdef __cplusplus
}
#endif

#endif