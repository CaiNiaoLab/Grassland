#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

static void led_Init(void);
static void hardware_Init(void);
static void led_Blink(void);

static void led_Init(void) {
    //< P1.0 Init
    GPIO_setAsOutputPin(
            GPIO_PORT_P1,
            GPIO_PIN0
            );
}

static void hardware_Init(void) {
    //< stop watchdog timer
    WDT_A_hold(WDT_A_BASE);
    led_Init();
}

static void led_Blink(void) {
    volatile uint32_t i;

    // Toggle P1.0 output
    GPIO_toggleOutputOnPin(
       GPIO_PORT_P1,
       GPIO_PIN0
       );

    // Delay
    for(i = 100000; i > 0; i--);
}

static void do_Something_One(void) {
    led_Blink();
}

static void do_Something_Two(void) {
    led_Blink();
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
