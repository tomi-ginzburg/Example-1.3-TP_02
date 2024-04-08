#include "mbed.h"
#include "arm_book_lib.h"

int main()
{
    // Cambio el codigo para utilizar c en lugar de c++

    gpio_t  gpio_d2, gpio_d3, gpio_b1, gpio_l1;

    gpio_init_in(&gpio_d2, D2); //DigitalIn gasDetector(D2);
    gpio_init_in(&gpio_d3, D3); //DigitalIn overTempDetector(D3);
    gpio_init_in(&gpio_b1, BUTTON1); //DigitalIn alarmOffButton(BUTTON1);
    gpio_init_out(&gpio_l1,LED1); //DigitalOut alarmLed(LED1);

    //gasDetector.mode(PullDown);
    core_util_critical_section_enter();
    gpio_mode(&gpio_d2, PullDown);
    core_util_critical_section_exit();
    
    //overTempDetector.mode(PullDown);
    core_util_critical_section_enter();
    gpio_mode(&gpio_d3, PullDown);
    core_util_critical_section_exit();

     gpio_write(&gpio_l1, OFF); //alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if (gpio_read(&gpio_d2) || gpio_read(&gpio_d3)){ //if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        gpio_write(&gpio_l1, alarmState); //alarmLed = alarmState;

        if (gpio_read(&gpio_b1)){ // )if ( alarmOffButton ) {
            alarmState = OFF;
        }
        
         printf("Gas: %d\n", gpio_read(&gpio_d2));
         printf("Temperatura: %d\n", gpio_read(&gpio_d3));
         printf("LED: %d\n", gpio_read(&gpio_l1));
    }
}