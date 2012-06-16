// Arduino Motorshield Rev. 3 Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include <avr/io.h>
#include "WProgram.h"
#endif
#include "MotorShield.h"

MS_DCMotor::MS_DCMotor(uint8_t num) {
	switch (num) {
		case 1:
		case MOTOR_A:
			motorspeed =     MOTOR_A;
			motorbrake =     MOTOR_A_BRAKE;
			motordirection = MOTOR_A_DIRECTION;
			motorsensor =    MOTOR_A_SENSOR;
			break;
		case 2:
		case MOTOR_B:
			motorspeed =     MOTOR_B;
			motorbrake =     MOTOR_B_BRAKE;
			motordirection = MOTOR_B_DIRECTION;
			motorsensor =    MOTOR_B_SENSOR;
			break;
		default:
			return;
	}
	pinMode(motorspeed, OUTPUT);     //Initializes motor's channel speed pin
	pinMode(motorbrake, OUTPUT);     //Initializes motor's channel brake pin
	pinMode(motordirection, OUTPUT); //Initializes motor's channel direction pin
	pinMode(motorsensor, INPUT);     //Initializes motor's channel current-sensing pin
}

void MS_DCMotor::run(uint8_t cmd) {
	switch (cmd) {
		case RELEASE:
			digitalWrite(motorbrake, LOW);
			break;
		case BRAKE:
			digitalWrite(motorbrake, HIGH);
			break;
		case FORWARD:
			digitalWrite(motordirection, HIGH);
			break;
		case BACKWARD:
			digitalWrite(motordirection, LOW);
			break;
		default:
			return;
	}
}

void MS_DCMotor::setSpeed(uint8_t speed) {
	if (speed > 255) speed = 255;
	else if (speed < 0) speed = 0;
	analogWrite(motorspeed, speed);
}

uint8_t MS_DCMotor::getCurrentSensing(void) {
	return analogRead(motorsensor);
}
