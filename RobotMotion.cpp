#include "Arduino.h"
#include "RobotMotion.h"


/** CONSTRUCTOR: FULL **/
RobotMotion::RobotMotion(byte mad, byte mas, byte mbd, byte mbs){
    setControlPins(mad, mas, mbd, mbs);
}


/** CONSTRUCTOR: DEFAULT **/
RobotMotion::RobotMotion() {
    //setEnablePins(1, 2);
    setControlPins(1, 2, 3, 4);
    //setSpeed(255);
}

/** SET MOTOR PINS **/
void RobotMotion::setControlPins(byte mad, byte mas, byte mbd, byte mbs) {

    ad = mad;
    as = mas;
    bd = mbd;
    bs = mbs;

    pinMode(ad, OUTPUT);
    pinMode(as, OUTPUT);
    pinMode(bd, OUTPUT);
    pinMode(bs, OUTPUT);
}


/** FORWARD **/
void RobotMotion::moveForward(int spd){
  digitalWrite(ad, LOW);
  digitalWrite(bd, LOW);

  analogWrite(as, spd);
  analogWrite(bs, spd);
}


/** TURN LEFT **/
void RobotMotion::left(int spd){
  digitalWrite(ad, HIGH);
  digitalWrite(bd, LOW);

  analogWrite(as, spd);
  analogWrite(bs, spd);
}


/** TURN RIGHT **/
void RobotMotion::right(int spd){
  digitalWrite(ad, LOW);
  digitalWrite(bd, HIGH);

  analogWrite(as, spd);
  analogWrite(bs, spd);
}


/** STOP **/
void RobotMotion::stopNow(){
  analogWrite(as, 0);
  analogWrite(bs, 0);
}
