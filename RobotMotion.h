#ifndef DCMotorBot_H
#define DCMotorBot_H

#include "Arduino.h"

class RobotMotion {

    public:
        // CONSTRUCTOR:
        RobotMotion(); // DEFAULT
        RobotMotion(byte mad, byte mas, byte mbd, byte mbs); // FULL

        void setControlPins(byte mad, byte mas, byte mbd, byte mbs);

        // movement functions
        void moveForward(int spd);
        void left(int spd);
        void right(int spd);
        void stopNow();

    private:
        // Control Pins
        byte ad;
        byte as;
        byte bd;
        byte bs;
};

#endif
