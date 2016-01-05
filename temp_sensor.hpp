//The temp_sensor class is responsible for reading the temperature, and storing it in the logfile.

#include "sensor.hpp"


class tempSensor : public Sensor {

public:

	tempSensor(string name) : Sensor(name){} //Calling the parent constructor with the child constructor.
	int initSensor();
	int readSensor();

private:

	int fd_; //File handler for I2C bus.

};
