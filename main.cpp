#include "stm32f103c8t6.h"
#include <mbed.h>
#include "Crawler.h"
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>

#define ENC1_A PB_12
#define ENC1_B PB_13

DigitalOut led(LED1);
AnalogIn battery(PA_0);


Crawler cr_left(Crawler::Type::LEFT);
Crawler cr_right(Crawler::Type::RIGHT);

ros::NodeHandle nh;
std_msgs::Int16 encoder_left_msg;
std_msgs::Int16 encoder_right_msg;
ros::Publisher pub_encoder_left("encoder_left", &encoder_left_msg);
ros::Publisher pub_encoder_right("encoder_right", &encoder_right_msg);

void velocity_left_cb(const std_msgs::Float32& msg) {
	cr_left.set_velocity(msg.data);
}

void velocity_right_cb(const std_msgs::Float32& msg) {
	cr_right.set_velocity(msg.data);
}

ros::Subscriber<std_msgs::Float32> sub_vel_left("cmd_vel_left", &velocity_left_cb);
ros::Subscriber<std_msgs::Float32> sub_vel_right("cmd_vel_right", &velocity_right_cb);

void wait_for_battery() {
	float battery_status;
	do {
		battery_status = battery.read();
		wait_ms(1000);
	} while(battery_status < 0.33);
	wait_ms(1000);

}

int main() {
	// setup begin
	confSysClock();
	wait_for_battery();
	cr_left.set_velocity(0);
	cr_right.set_velocity(0);
	nh.initNode();
	nh.subscribe(sub_vel_left);
	nh.subscribe(sub_vel_right);
	led = 0;
	nh.advertise(pub_encoder_left);
	nh.advertise(pub_encoder_right);
	// setup end

	while (true) {
		encoder_left_msg.data= cr_left.getMotor()->getEncoder().get_pulses();
		encoder_right_msg.data = cr_right.getMotor()->getEncoder().get_pulses();
		pub_encoder_left.publish(&encoder_left_msg);
		pub_encoder_right.publish(&encoder_right_msg);

	
		wait_ms(10);
		nh.spinOnce();
	}

}
