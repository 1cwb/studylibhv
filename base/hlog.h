#pragma once
/*
* time 与 gettimeofday 两个函数得到的都是从Epoch开始到当前的秒数(tt=tv.tv_sec)，而后者还能得到更精细的微秒级结果，
* 即tv_sec*(10^6)+tv_usec为从Epoch开始到当前的微秒数
* time_t time(time_t *t); 
* 函数说明：此函数会返回从公元 1970 年1 月1 日的UTC 时间从0 时0 分0 秒算起到现在所经过的秒数。
* 如果t 并非空指针的话，此函数也会将返回值存到t 指针所指的内存。
* 	
* int gettimeofday(struct timeval *tv, struct timezone *tz);
* 用于获取调用该代码时，距离Epoch的时间。
*
* struct tm 与日期和时间相关的数据结构
* struct tm * gmtime(const time_t *timer);                                          
* struct tm * localtime(const time_t * timer);

* 其中gmtime()函数是将日历时间转化为世界标准时间（即格林尼治时间），并返回一个tm结构体来保存这个时间，
* 而localtime()函数是将日历时间转化为本地时间。比如现在用gmtime()函数获得的世界标准时间是2005年7月30日7点18分20秒，
* 那么我用localtime()函数在中国地区获得的本地时间会比时间标准时间晚8个小时，即2005年7月30日15点18分20秒。下面是个例子：
*
*
* ============================================================================================================
* hlog call flow:
* first call hv_default_logger()
* it will call logger_create() to create a logger_t, 
* then call malloc and call logger_init()
* if you call logger_print(logger_t* logger, int level, const char* fmt, ...)
* 
*/

/*
 * hlog is thread safe
 */
#include <string.h>
#include "hexport.h"

#define DIR_SEPARATOR '/'
#define DIR_SEPARATOR_STR "/"

#ifndef __FILENAME__
    #define __FILENAME__ (strrchr(DIR_SEPARATOR_STR __FILE__, DIR_SEPARATOR) + 1)
#endif

#define CLR_CLR         "\033[0m"       /* 恢复颜色 */
#define CLR_BLACK       "\033[30m"      /* 黑色字 */
#define CLR_RED         "\033[31m"      /* 红色字 */
#define CLR_GREEN       "\033[32m"      /* 绿色字 */
#define CLR_YELLOW      "\033[33m"      /* 黄色字 */
#define CLR_BLUE        "\033[34m"      /* 蓝色字 */
#define CLR_PURPLE      "\033[35m"      /* 紫色字 */
#define CLR_SKYBLUE     "\033[36m"      /* 天蓝字 */
#define CLR_WHITE       "\033[37m"      /* 白色字 */

#define CLR_BLK_WHT     "\033[40;37m"   /* 黑底白字 */
#define CLR_RED_WHT     "\033[41;37m"   /* 红底白字 */
#define CLR_GREEN_WHT   "\033[42;37m"   /* 绿底白字 */
#define CLR_YELLOW_WHT  "\033[43;37m"   /* 黄底白字 */
#define CLR_BLUE_WHT    "\033[44;37m"   /* 蓝底白字 */
#define CLR_PURPLE_WHT  "\033[45;37m"   /* 紫底白字 */
#define CLR_SKYBLUE_WHT "\033[46;37m"   /* 天蓝底白字 */
#define CLR_WHT_BLK     "\033[47;30m"   /* 白底黑字 */

//XXX(id, str, clr)
#define LOG_LEVEL_MAP(XXX) \
    XXX(LOG_LEVEL_DEBUG, "DEBUG", CLR_WHITE)     \
    XXX(LOG_LEVEL_INFO,  "INFO",  CLR_GREEN)     \
    XXX(LOG_LEVEL_WARN,  "WARN",  CLR_YELLOW)    \
    XXX(LOG_LEVEL_ERROR, "ERROR", CLR_RED)       \
    XXX(LOG_LEVEL_FATAL, "FATAL", CLR_RED_WHT)
    
typedef enum
{
    LOG_LEVEL_VEBOSE = 0,
#define XXX(id, str, clr) id,
    LOG_LEVEL_MAP(XXX)
#undef  XXX
    LOG_LEVEL_SILENT
}log_level_e;

