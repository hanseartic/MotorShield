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
	
	voltageMultiplicator = (5.0 / 1024.0);
	voltsPerAmp = 1.65;
}

bool MS_DCMotor::run(uint8_t cmds) {
	if (((FORWARD | BACKWARD) & cmds) == (FORWARD | BACKWARD)) {
		return false;
	}
	if (((BRAKE | RELEASE) & cmds) == (BRAKE | RELEASE)) {
		return false;
	}
	if ((cmds & FORWARD) == FORWARD) {
		digitalWrite(motordirection, HIGH);
		runstate = (runstate & (BRAKE | RELEASE)) | FORWARD;
	}
	if ((cmds & BACKWARD) == BACKWARD) {
		digitalWrite(motordirection, LOW);
		runstate = (runstate & (BRAKE | RELEASE)) | BACKWARD;
	}
	if ((cmds & RELEASE) == RELEASE) {
		digitalWrite(motorbrake, LOW);
		runstate = (runstate & (FORWARD | BACKWARD)) | RELEASE;
	}
	if ((cmds & BRAKE) == BRAKE) {
		digitalWrite(motorbrake, HIGH);
		runstate = (runstate & (FORWARD | BACKWARD)) | BRAKE;
	}
	return true;
}

void MS_DCMotor::setSpeed(uint8_t speed) {
	if (speed > 255) speed = 255;
	else if (speed < 0) speed = 0;
	analogWrite(motorspeed, speed);
}

uint8_t MS_DCMotor::getState(void) {
	return runstate & (BRAKE | RELEASE);
}

uint8_t MS_DCMotor::getDirection(void) {
	return runstate & (FORWARD | BACKWARD);
}

float MS_DCMotor::getCurrentAmps(void) {
	readCurrentSensor();
	return currentAmps;
}

float MS_DCMotor::getCurrentVoltage(void) {
	readCurrentSensor();
	return currentVolts;
}

void MS_DCMotor::readCurrentSensor(void) {
	float currentRawSensor = analogRead(motorsensor);
	currentVolts = voltageMultiplicator * currentRawSensor;
	currentAmps = currentVolts / voltsPerAmp;
}
