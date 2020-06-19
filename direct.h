#ifndef DIRECT_H_INCLUDED
#define DIRECT_H_INCLUDED

#include <iostream>

class cache_d {

private:
    bool valid;
    unsigned int tag;


public:
    cache_d() {valid = 0; tag = 0; }
    ~cache_d() {}

    static int mem_write_cnt;
    static int miss;

    bool is_valid() {return valid;}
    void set_valid() {if(valid==0) valid = !valid; }
    unsigned int get_tag() {return tag;}
    void set_tag(unsigned int tag_num) {tag = tag_num;}


};

class address_chopper {

private:
    unsigned int tag;
    int index;
    int inst_type;

public:
    address_chopper() {tag = 0; index = 0;inst_type=0;}
    address_chopper(char* inst);
    int get_inst_type() {return inst_type;}
    unsigned int get_tag() {return tag;}
    int get_index() {return index;}

};


void direct_map_cache(char* inst, cache_d* cache);




#endif // DIRECT_H_INCLUDED
