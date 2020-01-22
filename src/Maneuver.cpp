/*
 Name:		Maneuver.cpp
 Created:	12/31/2019 9:07:52 PM
 Author:	John Bales
 Editor:	Notepad++, Arduino IDE
*/

#include <Maneuver.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 10, 4, 3, 2);

const String SPEED_MSG = "Speed not set";
const String CONFIG_MSG = "PIN Configuration not set.";
const String DIST_MSG = "Distance: ";
const String TOP = "top";
const String BTM = "bottom";

int _driveA, _driveB, _motor1, _motor2, _motor3, _motor4, _speed, _turnSpeed;
bool _debug = false;
bool _isConfigured = false;

Maneuver::Maneuver() {	
}

Maneuver::Maneuver(int speed){
	SetSpeed(speed);	
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
	
	_isConfigured = true;
}

void Maneuver::SetSpeed(int speed){
	if(speed > 0){
		_speed = speed;
		_turnSpeed = speed / 2;
	}else{
		printMsg("Speed not set");
	}
}

void Maneuver::Forward() {
	String msg = "";
	
	if(_isConfigured){
		if(_speed > 0){
			analogWrite(_driveA, _speed);
			analogWrite(_driveB, _speed);
			
			digitalWrite(_motor1, HIGH);
			digitalWrite(_motor2, LOW);
			digitalWrite(_motor3, LOW);
			digitalWrite(_motor4, HIGH);
			
			msg = "Moving Forward";
		}else {
			msg = SPEED_MSG;
		}	
	} else{
		msg = CONFIG_MSG;
	}

	printMsg(msg);		
}

void Maneuver::Backward() {
	String msg = "";
	
	if(_isConfigured) {
		if(_speed > 0){
			analogWrite(_driveA, _speed);
			analogWrite(_driveB, _speed);
			
			digitalWrite(_motor1, LOW);
			digitalWrite(_motor2, HIGH);
			digitalWrite(_motor3, HIGH);
			digitalWrite(_motor4, LOW);	
			
			msg = "Moving Backward";
		}else {
			msg = SPEED_MSG;
		}		
	}else {
		msg = CONFIG_MSG;
	}

	printMsg(msg);	
}

void Maneuver::Left() {
	String msg = "";
	
	if(_isConfigured) {
		if(_turnSpeed > 0){
			analogWrite(_driveA, _speed);
			analogWrite(_driveB, _speed);
			
			digitalWrite(_motor1, LOW);
			digitalWrite(_motor2, HIGH);
			digitalWrite(_motor3, LOW);
			digitalWrite(_motor4, HIGH);
			
			msg = "Moving Left";
		}else{
			msg = SPEED_MSG;
		}
	} else {
		msg = CONFIG_MSG;
	}		

	printMsg(msg);	
}

void Maneuver::Right() {
	String msg = "";
	
	if(_isConfigured) {
		if(_turnSpeed > 0) {
			analogWrite(_driveA, _speed);
			analogWrite(_driveB, _speed);

			digitalWrite(_motor1, HIGH);
			digitalWrite(_motor2, LOW);
			digitalWrite(_motor3, HIGH);
			digitalWrite(_motor4, LOW);	
			
			msg = "Moving Right";
		} else {
			msg = SPEED_MSG;
		}
	}else {
		msg = CONFIG_MSG;
	}
	
	printMsg(msg);
}

void Maneuver::Stop() {
	String msg = "";
	
	if(_isConfigured){
		digitalWrite(_driveA, LOW);
		digitalWrite(_driveB, LOW);
		
		msg = "Stop!";
	}else {
		msg = CONFIG_MSG;
	}

	printMsg(msg);	
}

void Maneuver::Turn(char direction, int radius) {
	switch (direction) 
	{
		case 'L': Left(); break;
		case 'R': Right(); break;
	}

	switch (radius) 
	{
		case 90: delay(300); break;
		case 180: delay(600); break;
		case 360: delay(1600); break;
	}

	Stop();
}

int Maneuver::GetDistance(Sensor sensor) {
	if(_isConfigured){
		digitalWrite(sensor.Trig, LOW);   
		delayMicroseconds(2);
		
		digitalWrite(sensor.Trig, HIGH);  
		delayMicroseconds(20);
		
		digitalWrite(sensor.Trig, LOW);   
		float Fdistance = pulseIn(sensor.Echo, HIGH);  
		Fdistance = Fdistance / 58;
		
		//printMsg(DIST_MSG + (String)Fdistance, BTM);
		
		return (int)Fdistance;
	} else {
		
		printMsg(CONFIG_MSG);			
		Serial.println(CONFIG_MSG);
		
		return 0;
	}
}

void Maneuver::Scan(Sensor sensor){
	Distance distance;
	
	delay(500);

	Turn('L',90);
	delay(500);
	distance.Left = GetDistance(sensor);
	printMsg(DIST_MSG + (String)distance.Left, BTM);	
	delay(500);

	Turn('R',180);
	delay(500);
	distance.Right = GetDistance(sensor);
	printMsg(DIST_MSG + (String)distance.Right, BTM);
	delay(500);

	Turn('L',90);
	delay(500);
	distance.Forward = GetDistance(sensor);
	printMsg(DIST_MSG + (String)distance.Forward, BTM);
	delay(500);

	SetDirection(sensor, distance);
} 

void Maneuver::SetDirection(Sensor sensor, Distance distance){
	if((distance.Right <= 50) && (distance.Left <= 50) && (distance.Forward <= 50)){
		Backward();
		Scan(sensor);
	}else if((distance.Left >= 50) && (distance.Left > distance.Right)){
		Turn('L',90);
	}else if ((distance.Right >= 50) && (distance.Right > distance.Left)){
		Turn('R', 90);
	}else if((distance.Forward >= 50) && ((distance.Forward > distance.Left) && (distance.Forward > distance.Right))) {
		Forward();
	}else {
		// write a function to randomly determine a direction here
		Turn('L',90);
	}
}

void Maneuver::printMsg(String msg){
	printMsg(msg, "");
}

void Maneuver::printMsg(String msg, String pos){
	if (_debug){
		lcd.begin(16, 2);

		if(pos == TOP){
			lcd.setCursor(0, 0);
		}else if(pos == BTM) {
			lcd.setCursor(0, 1);
		}else{
			lcd.home();
		}	

		lcd.print(msg);
	
		Serial.println(msg);		
	}
}