#ifndef ENCODER_H
#define ENCODER_H
#include "mbed.h"

class Encoder {
public:
  Encoder(PinName irp_a, PinName irp_b);
  int get_pulses();
  float get_pulse_per_sec();
  void reset();
  bool is_idle();
private:
  void rise();
  void fall();
  int _counter;
  float _time_between_pulse;
  InterruptIn _irp_a;
  DigitalIn _irp_b;
  Timer t;
};

#endif
