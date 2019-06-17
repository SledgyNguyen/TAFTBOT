#ifndef USensor_H
#define USensor_H

#include "Arduino.h"

class USensor {

    public:

        //CONSTRUCTOR
        USensor(byte uTrigPin, byte uEchoPin);

        void setSensorPin(byte uTrigPin, byte uEchoPin);

        int sensorMeasure();

    private:

        byte trigPin;
        byte echoPin;

        int duration;
        int cm;

};

#endif

