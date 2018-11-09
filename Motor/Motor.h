#ifndef MOTOR_H
#define MOTOR_H
#include <mbed.h>
#include "Encoder.h"
#define MIN_PWM 0.03
#define PULSES_PER_REVOLUTION 75
#define WHEEL_SIZE 1
#define PI 3.1415926
#define GEAR_RATIO 1

class Motor {
public:
	Motor(PinName ma, PinName mb, PinName encA, PinName encB);
	void setPWM(float velocity);
	float get_rev_per_sec();
	Encoder & getEncoder();
	void compute_velocity();
private:
	Encoder _encoder;
    Timer _velocity_timer;
	PwmOut _mb;
	PwmOut _ma;
	int _last_count;
	float _velocity;
};


#endif
