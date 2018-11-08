#include "Motor.h"
#include <mbed.h>
DigitalOut ledt(LED1);
Motor::Motor(PinName ma, PinName mb, PinName encA, PinName encB) :_encoder(encA, encB),  _ma(ma), _mb(mb) {
	_ma.period(0.001);
	_mb.period(0.001);
	_ma.write(0.0);
	_mb.write(0.0);
	_velocity = 0;
	_last_count = 0;
}

void Motor::setPWM(float velocity) {
	ledt = !ledt;
	velocity = (velocity - (-1000)) * (0.97 - (-0.97)) / (1000 - (-1000)) + -0.97;
	if(abs(velocity) < 0.03) {
		_ma.write(0.0);
		_mb.write(0.0);
	} else if (velocity > 0) {
		_ma.write(velocity);
		_mb.write(MIN_PWM);
	} else {
		_ma.write(MIN_PWM);
		_mb.write(-velocity);
	}
}

Encoder & Motor::getEncoder() {
	return this->_encoder;
}

float Motor::get_rev_per_sec() {
//	int current_count = _encoder.get_pulses();
//	_velocity = ((current_count - _last_count) / PULSES_PER_REVOLUTION)*0.1 + _velocity*0.9;
//	_last_count = current_count;
//	return _velocity;
	return _encoder.get_pulse_per_sec() / PULSES_PER_REVOLUTION;
}

