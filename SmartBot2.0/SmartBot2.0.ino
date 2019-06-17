#include <RobotMotion.h>
#include <taftutils.h>
#include <USensor.h>

#include <RobotMotion.h>
#include <taftutils.h>
#include <USensor.h>

#include <RobotMotion.h>
#include <USensor.h>

#define ts 12

#define UMt 6
#define UMe 7

#define ULt 4
#define ULe 5

#define URt 11
#define URe 10

#define MOTORAD 2
#define MOTORBD 8

#define MOTORAS 3
#define MOTORBS 9

int dlen = 100;
int spd = 255;
int loth = 5;
int upth = 50;
int Ath = 25;           //Detection range for AVOIDING
int Fth = 45;           //Detection range for FOLLOWING

int re;
bool sm;
int sv1, sv2, sv3;
int cv1, cv2, cv3;      //Constrain Values
int od1, od2, od3;      //Object Detection Flag

USensor midSen(UMt, UMe);
USensor leftSen(ULt, ULe);
USensor rightSen(URt, URe);

RobotMotion TAFT(MOTORAD, MOTORAS, MOTORBD, MOTORBS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Tracking Sensor
  pinMode(ts, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sv1 = midSen.sensorMeasure();
  sv2 = leftSen.sensorMeasure();
  sv3 = rightSen.sensorMeasure();
  
  cv1 = constrain(sv1, loth, upth);
  cv2 = constrain(sv2, loth, upth); 
  cv3 = constrain(sv3, loth, upth);

  //DETECT CURRENT MODE
  sm = digitalRead(ts);


  //---MODE SWITCHING
  //Hat OFF
  if (sm == 1){
    Serial.print("MODE ");
    Serial.print(sm);
    Serial.println(": Following");

    od1 = dect(cv1, Fth);
    od2 = dect(cv2, Fth);
    od3 = dect(cv3, Fth);

    //---FOLLOWING STARTS---
    if (od1 == 1){
    
    //Left is active: 110
      if ((od2 == 1) && (od3 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 110: ");
        
        //---Change decision HERE---
        Serial.println("Forward 1-2");
        TAFT.moveForward(spd);
        //--------------------------
        
      }
      
      //Right is active: 101
      else if ((od3 == 1) && (od2 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 101: ");
        
        //---Change decision HERE---
        Serial.println("Forward 1-3");
        TAFT.moveForward(spd);
        //--------------------------
      }
      
      //Left and Right are active: 111
      else if ((od2 == 1) && (od3 == 1)){
        monitor(od1, od2, od3);
        Serial.print("Case 111: ");
        
        //---Change decision HERE---
        Serial.println("Stop! 1");
        TAFT.stopNow();
        //--------------------------
      }
      
      //Left and Right are inactive: 100
      //Making a random turn
      else {
        monitor(od1, od2, od3);
        Serial.print("Case 100: ");
        
        //---Change decision HERE---
        Serial.println("Forward 1-1");
        TAFT.moveForward(spd);
      }
    }
  
    //Mid is inactive
    else if (od1 == 0){
      
      //Left is active: 010
      if ((od2 == 1) && (od3 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 010: ");
        
        //---Change decision HERE---
        Serial.println("Turning left 2");
        TAFT.left(spd);
        //--------------------------
      }
      
      //Right is active: 001
      else if ((od3 == 1) && (od2 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 001: ");
        
        //---Change decision HERE---
        Serial.println("Turning right 2");
        TAFT.right(spd);
        //--------------------------
      }
      
      //Left and Right are active: 011
      else if ((od2 == 1) && (od3 == 1)){
        if (cv2 > cv3){
          monitor(od1, od2, od3);
          Serial.print("Case 011-R: ");
          
          //---Change decision HERE---
          Serial.println("Turning right 3");
          TAFT.right(spd);
          //--------------------------
        }
        else {
          monitor(od1, od2, od3);
          Serial.print("Case 011-L: ");
          
          //---Change decision HERE---
          Serial.println("Turning left 3");
          TAFT.left(spd);
          //--------------------------
        }
      }
      
      //Left and Right are inactive: 000
      else {
        monitor(od1, od2, od3);
        Serial.print("Case 000: ");
        
        //---Change decision HERE---
        Serial.println("Stop! 2");
        TAFT.stopNow();
        //--------------------------
      }
    }
    //---FOLLOWING ENDS---
  }

  //Hat ON
  else {
    Serial.print("MODE ");
    Serial.print(sm);
    Serial.println(": Avoiding");

    od1 = dect(cv1, Ath);
    od2 = dect(cv2, Ath);
    od3 = dect(cv3, Ath);

    //---AVOIDING STARTS---
    //Mid is active
    if (od1 == 1){
      
      //Left is active: 110
      if ((od2 == 1) && (od3 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 110: ");
        
        //---Change decision HERE---
        Serial.println("Turning right 1");
        TAFT.right(spd);
        //--------------------------
        
      }
      
      //Right is active: 101
      else if ((od3 == 1) && (od2 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 101: ");
        
        //---Change decision HERE---
        Serial.println("Turning left 1");
        TAFT.left(spd);
        //--------------------------
      }
      
      //Left and Right are active: 111
      else if ((od2 == 1) && (od3 == 1)){
        monitor(od1, od2, od3);
        Serial.print("Case 111: ");
        
        //---Change decision HERE---
        Serial.println("Stop! 1");
        TAFT.stopNow();
        //--------------------------
      }
      
      //Left and Right are inactive: 100
      //Making a random turn
      else {
        int re = randDec();
        if (re == 1){
          monitor(od1, od2, od3);
          Serial.print("Case 100: ");
          
          //---Change decision HERE---
          Serial.println("Randomly turning left 3");
          TAFT.left(spd);
          //--------------------------
        }
          
        else {
          monitor(od1, od2, od3);
          Serial.print("Case 100: ");
          
          //---Change decision HERE---
          Serial.println("Randomly turning right 3");
          TAFT.right(spd);
          //--------------------------
        }
      }
    }
    
    //Mid is inactive
    else if (od1 == 0){
      
      //Left is active: 010
      if ((od2 == 1) && (od3 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 010: ");
        
        //---Change decision HERE---
        Serial.println("Turning right 2");
        TAFT.right(spd);
        //--------------------------
      }
      
      //Right is active: 001
      else if ((od3 == 1) && (od2 == 0)){
        monitor(od1, od2, od3);
        Serial.print("Case 001: ");
        
        //---Change decision HERE---
        Serial.println("Turning left 2");
        TAFT.left(spd);
        //--------------------------
      }
      
      //Left and Right are active: 011
      else if ((od2 == 1) && (od3 == 1)){
        monitor(od1, od2, od3);
        Serial.print("Case 011: ");
        
        //---Change decision HERE---
        Serial.println("Stop! 2");
        TAFT.stopNow();
        //--------------------------
      }
      
      //Left and Right are inactive: 000
      else {
        monitor(od1, od2, od3);
        Serial.print("Case 000: ");
        
        //---Change decision HERE---
        Serial.println("Forward! 2");
        TAFT.moveForward(spd);
        //--------------------------
      }
    }
    //---AVOIDING ENDS---
  }
  
    
  delay(dlen);

}


//DISPLAY INFORMATION
void monitor(int od1, int od2, int od3){
  Serial.print(od2);
  Serial.print(" - ");
  Serial.print(od1);
  Serial.print(" - ");
  Serial.println(od3);
}
