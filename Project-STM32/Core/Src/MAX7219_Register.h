#ifndef MAX7219_MAX7219_REGISTER_H
#define MAX7219_MAX7219_REGISTER_H

enum class MAX7219_Register {

    Noop = 0x00,
    Digit0, Digit1, Digit2, Digit3, Digit4, Digit5, Digit6, Digit7,
    DecodeMode,
    Intensity,
    ScanLimit,
    Shutdown,
    DisplayTest = 0x0F

};

#endif //MAX7219_MAX7219_REGISTER_H
