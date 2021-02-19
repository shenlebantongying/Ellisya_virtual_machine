#include <cstdint>
#include <iostream>
#include <fstream>

#define MEM_SIZE 65535
#define W1(x) W<oneByte>(x,&out);
#define W4(x) W<fourByte>(x,&out);


typedef uint8_t  oneByte;   //operator length or register length
typedef uint32_t fourByte;  //data cache length
typedef uint32_t i32bits;
typedef uint64_t eightByte; //length of a complete instruction


template <class T>
void W(T bytecode,std::ofstream *x){
    x->write(reinterpret_cast<char*>(&bytecode),sizeof(T));

}


int main(){
    std::ofstream out("vm.image",std::ios::binary|std::ios::out);;

    oneByte  halt = 0x00;
    oneByte  load = 0x01;
    oneByte  inc  = 0x02;
    oneByte  add  = 0x03;
    oneByte  read = 0x04;
    oneByte  write= 0x05;
    oneByte  print= 0x06;

    oneByte  rg0  = 0x00;
    oneByte  rg1  = 0x01;
    oneByte  rg2  = 0x02;
    oneByte  rg3  = 0x03;

    // load cache to rg1
    W1(load)
    W1(rg1)
    W1(rg0)
    W1(rg0)
    W4(0x12ABCDEF)

    //print rg1
    W1(print)
    W1(rg1)
    W1(rg0)
    W1(rg0)
    W4(0x00)

    //halt
    W1(halt)
    W1(rg0)
    W1(rg0)
    W1(rg0)
    W4(0x00)

  out.close();

    return 0;
}


