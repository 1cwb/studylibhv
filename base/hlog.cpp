#include "hlog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define hmutex_t            pthread_mutex_t
#define hmutex_init(mutex)  pthread_mutex_init(mutex, NULL)
#define hmutex_destroy      pthread_mutex_destroy
#define hmutex_lock         pthread_mutex_lock
#define hmutex_unlock       pthread_mutex_unlock

#define SECONDS_PER_HOUR    3600
#define SECONDS_PER_DAY     86400
#define SECONDS_PER_WEEK    604800

static int s_gmtoff = 28800; /*8*3600*/

struct logger_s
{
    logger_handler  handler;
    unsigned int    bufsize;
    char*           buf;
    int             level;
    int             enable_color;

    //for file logger
    char                filepath[256];
    unsigned long long  max_filesize;
    int                 remain_days;
    int                 enable_fsync;
    FILE*               fp_;
    char                cur_logfile[256];
    time_t              last_logfile_ts;
    int                 can_write_cnt;

    hmutex_t            mutex_;
};

static void logger_init(logger_t* logger)
{
    logger->handler = NULL;
    logger->bufsize = DEFAULT_LOG_MAX_BUFSIZE;
    logger->buf = (char*) malloc(logger->bufsize);

    logger->level = DEFAULT_LOG_LEVEL;
    logger->enable_color = 0;

    logger->fp_ = NULL;
    logger->max_filesize = DEFAULT_LOG_MAX_FILESIZE;
    logger->remain_days = DEFAULT_LOG_REMAIN_DAYS;
    logger->enable_fsync = 1;
    logger->last_logfile_ts = 0;
    logger->can_write_cnt = -1;
    logger_set_file(logger, DEFAULT_LOG_FILE);
    hmutex_init(&logger->mutex_);
}

logger_t* logger_create()
{
    time_t ts = time(NULL);
    struct tm* local_tm = localtime(&ts);
    int local_hour = local_tm->tm_hour;
    struct tm* gmt_tm = gmtime(&ts);
    int gmt_hour = gmt_tm->tm_hour;
    s_gmtoff = (local_hour - gmt_hour) * SECONDS_PER_HOUR;

    logger_t* logger = (logger_t*)malloc(sizeof(logger_t));
    logger_init(logger);
    return logger;
}

void logger_destroy(logger_t* logger)
{
    if(logger)
    {
        if(logger->buf)
        {
            free(logger->buf);
            logger->buf = NULL;
        }
        if(logger->fp_)
        {
            fclose(logger->fp_);
            logger->fp_ = NULL;
        }
        hmutex_destroy(&logger->mutex_);
        free(logger);
    }
}

void logger_set_handler(logger_t* logger, logger_handler fn)
{
    logger->handler = fn;
}

void logger_set_level(logger_t* logger, int level)
{
    logger->level = level;
}

void logger_set_level_by_str(logger_t* logger, const char* level)
{
    int loglevel = DEFAULT_LOG_LEVEL;
    if(strcmp(level, "VEBOSE") == 0)
    {
        loglevel = LOG_LEVEL_VEBOSE;
    }
    else if(strcmp(level, "DEBUG") == 0)
    {
        loglevel = LOG_LEVEL_DEBUG;
    }
    else if(strcmp(level, "INFO") == 0)
    {
        loglevel = LOG_LEVEL_INFO;
    }
    else if(strcmp(level, "WARN") == 0)
    {
        loglevel = LOG_LEVEL_WARN;
    }
    else if(strcmp(level, "ERROR") == 0)
    {
        loglevel = LOG_LEVEL_ERROR;
    }
    else if(strcmp(level, "FATAL") == 0)
    {
        loglevel = LOG_LEVEL_FATAL;
    }
    else if(strcmp(level, "SILENT") == 0)
    {
        loglevel = LOG_LEVEL_SILENT;
    }
    logger->level = loglevel;
}

void logger_set_remain_days(logger_t* logger, int days)
{
    logger->remain_days = days;
}

void logger_set_max_bufsize(logger_t* logger, unsigned int bufsize)
{
    logger->bufsize = bufsize;
    logger->buf = (char*)realloc(logger->buf, bufsize);
}

void logger_enable_color(logger_t* logger, int on)
{
    logger->enable_color = on;
}

void logger_set_file(logger_t* logger, const char* filepath)
{
    strncpy(logger->filepath, filepath, sizeof(logger->filepath));
    char* suffix = strrchr(logger->filepath, '.');
    if(suffix && strcmp(suffix, ".log") == 0)
    {
        *suffix = '\0';
    }
}

void logger_set_max_filesize(logger_t* logger, unsigned long long filesize) {
    logger->max_filesize = filesize;
}

void logger_set_max_filesize_by_str(logger_t* logger, const char* str)
{
    
}