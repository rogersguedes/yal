#ifndef __yal_mutex_H__
#define __yal_mutex_H__

#ifdef __cplusplus
extern "C" {
#endif

// #define YAL_THREAD_MSVC 1 //FIXME remove after tests

#if defined(YAL_THREAD_POSIX)
#elif defined(YAL_THREAD_FREERTOS)
#elif defined(YAL_THREAD_MSVC)
#    include <windows.h>
typedef HANDLE yal_mutex_t;
#elif defined(YAL_THREAD_NONE)
#else
#    error "Locking mechanism is not set. Please specify it. Available options: YAL_THREAD_POSIX, YAL_THREAD_FREERTOS"
#endif

static inline int yal_mutex_init(yal_mutex_t* lock)
{
#if defined(YAL_THREAD_POSIX)
#elif defined(YAL_THREAD_FREERTOS)
#elif defined(YAL_THREAD_MSVC)
    *lock = CreateMutexA(NULL, FALSE, NULL);
    return *lock != NULL ? 0 : ENOMEM;
#endif
}

static inline int yal_mutex_deinit(yal_mutex_t* lock)
{
#if defined(YAL_THREAD_POSIX)
#elif defined(YAL_THREAD_FREERTOS)
#elif defined(YAL_THREAD_MSVC)
    BOOL result = CloseHandle(*lock);
    return result ? 0 : -1;
#endif
}

static inline int yal_mutex_lock(yal_mutex_t* lock)
{
#if defined(YAL_THREAD_POSIX)
#elif defined(YAL_THREAD_FREERTOS)
#elif defined(YAL_THREAD_MSVC)
    DWORD result = WaitForSingleObject(*lock, INFINITE);
    return result == WAIT_OBJECT_0 ? 0 : -1;
#endif
}

static inline int yal_mutex_unlock(yal_mutex_t* lock)
{
#if defined(YAL_THREAD_POSIX)
#elif defined(YAL_THREAD_FREERTOS)
#elif defined(YAL_THREAD_MSVC)
    BOOL result = ReleaseMutex(*lock);
    return result ? 0 : -1;
#endif
}

#ifdef __cplusplus
}
#endif

#endif