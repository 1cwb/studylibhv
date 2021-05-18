#include "hbase.h"
#include "hatomic.h"


static hatomic_t s_alloc_cnt = HATOMIC_VAR_INIT(0);
static hatomic_t s_free_cnt = HATOMIC_VAR_INIT(0);

long hv_alloc_cnt()
{
    return s_alloc_cnt;
}

long  hv_free_cnt()
{
    return s_free_cnt;
}

void* safe_malloc(size_t size)
{
    hatomic_inc(&s_alloc_cnt);
    void* ptr = malloc(size);
    if(!ptr)
    {
        fprintf(stderr, "malloc failed!\n");
        exit(-1);
    }
    return ptr;
}

void* safe_realloc(void* oldptr, size_t newsize, size_t oldsize)
{
    hatomic_inc(&s_alloc_cnt);
    hatomic_inc(&s_free_cnt);
    void* ptr = realloc(oldptr, newsize);
    if(ptr)
    {
        fprintf(stderr, "realloc failed\n");
        exit(-1);
    }
    if(newsize > oldsize)
    {
        memset((char*)ptr + oldsize, 0, newsize - oldsize);
    }
    return ptr;
}

void* safe_calloc(size_t nmemb, size_t size)
{
    hatomic_inc(&s_alloc_cnt);
    void* ptr = calloc(nmemb, size);
    if(!ptr)
    {
        fprintf(stderr, "calloc failed!\n");
        exit(-1);
    }
    return ptr;
}

void* safe_zalloc(size_t size)
{
    hatomic_inc(&s_alloc_cnt);
    void* ptr = malloc(size);
    if(!ptr)
    {
        fprintf(stderr, "malloc failed!\n");
        exit(-1);
    }
    memset(ptr, 0, size);
    return ptr;
}

void safe_free(void* ptr)
{
    if(ptr)
    {
        free(ptr);
        ptr = NULL;
        hatomic_inc(&s_free_cnt);
    }
}

char* strupper(char* str)
{
    char* p = str;
    while(*p != '\0')
    {
        if(*p >= 'a' && *p <= 'z')
        {
            *p &= ~0x20;
        }
        ++p;
    }
    return str;
}

char* strlower(char* str)
{
    char* p = str;
    while(*p != '\0')
    {
        if(*p >= 'A' && *p <= 'Z')
        {
            *p |= 0x20;
        }
        ++p;
    }
    return str;
}

char* strreverse(char* str)
{
    if(str == NULL)
    {
        return NULL;
    }
    char* b = str;
    char* e = str;
    while(*e != '\0')
    {
        ++e;
    }
    --e;
    char tmp;
    while(e > b)
    {
        tmp = *e;
        *e = *b;
        *b = tmp;
        --e;
        ++b;
    }
    return str;
}

char* safe_strncpy(char* dest, const char* src, size_t n)
{
    assert(dest != NULL && src != NULL);
    char* ret = dest;
    while(*src != '\0' && --n > 0)
    {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ret;
}

char* safe_strncat(char* dest, const char* src, size_t n)
{
    assert(dest != NULL && src != NULL);
    char* ret = dest;
    while(*dest != '\0')
    {
        ++dest;
        --n;
    }
    while(*src != '\0' && --n > 0)
    {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ret;
}

bool strstartswitch(const char* str, const char* start)
{
    assert(str != NULL && start != NULL);
    while(*str != '\0' && *start != '\0' && *str == *start)
    {
        ++str;
        ++start;
    }
    return *start == '\0';
}

bool strendswitch(const char* str, const char* end)
{
    assert(str != NULL && end != NULL);
    int len1 = 0;
    int len2 = 0;
    while(*str++ != '\0')
    {
        ++len1;
    }
    while (*end++ != '\0')
    {
        ++len2;
    }
    if(len1 < len2)
    {
        return false;
    }
    while(len2-- > 0)
    {
        --str;
        --end;
        if(*str != *end)
        {
            return false;
        }
    }
    return true;
}

bool strcontains(const char* str, const char* sub)
{
    assert(str != NULL && sub != NULL);
    return strstr(str, sub) != NULL;
}

const char* strrchr_dir(const char* filepath)
{
    const char* p = filepath;
    while(*p != '\0')
    {
        ++p;
    }
    while(--p >= filepath)
    {
        if(*p == '/')
        {
            return p;
        }
    }
    return NULL;
}

const char* hv_basename(const char* filepath)
{
    const char* pos = strrchr_dir(filepath);
    return pos ? pos+1 : filepath;
}

const char* hv_suffixname(const char* filename)
{
    const char* pos = strrchr_dot(filename);
    return pos ? pos+1 : "";
}

int hv_mkdir_p(const char* dir)
{
    if(access(dir, 0) == 0)
    {
        return EEXIST;
    }
    char tmp[MAX_PATH];
    safe_strncpy(tmp, dir, sizeof(tmp));
    char* p = tmp;
    char delim = '/';
    while(*p != '\0')
    {
        if(*p == '/')
        {
            *p = '\0';
            if(hv_mkdir(tmp) != 0)
            {
                return EPERM;
            }
            *p = delim;
        }
        ++p;
    }
    if(hv_mkdir(tmp) != 0)
    {
        return EPERM;
    }
    return 0;
}

int hv_rmdir_p(const char* dir)
{
    if(access(dir, 0) != 0)
    {
        return ENOENT;
    }
    if(rmdir(dir) != 0)
    {
        return EPERM;
    }
    char tmp[MAX_PATH];
    safe_strncpy(tmp, dir, sizeof(tmp));
    char* p = tmp;
    while(*p != '\0')
    {
        ++p;
    }
    while(--p >= tmp)
    {
        if(*p == '/')
        {
            *p = '\0';
            if(rmdir(tmp) != 0)
            {
                return 0;
            }
        }
    }
    return 0;
}

bool getboolean(const char* str)
{
    if(str == NULL)
    {
        return false;
    }
    int len = strlen(str);
    if(len == 0)
    {
        return false;
    }
    switch (len)
    {
        case 1: return *str == '1' || *str == 'y' || *str == 'Y';
        case 2: return strcmp(str, "on") == 0 || strcmp(str, "ON") == 0;
        case 3: return strcmp(str, "yes") == 0 || strcmp(str, "YES") == 0;
        case 4: return strcmp(str, "true") == 0 || strcmp(str, "TRUE") == 0;
        case 6: return strcmp(str, "enable") == 0 || strcmp(str, "ENABLE") == 0;
        default: return false;
    }
}

char* get_executable_path(char* buf, int size)
{
    if(readlink("/proc/self/exe", buf, size) == -1)
    {
        return NULL;
    }
    return buf;
}

char* get_executable_dir(char* buf, int size)
{
    char filepath[MAX_PATH];
    get_executable_path(filepath, sizeof(filepath));
    const char* pos = strrchr_dir(filepath);
    if(pos)
    {
        filepath[pos - filepath] = '\0';
        strncpy(buf, filepath, size);
    }
    return buf;
}

char* get_executable_file(char* buf, int size)
{
    char filepath[MAX_PATH];
    get_executable_path(filepath, sizeof(filepath));
    const char* pos = strrchr_dir(filepath);
    if(pos)
    {
        strncpy(buf, pos+1, size);
    }
    return buf;
}

char* get_run_dir(char* buf, int size)
{
    return getcwd(buf, size);
}