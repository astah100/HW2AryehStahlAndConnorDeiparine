#include "cache.hh"
#include <iostream>
#include <cstring>
#include "fifo_evictor.hh"
#include "lru_evictor.hh"


void test1(Cache *c){
  Cache::val_type  string = "testVal1";
    key_type test = "testKey1";
    Cache::size_type size = strlen(string)+1;
    c->set(test, string, size);
    std::cout << c->space_used() << std::endl;
    c->set(test, string, size);
    c->set(test, string, size);
    std::cout << c->space_used() << std::endl;
    Cache::val_type got = c->get("testKey1", size);
    std::cout << got << std::endl;
    std::cout << c->space_used() << std::endl;
    std::cout << c->space_used() << std::endl;
}

void test2(Cache *c){
  std::cout << c->space_used() << std::endl;
  Cache::val_type  string1 = "1";
    key_type test1 = "testKey1";
    Cache::size_type size1 = strlen(string1)+1;
    c->set(test1, string1, size1);
    std::cout << c->space_used() << std::endl;
    Cache::val_type  string2 = "2";
    key_type test2 = "testKey2";
    Cache::size_type size2 = strlen(string2)+1;
    c->set(test2, string2, size2);
    std::cout << c->space_used() << std::endl;
    Cache::size_type size = 2;
    c->get("testKey1", size);
    std::cout << c->space_used() << std::endl;
    Cache::val_type  string3 = "3";
    key_type test3 = "testKey3";
    Cache::size_type size3 = strlen(string3)+1;
    c->set(test3, string3, size3);
    std::cout << c->space_used() << std::endl;
    Cache::val_type  string4 = "4";
    key_type test4 = "testKey4";
    Cache::size_type size4 = strlen(string4)+1;
    c->set(test4, string4, size4);
    std::cout << c->space_used() << std::endl;

    Cache::val_type  string5 = "5";
    key_type test5 = "testKey5";
    Cache::size_type size5 = strlen(string5)+1;
    c->set(test5, string5, size5);
    std::cout << c->space_used() << std::endl;

}

void testCustomHash(Cache *c){

       Cache::val_type  string = "1";
       key_type test= "x";
       Cache::size_type size = strlen(string)+1;
       c->set(test, string, size);
       Cache::val_type  string2 = "2";
       key_type test2 = "xx";
       Cache::size_type size2 = strlen(string2)+1;
       c->set(test2, string2, size2);
       Cache::val_type  string3 = "3";
       key_type test3 ="xxx";
       Cache::size_type size3 = strlen(string3)+1;
       c->set(test3, string3, size3);
       Cache::val_type  string4 = "4";
       key_type test4 ="xxxx";
       Cache::size_type size4 = strlen(string4)+1;
       c->set(test4, string4, size4);
   
  
}


int main() {
    FIFO* ev(new FIFO());
    Cache * c(new Cache(10, .75, ev));
    LRU* ev2(new LRU());
    Cache *c2(new Cache(6, .75, ev2));
    //testing with simple hash function based on length of string
    Cache::hash_func testFunc = [](key_type key){return key.length() % 10;};
    FIFO* ev3(new FIFO());
    Cache *c3(new Cache(6, .75, ev3, testFunc));
      
    test1(c);
    test2(c2);
    testCustomHash(c3);

    delete c;
    delete ev;
    delete c2;
    delete ev2;
    delete ev3;
    delete c3;
    return 1;
}
