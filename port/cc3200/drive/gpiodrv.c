/*
 * gpio_option.c
 *
 *  Created on: 2021年8月2日
 *      Author: ZhaoSQ
 */
#include <stdbool.h>
#include <gpiodrv.h>

#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"

extern const GPIO_Config GPIO_config[];
extern const uint_least8_t g_GPIOCount;

static void GPIO_Drvice_Init(GPIO_Handle handle);
static GPIO_Handle GPIO_Drvice_Open(GPIO_Handle handle);
static GPIO_Handle GPIO_Drvice_Close(GPIO_Handle handle);

const GPIO_FxnTable GPIODrvice_fxnTable =
{
     GPIO_Drvice_Init,
     GPIO_Drvice_Open,
     GPIO_Drvice_Close,
};

static void getToPin(uint64_t pin, uint64_t *gpiopin) {
    //< 从外部引脚号获取GPIO引脚编号
    *gpiopin  = 1 << (pin % 8);
}

static void gpiodrvTryToPeripheralClkRestart() {
    //< 使能 端口A1外设时钟
    PRCMPeripheralClkEnable(PRCM_GPIOA1,PRCM_RUN_MODE_CLK);
}

static void GPIO_Drvice_Init(GPIO_Handle handle) {
    GPIOMCU_HWAttrs const   *hwAttrs = handle->hwAttrs;
    GPIO_Object             *object = handle->object;
    uint_fast8_t i;

    gpiodrvTryToPeripheralClkRestart();
    for( i = 0; i < g_GPIOCount; i++) {
        getToPin(hwAttrs[i].pin_num,&object[i].pin_address);
        PinTypeGPIO(hwAttrs[i].init_pin, object[i].pin_mode, false);
        //< 配置GPIO 11为输出模式
        GPIODirModeSet(hwAttrs[i].base_port , object[i].pin_address , object[i].dircetion);
    }

}

static GPIO_Handle GPIO_Drvice_Open(GPIO_Handle handle) {
    GPIOMCU_HWAttrs const   *hwAttrs = handle->hwAttrs;
    GPIO_Object             *object = handle->object;
    uint8_t gpio_value = 1 << (hwAttrs->pin_num % 8);
    GPIOPinWrite(hwAttrs->base_port, object->pin_address, gpio_value);
    return (handle);
}

static GPIO_Handle GPIO_Drvice_Close(GPIO_Handle handle) {
    GPIOMCU_HWAttrs const   *hwAttrs = handle->hwAttrs;
    GPIO_Object             *object = handle->object;
    uint8_t gpio_value = 0 << (hwAttrs->pin_num % 8);
    GPIOPinWrite(hwAttrs->base_port, object->pin_address, gpio_value);
    return (handle);
}
