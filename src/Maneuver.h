/*
 Name: 		Maneuver.h
 Created:	12/31/2019 9:07:52 PM
 Author:	John Bales
 Editor:	Notepad++, Arduino IDE
*/

#ifndef _Maneuver_h
#define _Maneuver_h

#include <Arduino.h>

struct Sensor {
  int Echo;
  int Trig;
};

struct Settings {
	int DriveA;
	int DriveB;
	int Motor1;
	int Motor2;
	int Motor3;
	int Motor4;
	bool Debug;
};

struct Distance {
	int Left;
	int Right;
	int Forward;
	int Backward;
};

class Maneuver {
public:
	Maneuver();
	Maneuver(int speed);
	void SetSpeed(int speed);
	void Configure(Settings setting);
	void Forward();
	void Backward();
	void Left();
	void Right();
	void Stop();
	void Turn(char direction, int radius);
	int GetDistance(Sensor sensor);
	void Scan(Sensor sensor);
	void SetDirection(Sensor sensor, Distance distance);

private:
	void printMsg(String msg);
	void printMsg(String msg, String pos);	
};

#endif