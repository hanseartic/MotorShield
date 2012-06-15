// Arduino Motorshield Rev. 3 Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#ifndef _MotorShield_h_
#define _MotorShield_h_

#include <inttypes.h>
#include <avr/io.h>

#define MOTOR_A 3
#define MOTOR_A_DIRECTION 12
#define MOTOR_A_BRAKE 9
#define MOTOR_A_SENSOR 0

#define MOTOR_B 11
#define MOTOR_B_DIRECTION 13
#define MOTOR_B_BRAKE 8
#define MOTOR_B_SENSOR 1

#define FORWARD 0
#define BACKWARD 2
#define BRAKE 4
#define RELEASE 8

class MS_DCMotor {
public:
	MS_DCMotor(uint8_t motornum);
	void run(uint8_t);
	void setSpeed(uint8_t);
	
private:
	uint8_t motorspeed, motorbrake, motordirection, motorsensor;
};

#endif
