#include <iostream>
#include "hbase.h"
using namespace std;
int main()
{
    char buf[MAX_PATH];
    cout << get_executable_dir( buf, MAX_PATH) <<endl;
    cout <<"hello world" <<endl;
    return 0;
}