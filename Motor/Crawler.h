#ifndef CRAWLER_H
#define CRAWLER_H
#include <mbed.h>
#include "Motor.h"

#define M1A PA_15//PE_6
#define M2A PB_5//PF_9
#define E1A PB_12//PF_15//PD_7
#define E2A PB_13//PE_3

#define M1B PB_3//PE_5
#define M2B PB_4//PA_0
#define E1B PB_14//PF_13//PC_14
#define E2B PB_15//PF_14

#define PI 3.1415926f
#define CM_PER_REV 13.9523f
Serial pcC(USBTX, USBRX);
class Crawler {
public:
	typedef enum Type{
		LEFT,
		RIGHT
	};

	Crawler(Type type) : _type(type) {
		initMotor();
	}

	float get_cm_per_sec() {
		return this->_motor->get_rev_per_sec() * CM_PER_REV;
	}
	Motor * getMotor() {
		return this->_motor;
	}
	void set_velocity(int velocity) {
		this->_motor->setPWM((float) velocity);
	}
	
private:
	void initMotor() {
		if(_type == Crawler::Type::LEFT) {
			_motor = new Motor(M1A, M2A, E1A, E2A);	
		} else {
			_motor = new Motor(M1B, M2B, E1B, E2B);
		}
	}

	Crawler::Type _type;
	Motor * _motor;
};

#endif

