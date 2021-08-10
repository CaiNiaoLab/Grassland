/*
 * gpio_option.h
 *
 *  Created on: 2021年4月28日
 *      Author: DELL
 */

#ifndef GPIODRV_H_
#define GPIODRV_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct GPIO_Config_ *GPIO_Handle;

/**
 *  \def    MCU_GPIOName
 *  \brief  Enum of GPIOs on the MCU dev board
 */
typedef enum GPIO_Name {
    kREDLED = 0,
    //kGRELED,
    kMCU_COUNT
} GPIO_Name;

typedef enum {
    kClose,
    kOpen
} GPIO_Status;

typedef enum {
    kGPIOWrite,
    kGPIORead
} GPIO_Dircetion;

/*
 * < 指向GPIO_init()驱动程序特定实现的函数指针
 */
typedef void (*GPIO_InitFxn)(GPIO_Handle handle);

typedef GPIO_Handle (*GPIO_OpenFxn) (GPIO_Handle handle);
typedef GPIO_Handle (*GPIO_CloseFxn)(GPIO_Handle handle);

typedef struct GPIOMCU_HWAttrs {
    uint64_t base_port;
    uint64_t pin_num;
    uint64_t init_pin;
} GPIOMCU_HWAttrs;

typedef struct {
    GPIO_Status gpioStatus;
    uint64_t dircetion;
    uint64_t pin_mode;
    uint64_t pin_address;
} GPIO_Object;

/*
 * < GPIO函数表的定义，其中包含控制特定 GPIO 驱动实现所需的一组函数。
 */
typedef struct {
    GPIO_InitFxn initFxn;
    GPIO_OpenFxn openFxn;
    GPIO_CloseFxn closeFxn;
} GPIO_FxnTable;

/*
 * < GPIO_Config 结构包含一组用于表征 GPIO 驱动器实现的指针。
 */
typedef struct GPIO_Config_ {
    GPIO_FxnTable const *fxnTablePtr;
    void                *object;
    void          const *hwAttrs;
}GPIO_Config;

extern const GPIO_FxnTable GPIODrvice_fxnTable;

#endif /* GPIODRV_H_ */
