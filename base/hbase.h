#pragma once

#include "hexport.h"
#include "hplatform.h"
#include "hdef.h"

//--------------------------SAFE ALLOC/FREE-----------------
HV_EXPORT void* safe_malloc(size_t size);
HV_EXPORT void* safe_realloc(void* oldptr, size_t newsize, size_t oldsize);
HV_EXPORT void* safe_calloc(size_t nmemb, size_t size);
HV_EXPORT void* safe_zalloc(size_t size);
HV_EXPORT void  safe_free(void* ptr);

#define HV_ALLOC(ptr, size)\
    do{\
        *((void**)&(ptr)) = safe_zalloc(size);\
        printd("alloc(%p, size=%llu)\tat [%s:%d:%s]\n", ptr, (unsigned long long)size, __FILE__, __LINE__, __FUNCTION__);\
    }while(0)

#define HV_ALLOC_SIZEOF(ptr) HV_ALLOC(ptr, sizeof(*(ptr)))

#define HV_FREE(ptr)\
    do{\
        if(ptr)\
        {\
            safe_free(ptr);\
            printd("free( %p )\tat [%s:%d:%s]\n", ptr, __FILE__, __LINE__, __FUNCTION__);\
            ptr = NULL;\
        }\
    }while(0)

HV_EXPORT long hv_alloc_cnt();
HV_EXPORT long hv_free_cnt();
static inline void hv_memcheck()
{
    printf("Memcheck => alloc:%ld free:%ld\n", hv_alloc_cnt(), hv_free_cnt());
}

#define HV_MEMECHECK atexit(hv_memcheck) //register a func when exit called

//------------------------SAFE STRING--------------------------
HV_EXPORT char* strupper(char* str);
HV_EXPORT char* strlower(char* str);
HV_EXPORT char* strreverse(char* str);

HV_EXPORT bool strstartswitch(const char* str, const char* start);
HV_EXPORT bool strendswitch(const char* str, const char* end);
HV_EXPORT bool strcontains(const char* str, const char* sub);

// strncpy n = sizeof(dest_buf)-1 !!! because strncpy will not add '\0'
// safe_strncpy n = sizeof(dest_buf)
HV_EXPORT char* safe_strncpy(char* dest, const char* src, size_t n);

// strncat n = sizeof(dest_buf)-1-strlen(dest)
// safe_strncpy n = sizeof(dest_buf)
HV_EXPORT char* safe_strncat(char* dest, const char* src, size_t n);

#define strlcpy safe_strncpy
#define strlcat safe_strncat

#define strrchr_dot(str) strrchr(str, '.')
HV_EXPORT const char* strrchr_dir(const char* filepath);

//basename
HV_EXPORT const char* hv_basename(const char* filepath);
HV_EXPORT const char* hv_suffixname(const char* filename);
//mkdir -p
HV_EXPORT int hv_mkdir_p(const char* dir);
//rmdir -p
HV_EXPORT int hv_rmdir_p(const char* dir);

//1 y on yes true enable
HV_EXPORT bool getboolean(const char* str);

HV_EXPORT char* get_executable_path(char* buf, int size);
HV_EXPORT char* get_executable_dir(char* buf, int size);
HV_EXPORT char* get_executable_file(char* buf, int size);
HV_EXPORT char* get_run_dir(char* buf, int size);
