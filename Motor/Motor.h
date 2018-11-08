#ifndef MOTOR_H
#define MOTOR_H
#include <mbed.h>
#include "Encoder.h"
#define MIN_PWM 0.03
#define PULSES_PER_REVOLUTION 75

class Motor {
public:
	Motor(PinName ma, PinName mb, PinName encA, PinName encB);
	void setPWM(float velocity);
	float get_rev_per_sec();
	Encoder & getEncoder();
private:
	Encoder _encoder;
	PwmOut _mb;
	PwmOut _ma;
	int _last_count;
	float _velocity;
};


#endif
