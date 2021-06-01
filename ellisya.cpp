#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

typedef  uint8_t oneByte;  //operator length or register length
typedef uint16_t twoByte;
typedef uint32_t fourByte;  //data Data length
typedef uint64_t eightByte; //length of a complete instruction

#define MEM_SIZE 65535
#define PAGE_SIZE 3

// VM's hardware
int       *memory = nullptr; //memory
eightByte *Cache = nullptr;      //registers

oneByte op = 0;
twoByte r1 = 0;
twoByte r2 = 0;
twoByte r3 = 0;
fourByte Data = 0;

//States
bool running = true;

void cycle() {
    switch (op) {
        case 0x00: //halt
            running = false;
            break;
        case 0x01: // load
            Cache[r1] = Data;
            break;
        case 0x02: // inc
            Cache[r1]++;
        case 0x03: //add
            Cache[r1]= Cache[r2] + Cache[r3];
            break;
        case 0x04: //read
            Cache[r1] = memory[Cache[r2]];
            break;
        case 0x05: //write
            memory[Cache[r2]]=Cache[r1];
            break;
        case 0x06: //print
          printf("[Print]: %08lx\n", Cache[r1]);
          break;
        default:
            perror("Operator invalid");
            exit(EXIT_FAILURE);
    }
}

int main() {
    memory    = (int*) calloc(MEM_SIZE, sizeof(int));
    Cache = (eightByte*)calloc(PAGE_SIZE, sizeof(eightByte));

    std::ifstream image("vm.image", std::ios::binary | std::ios::out);

    eightByte buffer = 0;

  while (running and image.read(reinterpret_cast<char *>(&buffer), sizeof(eightByte))){

            op = (buffer & 0xff);
            r1 = (buffer & 0x000000000000FF00) >> (8 * 1);
            r2 = (buffer & 0x0000000000FF0000) >> (8 * 2);
            r3 = (buffer & 0x00000000FF000000) >> (8 * 3);
      Data = (buffer & 0xFFFFFFFF00000000) >> (8 * 4);

            printf("===============\n");
            printf("   op = %02X\n", op);
            printf("   r1 = %02X\n", r1);
            printf("   r2 = %02X\n", r2);
            printf("   r3 = %02X\n", r3);
            printf("Data = %08X\n", Data);

            printf("  rgs =%08lx,%08lx,%08lx \n", Cache[0x01], Cache[0x02], Cache[0x03]);

            cycle();
    }

    return 0;
}