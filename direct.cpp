#include "direct.h"
#include <iostream>




address_chopper::address_chopper(char* inst)
{
    //inst type def
    if(inst[0] == 'L')
    {
        this->inst_type = 0;
    }
    else if (inst[0] == 'S')
    {
        this->inst_type = 1;
    }
    //printf("type %d ", this->inst_type);

    int address[32] = {0,};

    for(int k = 2 ; k < 10;k++)
    {
        if(48 <= (int)inst[k] && (int)inst[k] <= 57)    //number
        {
            int value = (int)inst[k] - 48;
            //printf("value %d\n", value);
            for(int i = 0; i<3;i++)
            {
                address[31-4*(k-2)-i] = value % 2;
                //printf("address value %d\n", address[31-k-2-i]);
                value /=2;
            }
            address[31-4*(k-2)-3] = value;
            //printf("address value %d\n", address[31-k-2-3]);
        }
        else if(65 <= (int)inst[k])     //alphabet
        {
            //printf("fuckkkkkkkkkk\n");
            int value = (int)inst[k] - 55;
            //printf("value %d\n", value);
            for(int i = 0; i<3;i++)
            {
                address[31-4*(k-2)-i] = value % 2;
                value /=2;
            }
            address[31-4*(k-2)-3] = value;
        }
    }


    //tag def
    unsigned int tag_num = 0;
    unsigned int digit_t = 131072;
    for(int i = 0; i < 18; i++)
    {
        tag_num += address[31-i] * digit_t;
        digit_t /= 2;
    }
    this->tag = tag_num;
    //printf("tag %u ", this->tag);

    //index def
    int index_num = 0;
    int digit_i = 512;
    for(int i = 0; i<10;i++)
    {
        index_num += address[13-i]*digit_i;
        digit_i /=2;
    }
    this->index = index_num;
    //printf("index %d ", this->index);



}


void direct_map_cache(char* inst, cache_d* cache)
{


    address_chopper address(inst);  //decode inst

    if(address.get_inst_type() == 0)    //load
    {

        if(cache[address.get_index()].get_tag()==address.get_tag() && cache[address.get_index()].is_valid()==1) //load hit
        {
            //printf("load hit\n");
        }
        else if(cache[address.get_index()].get_tag()!= address.get_tag() || cache[address.get_index()].is_valid()==0) //load miss
        {
            cache_d::miss ++;
            cache[address.get_index()].set_valid();
            cache[address.get_index()].set_tag(address.get_tag());
            //printf("load miss\n");
        }


    }

    else if(address.get_inst_type() == 1)   //store
    {
        if(cache[address.get_index()].get_tag()==address.get_tag() && cache[address.get_index()].is_valid()==1) //store hit
        {
            cache_d::mem_write_cnt ++;
            //printf("store hit\n");

        }
        else if(cache[address.get_index()].get_tag()!= address.get_tag() || cache[address.get_index()].is_valid()==0) //store miss
        {
            cache_d::miss ++;
            cache_d::mem_write_cnt ++;
            //printf("store miss\n");
        }

    }


}
