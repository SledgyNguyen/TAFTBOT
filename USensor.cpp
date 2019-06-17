#include "Arduino.h"
#include "USensor.h"


USensor::USensor(byte uTrigPin, byte uEchoPin){
    setSensorPin(uTrigPin, uEchoPin);
}


/** SET SENSOR PIN **/
void USensor::setSensorPin(byte uTrigPin, byte uEchoPin){
    trigPin = uTrigPin;
    echoPin = uEchoPin;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}


/** SENSOR MEASURE **/
int USensor::sensorMeasure(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);

    cm = (duration/2) / 29.1;
    return cm;
}
