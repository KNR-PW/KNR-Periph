#pragma once
#include "Peripheral.hpp"
#include <Arduino.h>

class BLDC_PWM : public IPeripheral
{
    public:

        explicit BLDC_PWM(uint8_t pin,
                      uint16_t min_us = 1000,
                      uint16_t max_us = 2000,
                      uint16_t period_us = 20000,
                      uint8_t  res_bits = 12);

        void init() override;
        void update() override;

        void setMicroseconds(uint16_t us);

    private:
        uint8_t  _pin;
        uint16_t _min_us;
        uint16_t _max_us;
        uint16_t _period_us;
        uint8_t  _res_bits;
        uint16_t _current_us;

        // konwersja μs na duty cycle
        uint16_t toDuty(uint16_t us) const;
}