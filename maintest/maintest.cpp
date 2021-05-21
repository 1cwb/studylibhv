#include <iostream>
#include "hbase.h"
#include "hbuf.h"
using namespace std;
int main()
{
    char buf[MAX_PATH];
    cout << get_executable_dir( buf, MAX_PATH) <<endl;
    cout <<"hello world" <<endl;
    HBuf test(buf, MAX_PATH);
    cout <<offsetof(hbuf_s ,base) <<endl;
    cout <<strstartswitch("ABCD" ,"ABC") <<endl;
    cout <<strrchr_dir("/etc/mm/hello") <<endl;
    return 0;
}