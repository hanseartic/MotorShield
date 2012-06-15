// Arduino Motorshield Rev. 3 Library
// based on the Adafruit Motor shield library
// this code is also public domain, enjoy!

#ifndef _MotorShield_h_
#define _MotorShield_h_

#include <inttypes.h>
#include <avr/io.h>

//#define MOTORDEBUG 1

#define MICROSTEPS 16         // 8 or 16

#define MOTOR12_64KHZ _BV(CS20)  // no prescale
#define MOTOR12_8KHZ _BV(CS21)   // divide by 8
#define MOTOR12_2KHZ _BV(CS21) | _BV(CS20) // divide by 32
#define MOTOR12_1KHZ _BV(CS22)  // divide by 64

#define MOTOR34_64KHZ _BV(CS00)  // no prescale
#define MOTOR34_8KHZ _BV(CS01)   // divide by 8
#define MOTOR34_1KHZ _BV(CS01) | _BV(CS00)  // divide by 64

#define MOTOR_A 3
#define MOTOR_A_DIRECTION 12
#define MOTOR_A_BRAKE 9
#define MOTOR_A_SENSOR 0

#define MOTOR_B 11
#define MOTOR_B_DIRECTION 13
#define MOTOR_B_BRAKE 8
#define MOTOR_B_SENSOR 1

#define FORWARD HIGH
#define BACKWARD LOW
#define BRAKE HIGH
#define RELEASE LOW

class MSMotorController
{
  public:
    MSMotorController(void);
    void enable(void);
    friend class MS_DCMotor;
};

class MS_DCMotor
{
 public:
  AF_DCMotor(uint8_t motornum);
  void run(uint8_t);
  void setSpeed(uint8_t);

 private:
  uint8_t motornum, pwmfreq;
};

#endif
