#include <iostream>
#include <fstream>
#include "direct.h"
#include "associative.h"

using namespace std;

int cache_d::mem_write_cnt = 0;
int cache_d::miss = 0;
int cache_a::mem_write_cnt_a = 0;
int cache_a::miss_a = 0;

int main(int argc, char *argv[])
{
    char file_name[15];
    sprintf(file_name, "trace%s.txt", argv[2]);

    ifstream in(file_name, ios::binary);
    string contents;
    char buff[10];
    int x;

    if(in.is_open())
    {
        if(*argv[1] == '0') //direct map
        {
            cache_d cache[1024];

            while(in)
            {

                in.getline(buff,12);
                direct_map_cache(buff,cache);

            }
            printf("%d %d", cache_d::miss, cache_d::mem_write_cnt);

        }

        else if(*argv[1] == '1') //associative
        {
            cache_a cache[512];

            while(in)
            {
                in.getline(buff,12);
                associative_cache(buff,cache);
            }
            printf("%d %d", cache_a::miss_a, cache_a::mem_write_cnt_a);

        }


    }
    else
    {
        cout << "you" <<endl;
    }






}
