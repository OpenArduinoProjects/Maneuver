/*
 Name:		Maneuver.cpp
 Created:	12/31/2019 9:07:52 PM
 Author:	John Bales
 Editor:	Notepad++, Arduino IDE
*/

#include "Maneuver.h"
#include "Arduino.h"

Maneuver::Maneuver() {
	_speed = 250;
}

void Maneuver::Configure(Settings setting){
	_driveA = setting.DriveA;
	_driveB = setting.DriveB;

	_motor1 = setting.Motor1;
	_motor2 = setting.Motor2;
	_motor3 = setting.Motor3;
	_motor4 = setting.Motor4;
	
	_debug = setting.Debug;
	
	pinMode(_motor1, OUTPUT);
	pinMode(_motor2, OUTPUT);
	pinMode(_motor3, OUTPUT);
	pinMode(_motor4, OUTPUT);
	pinMode(_driveA, OUTPUT);
	pinMode(_driveB, OUTPUT);
}

void Maneuver::Forward() {
	analogWrite(_driveA, _speed);
	analogWrite(_driveB, _speed);
	digitalWrite(_motor1, HIGH);
	digitalWrite(_motor2, LOW);
	digitalWrite(_motor3, LOW);
	digitalWrite(_motor4, HIGH);

	if (_debug) {
		Serial.println("Forward");
	}	
}

void Maneuver::Reverse() {
	analogWrite(_driveA, _speed);
	analogWrite(_driveB, _speed);
	digitalWrite(_motor1, LOW);
	digitalWrite(_motor2, HIGH);
	digitalWrite(_motor3, HIGH);
	digitalWrite(_motor4, LOW);

	if (_debug) {
		Serial.println("Back");
	}	
}

void Maneuver::Left() {
	analogWrite(_driveA, _speed);
	analogWrite(_driveB, _speed);
	digitalWrite(_motor1, LOW);
	digitalWrite(_motor2, HIGH);
	digitalWrite(_motor3, LOW);
	digitalWrite(_motor4, HIGH);

	if (_debug) {
		Serial.println("Left");
	}	
}

void Maneuver::Right() {
	analogWrite(_driveA, _speed);
	analogWrite(_driveB, _speed);
	digitalWrite(_motor1, HIGH);
	digitalWrite(_motor2, LOW);
	digitalWrite(_motor3, HIGH);
	digitalWrite(_motor4, LOW);

	if (_debug) {
		Serial.println("Right");
	}	
}

void Maneuver::Stop() {
	digitalWrite(_driveA, LOW);
	digitalWrite(_driveB, LOW);

	if (_debug) {
		Serial.println("Stop!");
	}	
}

void Maneuver::Turn(char direction, int radius) {
	switch (direction) 
	{
		case 'L': Left(); break;
		case 'R': Right(); break;
	}

	switch (radius) 
	{
		case 90: delay(400); break;
		case 180: delay(800); break;
		case 360: delay(1600); break;
	}

	Stop();
}

int Maneuver::Distance(Sensor sensor) {
  digitalWrite(sensor.Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(sensor.Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(sensor.Trig, LOW);   
  float Fdistance = pulseIn(sensor.Echo, HIGH);  
  Fdistance = Fdistance / 58;
  
  return (int)Fdistance;
} 