#define DEFAULT_LOG_FILE            "libhv"
#define DEFAULT_LOG_LEVEL           LOG_LEVEL_INFO
#define DEFAULT_LOG_REMAIN_DAYS     1
#define DEFAULT_LOG_MAX_BUFSIZE     (1 << 14) //16k
#define DEFAULT_LOG_MAX_FILESIZE    (1 << 24) //16M

// logger: default file_logger
// network_logger() see event/nlog.h
typedef void (*logger_handler)(int loglevel, const char* buf, int len);

HV_EXPORT void stdout_logger(int loglevel, const char* buf, int len);
HV_EXPORT void stderr_logger(int loglevel, const char* buf, int len);
HV_EXPORT void file_logger(int loglevel, const char* buf, int len);

typedef struct logger_s logger_t;
HV_EXPORT logger_t* logger_create();
HV_EXPORT void logger_destroy(logger_t* logger);

HV_EXPORT void logger_set_handler(logger_t* logger, logger_handler fn);
HV_EXPORT void logger_set_level(logger_t* logger, int level);

HV_EXPORT void logger_set_level_by_str(logger_t* logger, const char* level);
HV_EXPORT void logger_set_max_bufsize(logger_t* logger, unsigned int bufsize);
HV_EXPORT void logger_enable_color(logger_t* logger, int on);
HV_EXPORT int logger_print(logger_t* logger, int level, const char* fmt, ...);

//file log
HV_EXPORT void logger_set_file(logger_t* logger, const char* filepath);
HV_EXPORT void logger_set_max_filesize(logger_t* logger, unsigned long long filesize);
HV_EXPORT void logger_set_max_filesize_by_str(logger_t* logger, const char* filesize);
HV_EXPORT void logger_set_remain_days(logger_t* logger, int days);
HV_EXPORT void logger_enable_fsync(logger_t* logger, int on);
HV_EXPORT void logger_fsync(logger_t* logger);
HV_EXPORT const char* logger_get_cur_file(logger_t* logger);

HV_EXPORT logger_t* hv_default_logger();

//macro hlog
#define hlog                            hv_default_logger()
#define hlog_set_file(filepath)         logger_set_file(hlog, filepath)
#define hlog_set_level(level)           logger_set_level(hlog, level)
#define hlog_set_level_by_str(level)    logger_set_level_by_str(hlog, level)
#define hlog_set_max_filesize(filesize) logger_set_max_filesize(hlog, filesize)
#define hlog_set_max_filesize_by_str(filesize) logger_set_max_filesize_by_str(hlog, filesize)
#define hlog_set_remain_days(days)      logger_set_remain_days(hlog, days)
#define hlog_enable_fsync()             logger_enable_fsync(hlog, 1)
#define hlog_disable_fsync()            logger_enable_fsync(hlog, 0)
#define hlog_enable_color()             logger_enable_color(hlog, 1)
#define hlog_disable_color()            logger_enable_color(hlog, 0)
#define hlog_fsync()                    logger_fsync(hlog)
#define hlog_get_cur_file()             logger_get_cur_file(hlog)
#define hlog_destroy()                  logger_destroy(hlog)

#define hlogd(fmt, ...) logger_print(hlog, LOG_LEVEL_DEBUG, fmt " [%s:%d:%s]\n", ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)
#define hlogi(fmt, ...) logger_print(hlog, LOG_LEVEL_INFO,  fmt " [%s:%d:%s]\n", ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)
#define hlogw(fmt, ...) logger_print(hlog, LOG_LEVEL_WARN,  fmt " [%s:%d:%s]\n", ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)
#define hloge(fmt, ...) logger_print(hlog, LOG_LEVEL_ERROR, fmt " [%s:%d:%s]\n", ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)
#define hlogf(fmt, ...) logger_print(hlog, LOG_LEVEL_FATAL, fmt " [%s:%d:%s]\n", ## __VA_ARGS__, __FILENAME__, __LINE__, __FUNCTION__)

#if !defined(LOGD) && !defined(LOGI) && !defined(LOGW) && !defined(LOGE) && !defined(LOGF)
#define LOGD    hlogd
#define LOGI    hlogi
#define LOGW    hlogw
#define LOGE    hloge
#define LOGF    hlogf
#endif