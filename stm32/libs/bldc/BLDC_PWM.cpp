#include "BLDC_PWM.hpp"

BLDC_PWM::BLDC_PWM(uint8_t pin,
                   uint16_t min_us,
                   uint16_t max_us,
                   uint16_t period_us,
                   uint8_t  res_bits)
  : _pin(pin)
  , _min_us(min_us)
  , _max_us(max_us)
  , _period_us(period_us)
  , _res_bits(res_bits)
  , _current_us(min_us)
{}

void BLDC_PWM::init() {
  // ustawienie częstotliwości i rozdzielczości PWM
  analogWriteFrequency(uint32_t(1e6) / _period_us);
  analogWriteResolution(_res_bits);

  pinMode(_pin, OUTPUT);

  // ARMING: minimalny sygnał
  setMicroseconds(_min_us);
  delay(2000);  // czekaj na ESC
}

void BLDC_PWM::update() {
  // nic do zrobienia – PWM jest ustawiany w setMicroseconds()
}

void BLDC_PWM::setMicroseconds(uint16_t us) {
  // klamrowanie wartości
  if (us < _min_us) us = _min_us;
  else if (us > _max_us) us = _max_us;

  _current_us = us;
  uint16_t duty = toDuty(us);
  analogWrite(_pin, duty);
}

uint16_t BLDC_PWM::toDuty(uint16_t us) const {
  float frac = float(us) / float(_period_us);
  return uint16_t(frac * ((1u << _res_bits) - 1));
}
