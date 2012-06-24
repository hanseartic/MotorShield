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
#define MOTOR_A_SENSOR A0

#define MOTOR_B 11
#define MOTOR_B_DIRECTION 13
#define MOTOR_B_BRAKE 8
#define MOTOR_B_SENSOR A1

#define FORWARD 1
#define BACKWARD 2
#define BRAKE 4
#define RELEASE 8

class MS_DCMotor {
public:
	MS_DCMotor(uint8_t motornum);
	bool run(uint8_t);
	void setSpeed(uint8_t);
	uint8_t getState(void);
	uint8_t getDirection(void);
	float getCurrentAmps(void);
	float getCurrentVoltage(void);
	
private:
	void readCurrentSensor(void);
	float currentVolts, currentAmps, voltageMultiplicator, voltsPerAmp;
	uint8_t motorspeed, motorbrake, motordirection, motorsensor, runstate;
};

#endif
