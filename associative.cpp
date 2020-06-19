#include "associative.h"
#include <iostream>



address_chopper_a::address_chopper_a(char* inst)
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
            int value = (int)inst[k] - 65;
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
    unsigned int digit_t = 65536;
    for(int i = 0; i < 17; i++)
    {
        tag_num += address[31-i] * digit_t;
        digit_t /= 2;
    }
    this->tag = tag_num;
    //printf("tag %u ", this->tag);

    //index def
    int index_num = 0;
    int digit_i = 256;
    for(int i = 0; i<9;i++)
    {
        index_num += address[14-i]*digit_i;
        digit_i /=2;
    }
    this->index = index_num;
    //printf("index %d ", this->index);



}



void associative_cache(char* inst, cache_a* cache)
{


    address_chopper_a address(inst);  //decode inst

    if(address.get_inst_type() == 0)    //load
    {
        if((cache[address.get_index()].is_valid_1()==1 && cache[address.get_index()].get_tag_1()==address.get_tag())
        || (cache[address.get_index()].is_valid_2()==1 && cache[address.get_index()].get_tag_2()==address.get_tag()) ) //load hit
        {
            cache[address.get_index()].set_LRU();
        }
        else //load miss
        {
            if(cache[address.get_index()].get_LRU()==0) //LRU point 1
            {
                cache_a::miss_a ++;
                if(cache[address.get_index()].is_dirty_1() == 1)
                {
                    cache_a::mem_write_cnt_a ++;
                    cache[address.get_index()].set_dirty_1();
                }
                cache[address.get_index()].set_LRU();
                cache[address.get_index()].set_valid_1();
                cache[address.get_index()].set_tag_1(address.get_tag());
            }
            else //LRU point 2
            {
                cache_a::miss_a ++;
                if(cache[address.get_index()].is_dirty_2() == 1)
                {
                    cache_a::mem_write_cnt_a ++;
                    cache[address.get_index()].set_dirty_2();
                }
                cache[address.get_index()].set_LRU();
                cache[address.get_index()].set_valid_2();
                cache[address.get_index()].set_tag_2(address.get_tag());
            }

        }


    }

    else if(address.get_inst_type() == 1)   //store
    {
        if((cache[address.get_index()].is_valid_1()==1 && cache[address.get_index()].get_tag_1()==address.get_tag())) //store hit 1
        {
            cache[address.get_index()].set_LRU();
            if(cache[address.get_index()].is_dirty_1() == 1)
            {
                cache_a::mem_write_cnt_a ++;
            }
            else
            {
                cache[address.get_index()].set_dirty_1();
            }

        }

        else if((cache[address.get_index()].is_valid_2()==1 && cache[address.get_index()].get_tag_2()==address.get_tag())) //store hit 2
        {
            cache[address.get_index()].set_LRU();
            if(cache[address.get_index()].is_dirty_2() == 1)
            {
                cache_a::mem_write_cnt_a ++;
            }
            else
            {
                cache[address.get_index()].set_dirty_2();
            }
        }

        else //store miss
        {
            if(cache[address.get_index()].get_LRU()==0) //LRU point 1
            {
                cache_a::miss_a ++;
                cache[address.get_index()].set_LRU();
                if(cache[address.get_index()].is_dirty_1() == 1)
                {
                    cache_a::mem_write_cnt_a ++;
                }
                else
                {
                    cache[address.get_index()].set_dirty_1();
                }
                cache[address.get_index()].set_valid_1();
                cache[address.get_index()].set_tag_1(address.get_tag());
            }
            else //LRU point 2
            {
                cache_a::miss_a ++;
                cache[address.get_index()].set_LRU();
                if(cache[address.get_index()].is_dirty_2() == 1)
                {
                    cache_a::mem_write_cnt_a ++;
                }
                else
                {
                    cache[address.get_index()].set_dirty_2();
                }
                cache[address.get_index()].set_valid_2();
                cache[address.get_index()].set_tag_2(address.get_tag());
            }

        }

    }


}




