//This program tests the sensor and tempSensor class
//It will initialize the temperature sensor, read it 100 times and print the result to the log

#include "temp_sensor.hpp"
#include <iostream>

using namespace std;

int main() {

	string sensorName = "tempSensor";
	tempSensor tempS(sensorName);
	cout << "Sensor 1 initialized" << endl;

	tempS.initSensor();
	for(int i = 0; i < 100; i++)
	{
	tempS.readSensor();
	}

}
