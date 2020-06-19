#ifndef ASSOCIATIVE_H_INCLUDED
#define ASSOCIATIVE_H_INCLUDED

#include <iostream>

class cache_a {

private:
    bool valid_1;
    bool valid_2;
    unsigned int tag_1;
    unsigned int tag_2;
    bool dirty_1;
    bool dirty_2;
    bool LRU;


public:
    cache_a() {valid_1 = 0;valid_2 = 0; tag_1 = 0;tag_2 = 0;dirty_1 = 0;dirty_2 = 0;LRU = 0; }
    ~cache_a() {}

    static int mem_write_cnt_a;
    static int miss_a;

    bool is_valid_1() {return valid_1;}
    bool is_valid_2() {return valid_2;}
    void set_valid_1() {if(valid_1==0) valid_1 = !valid_1; }
    void set_valid_2() {if(valid_2==0) valid_2 = !valid_2; }
    unsigned int get_tag_1() {return tag_1;}
    unsigned int get_tag_2() {return tag_2;}
    void set_tag_1(unsigned int tag_num) {tag_1 = tag_num;}
    void set_tag_2(unsigned int tag_num) {tag_2 = tag_num;}
    bool is_dirty_1() {return dirty_1;}
    bool is_dirty_2() {return dirty_2;}
    void set_dirty_1() {dirty_1 = !dirty_1;}
    void set_dirty_2() {dirty_2 = !dirty_2;}
    bool get_LRU() {return LRU;}
    void set_LRU() {LRU = !LRU;}


};

class address_chopper_a {

private:
    unsigned int tag;
    int index;
    int inst_type;

public:
    address_chopper_a() {}
    address_chopper_a(char* inst);
    int get_inst_type() {return inst_type;}
    int get_tag() {return tag;}
    int get_index() {return index;}

};


void associative_cache(char* inst, cache_a* cache);


#endif // ASSOCIATIVE_H_INCLUDED
