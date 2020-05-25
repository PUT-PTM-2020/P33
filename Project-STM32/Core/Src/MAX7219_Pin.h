#ifndef MAX7219_MAX7219_PIN_H
#define MAX7219_MAX7219_PIN_H

#include "stm32f4xx_hal.h"

class MAX7219_Pin {

public:

    GPIO_TypeDef *port;
    uint32_t pin;

    void high() {
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    }

    void low() {
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    }

};

#endif //MAX7219_MAX7219_PIN_H
