#include <keyboard_driver.h>
#include <keyboard.h>
#include <stdint.h>
#include <interrupts.h>


void keyboard_handler(uint64_t rsp){
    





}




char getChar(){
 	char c=0;

    _hlt();

    memset(&c, 0, 1);

    return c;

}
