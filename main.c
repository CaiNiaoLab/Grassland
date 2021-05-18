#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

void hardware_Init(void) {
    //< stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
}

void dummy (void) {
}

void do_Something_One(void) {
    dummy();
}

void do_Something_Two(void) {
    dummy();
}
int main(void)
{
    //< hardware init
    hardware_Init();

    while(1) {
        //< 处理事件1
        do_Something_One();

        //< 处理事件2
        do_Something_Two();
    }
}
