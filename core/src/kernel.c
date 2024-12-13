#include "multiboot.h"
#include "./global/globals.h"
#include "./util/util.h"
#include "./cursor/cursor.h"

struct multiboot_header multiboot __attribute__((section(".multiboot"))) = {
    MULTIBOOT_HEADER_MAGIC,
    MULTIBOOT_HEADER_FLAGS,
    MULTIBOOT_HEADER_CHECKSUM
};


void _start() {
    const char *str = "Welcome to riseros_";

    for (int i = 0; i < 11; i++) {  
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x0F; 
    }
    for(int i = 11; str[i] != '\0'; i++){
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x0C;
    }

    const char *riseros[5] = {
        "*****   ***  *****  *****  *****   ***   *****",
        "*    *   *   *      *      *    * *   *  *    ",
        "*****    *   ***    ****   *****  *   *  ***  ",
        "*   *    *      *   *      *   *  *   *     * ",
        "*    *  ***  *****  *****  *    *  ***   *****"
    };

    int row = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; riseros[i][j] != '\0'; j++) {
            video_memory[(row * 80 + j) * 2] = riseros[i][j];
            video_memory[(row * 80 + j) * 2 + 1] = 0x0C;  
        }
        row++;  
    }

    const char* contact = "Developed by Sumit Chauhan github.com/chauhansumitdev";
    for(int i = 0; (i < 80) && (i < 13); i++) {
        video_memory[(row*80+i)*2] = contact[i];
        video_memory[(row*80+i)*2+1] = 0x07;
    }
    for(int i = 13; contact[i] != '\0'; i++) {
        video_memory[(row*80+i)*2] = contact[i];
        video_memory[(row*80+i)*2+1] = 0x09;
    }
    row+=2;

    const char character = 0xDB;  
    int color = 0x0F;  
    for (int i = 0; i < 2; i++) {  
        for (int j = 0; j < 16; j++) {
            video_memory[(row * 80 + j) * 2] = character;  
            video_memory[(row * 80 + j) * 2 + 1] = color; 
            color = (color + 0x01) % 0x0F;  
        }
        row++;  
    }

    move_cursor(6, 54);

    time_delay(); // 5 sec delay -- obvisously system specific :(  temp -- to be rem.
    
    clear_screen();

    move_cursor(0,0);

    println("Error_generated ...");

    println("helllooooooooooooooooooooooooooooooooooooooooooo");
    
    println("riseros_");

    println(" :) :) :) :) :)");
}
