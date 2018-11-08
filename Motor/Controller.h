#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <mbed.h>
#include "Crawler.h"
#define SAMPLE_PERIOD 0.01f

Serial pc1(USBTX, USBRX);
struct PID_consts {
	float KP;
	float KI;
	float KD;
	PID_consts(float kp, float ki, float kd) {
		KP = kp;
		KI = ki;
		KD = kd;
	}
};

class Controller {
public:
	Controller(PID_consts left_consts, PID_consts right_consts) : _left_consts(left_consts), _right_consts(right_consts), _left_Crawler(Crawler::Type::LEFT), _right_Crawler(Crawler::Type::RIGHT) {
		pc1.baud(57600);
		left_current_velocity = 0;
		right_current_velocity = 0;
		_error_acc_left = 0;
		_error_acc_right = 0;
		_last_error_left = 0;
		_last_error_right = 0;
		set_left_target_velocity(0);
		set_right_target_velocity(0);
		ticker.attach(callback(this, &Controller::compute), SAMPLE_PERIOD);
	}
	
	void set_left_target_velocity(float velocity) {
		_left_target_velocity = velocity;
	}
	void set_right_target_velocity(float velocity) {
		_right_target_velocity = velocity;
	}
	
	Crawler & get_left_crawler() {
		return this->_left_Crawler;
	}
	
	Crawler & get_right_crawler() {
		return this->_right_Crawler;
	}
	
	float get_left_current_velocity() {
		return left_current_velocity;
	}

	float get_right_current_velocity() {
		return right_current_velocity;
	}
private:
	void compute() {
		
		if(_left_Crawler.getMotor()->getEncoder().is_idle()) {
			left_current_velocity = 0;
			_left_Crawler.getMotor()->getEncoder().reset();
		} else {
			left_current_velocity = _left_Crawler.get_cm_per_sec();
		}
		
		float error_left_velocity = _left_target_velocity - left_current_velocity;
	
//		pc1.printf("%f ", error_left_velocity);	
		float error_left_deriv = error_left_velocity - _last_error_left;


		_last_error_left = error_left_velocity;


		float power_left = error_left_velocity * _left_consts.KP + _error_acc_left * _left_consts.KI + error_left_deriv * _left_consts.KD;
		
		_error_acc_left += error_left_velocity;

//		pc1.printf("%0.2f ", left_current_velocity);

		if(power_left > 1000) {
			power_left = 1000;
		}

		if(power_left < -1000) {
			power_left = -1000;
		}


		_left_Crawler.getMotor()->setPWM(power_left);
	}
	
	Ticker ticker;
	PID_consts _left_consts;
	PID_consts _right_consts;
	Crawler _left_Crawler;
	Crawler _right_Crawler;
	float left_current_velocity;
	float right_current_velocity;
	float _left_target_velocity;
	float _right_target_velocity;
	float _error_acc_left;
	float _error_acc_right;
	float _last_error_left;
	float _last_error_right;	
};

#endif
