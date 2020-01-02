/*
 Name: 		Maneuver.h
 Created:	12/31/2019 9:07:52 PM
 Author:	John Bales
 Editor:	Notepad++, Arduino IDE
*/

#ifndef _Maneuver_h
#define _Maneuver_h

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
	int Distance(Sensor sensor);

private:
	int _driveA;
	int _driveB;
	int _motor1;
	int _motor2;
	int _motor3;
	int _motor4;
	int _speed;
	bool _debug;
	bool _isConfigured = false;
};

#endif