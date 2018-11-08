#include "Encoder.h"
//Serial pc1(PA_9, PA_10);
Encoder::Encoder(PinName irp_a, PinName irp_b) : _irp_a(irp_a), _irp_b(irp_b) {
//	pc1.baud(57600);
//	pc1.printf("encoder()");
//	t.start();
	_irp_a.rise(this, &Encoder::rise);
	_irp_a.fall(this, &Encoder::fall);
	_counter = 0;
}

bool Encoder::is_idle() {
	return t.read() >= 0.5;
}

int Encoder::get_pulses() {
	return _counter;
}

void Encoder::reset() {
//	t.reset();
	_counter = 0;
}

float Encoder::get_pulse_per_sec() {
	if(_time_between_pulse == 0) return 0;
	return 1/_time_between_pulse;
}

void Encoder::rise() {
//	pc1.printf("rise");
	if(_irp_a.read() ^ _irp_b) {
		_counter--;
//		_time_between_pulse = -t.read();
//		t.reset();
	}
}

void Encoder::fall() {
	if(!(_irp_a.read() ^ _irp_b)) {
		_counter++;
//		_time_between_pulse = t.read();
//		t.reset();
	}
}
