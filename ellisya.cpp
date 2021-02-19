#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

typedef  uint8_t oneByte;  //operator length or register length
typedef uint16_t twoByte;
typedef uint32_t fourByte;  //data cache length
typedef uint64_t eightByte; //length of a complete instruction

#define MEM_SIZE 65535
#define PAGE_SIZE 3

// VM's hardware
int       *memory = nullptr; //memory
eightByte *r = nullptr;      //registers

oneByte op = 0;
twoByte r1 = 0;
twoByte r2 = 0;
twoByte r3 = 0;
fourByte cache = 0;

//States
bool running = true;

void cycle() {
    switch (op) {
        case 0x00: //halt
            running = false;
            break;
        case 0x01: // load
            r[r1] = cache;
            break;
        case 0x02: // inc
            r[r1]++;
        case 0x03: //add
            r[r1]= r[r2] + r[r3];
            break;
        case 0x04: //read
            r[r1] = memory[r[r2]];
            break;
        case 0x05: //write
            memory[r[r2]]=r[r1];
            break;
        case 0x06: //print
          printf("Print: \n%08lx\n",r[r1]);
          break;
        default:
            perror("Operator invalid");
            exit(EXIT_FAILURE);
    }
}

int main() {
    memory    = (int*) calloc(MEM_SIZE, sizeof(int));
    r = (eightByte*)calloc(PAGE_SIZE, sizeof(eightByte));

    std::ifstream image("vm.image", std::ios::binary | std::ios::out);

    eightByte buffer = 0;

  while (running and image.read(reinterpret_cast<char *>(&buffer), sizeof(eightByte))){

            op = (buffer & 0xff);
            r1 = (buffer & 0x000000000000FF00) >> (8 * 1);
            r2 = (buffer & 0x0000000000FF0000) >> (8 * 2);
            r3 = (buffer & 0x00000000FF000000) >> (8 * 3);
            cache = (buffer & 0xFFFFFFFF00000000) >> (8 * 4);

            printf("   op= %02X\n", op);
            printf("   r1= %02X\n", r1);
            printf("   r2= %02X\n", r2);
            printf("   r3= %02X\n", r3);
            printf("cache= %08X\n", cache);

            printf("rgs  =%08lx,%08lx,%08lx \n",r[0x01],r[0x02],r[0x03]);

            cycle();
    }

    return 0;
}