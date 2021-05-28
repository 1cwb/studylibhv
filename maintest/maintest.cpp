#include <iostream>
#include "hbase.h"
#include "hbuf.h"
#include "hlog.h"

using namespace std;
int main()
{
    hlog_set_level(LOG_LEVEL_DEBUG);
    hlog_enable_color();
    //logger_t* logger = hv_default_logger();
    //logger_enable_color(logger, 1);
    //logger_set_level(logger,LOG_LEVEL_DEBUG);
    hlogd("hello worldww");
    hloge("hello worldww");
    printf("\033[31m xsdsds");

    //logger_destroy(logger);
    hlog_destroy();
    return 0;
}