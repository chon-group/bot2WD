#include <Javino.h>               //Available at: https://github.com/chon-group/javino2arduino
#include <HCSR04.h>               //Available at: https://www.arduinolibraries.info/libraries/hcsr04

#define PinLight  2               // Farol
#define PinBreakL 3               // Freio
#define PinEcho   5               // Sensor de Ultrasom Echo 5 e Trig 4
#define PinTrig   4               
#define PinBuzzer 22               // Buzzer
#define PinBridH1 7               // Ponte H M1=10, M2=9, M3=8, M4=7
#define PinBridH2 8 
#define PinBridH3 9 
#define PinBridH4 10
#define PinRx     11              // Transceptor RF: Rx11, Tx12
#define PinTx     12
#define PinLed    13              // Alerta ou Giroflex
#define PinLDR    A0              // Sensor de Luz


Javino javino;
UltraSonicDistanceSensor hc(PinTrig, PinEcho);
String strLedStatus;
String strBuzzerStatus;
String strMotorStatus;

void setup(){
  pinMode(PinLDR,     INPUT);
  pinMode(PinLight,   OUTPUT);
  pinMode(PinBreakL,  OUTPUT);
  pinMode(PinBuzzer,  OUTPUT);
  pinMode(PinLed,     OUTPUT);
  pinMode(PinBridH1,  OUTPUT);
  pinMode(PinBridH2,  OUTPUT);
  pinMode(PinBridH3,  OUTPUT);
  pinMode(PinBridH4,  OUTPUT);
  pinMode(PinTrig,    OUTPUT);
  pinMode(PinEcho,    INPUT);
  
  setLedStatus("off");
  setBuzzerStatus("off");
  setMotorStatus("stopped");
  javino.start(9600);
}

void serialEvent(){
  javino.readSerial();
}

void loop(){
  if(javino.availableMsg()){
    String strMsg = javino.getMsg();
    if(strMsg=="getPercepts"){javino.sendMsg(getStatus());}
    else if(strMsg=="buzzerOn"){buzzer("on");}
    else if(strMsg=="buzzerOff"){buzzer("off");}
    else if(strMsg=="ledOn"){led("on");}
    else if(strMsg=="ledOff"){led("off");}
    else if(strMsg=="stop"){stopRightNow();}
    else if(strMsg=="goLeft"){turnLeft();}
    else if(strMsg=="goRight"){turnRight();}
    else if(strMsg=="goAhead"){goAhead();}
    else if(strMsg=="lightOn"){light(true);}
    else if(strMsg=="lightOff"){light(false);}
    else if(strMsg=="breakLOn"){blight(true);}
    else if(strMsg=="breakLOff"){blight(false);}
  }
}

void light(boolean state){
  if(state){digitalWrite(PinLight, HIGH);}
  else{digitalWrite(PinLight, LOW);}
}

void blight(boolean state){
  if(state){digitalWrite(PinBreakL, HIGH);}
  else{digitalWrite(PinBreakL, LOW);}
}

void buzzer(String strOpt){
  if(strOpt=="on"){digitalWrite(PinBuzzer, HIGH);}
  else{digitalWrite(PinBuzzer, LOW);}
  setBuzzerStatus(strOpt);
}

void led(String strledOpt){
  if(strledOpt=="on"){
    digitalWrite(PinLed, HIGH);
  }else{
    digitalWrite(PinLed, LOW);
  }
  setLedStatus(strledOpt);
}

void goAhead(){
    digitalWrite(PinBridH1, HIGH);
    digitalWrite(PinBridH2, LOW);
    digitalWrite(PinBridH3, HIGH);
    digitalWrite(PinBridH4, LOW);
    setMotorStatus("running");
}


void stopRightNow(){
  digitalWrite(PinBridH1, LOW);
  digitalWrite(PinBridH2, LOW);
  digitalWrite(PinBridH3, LOW);
  digitalWrite(PinBridH4, LOW);
  setMotorStatus("stopped");
}

void turnLeft(){
  digitalWrite(PinBridH1, HIGH);
  digitalWrite(PinBridH2, LOW);
  digitalWrite(PinBridH3, LOW);
  digitalWrite(PinBridH4, HIGH);
  setMotorStatus("turningLeft");
}


void turnRight(){
  digitalWrite(PinBridH1, LOW);
  digitalWrite(PinBridH2, HIGH);
  digitalWrite(PinBridH3, HIGH);
  digitalWrite(PinBridH4, LOW);
  setMotorStatus("turningRight");
}


String getStatus(){
  int d = hc.measureDistanceCm();
  if(d==0){
    d=1024;
  }
  String out =  "ledStatus("+strLedStatus+");"+
                "buzzerStatus("+strBuzzerStatus+");"+
                "luminosity("+String(analogRead(PinLDR))+");"+
                "distance("+String(d)+");"+
                "motorStatus("+strMotorStatus+");";

   return out;
}

void setBuzzerStatus(String newValue){
  strBuzzerStatus=newValue;
}

void setLedStatus(String newValue){
  strLedStatus=newValue;
}

void setMotorStatus(String newValue){
  strMotorStatus=newValue;
}
