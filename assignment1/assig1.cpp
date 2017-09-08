#include "mbed.h"

DigitalOut ledon(PB_9);
DigitalOut myled(LED1);

int main() {
    while(1) {
        
        ledon = 1; // LED is ON
        wait(0.2); // 200 ms
        ledon = 0;
         // LED is OFF
        wait(1.0); // 1 sec
    }
}
