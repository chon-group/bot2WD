#include <Javino.h>     //Available at: https://github.com/chon-group/javino2arduino
#include <HCSR04.h>     //Available at: https://github.com/Martinsos/arduino-lib-hc-sr04

#define PinLight  2     // Farol
#define PinBreakL 3     // Freio
#define PinEcho   4     // Sensor de Ultrasom Echo 4 e Trig 5
#define PinTrig   5              
#define PinBuzzer 6     // Buzzer
#define PinBridH1 7     // Ponte H M1=7, M2=8, M3=9, M4=10
#define PinBridH2 8
#define PinBridH3 9
#define PinBridH4 10
#define PinLed    13    // Alerta ou Giroflex
#define PinLDR    A0    // Sensor de Luz


Javino javino;
UltraSonicDistanceSensor hc(PinTrig, PinEcho);
String strLedStatus, strLightStatus, strBreakLStatus, strBuzzerStatus, strMotorStatus;
unsigned long lastPercept = -1;

void serialEvent(){
   javino.readSerial();
}


void loop(){
if(javino.availableMsg()){
  String strMsg = javino.getMsg();
  if(strMsg=="getPercepts"){javino.sendMsg(getStatus());}
    else if(strMsg=="buzzerOn") {buzzer("on");}
    else if(strMsg=="buzzerOff")  {buzzer("off");}
    else if(strMsg=="ledOn")  {led("on");}
    else if(strMsg=="ledOff") {led("off");}
    else if(strMsg=="lightOn")  {light("on");}
    else if(strMsg=="lightOff") {light("off");}
    else if(strMsg=="breakLOn") {breakL("on");}
    else if(strMsg=="breakLOff")  {breakL("off");}
    else if(strMsg=="stop") {stopRightNow();}
    else if(strMsg=="goLeft") {turnLeft();}
    else if(strMsg=="goRight")  {turnRight();}
    else if(strMsg=="goAhead")  {goAhead();}

    lastPercept = millis();
  }

  if((lastPercept != -1) && (millis() > lastPercept+5000)){
    powerOff();
  }
}

void buzzer(String strOpt){
if(strOpt=="on"){digitalWrite(PinBuzzer, HIGH);}
  else{digitalWrite(PinBuzzer, LOW);}
setBuzzerStatus(strOpt);
}

void led(String strledOpt){
if(strledOpt=="on"){digitalWrite(PinLed, HIGH);}
  else{digitalWrite(PinLed, LOW);}
setLedStatus(strledOpt);
}

void light(String strledOpt){
if(strledOpt=="on"){digitalWrite(PinLight, HIGH);}
  else{digitalWrite(PinLight, LOW);}
setLightStatus(strledOpt);
}

void breakL(String strledOpt){
  if(strledOpt=="on"){
    digitalWrite(PinBreakL, HIGH);
  }else{
    digitalWrite(PinBreakL, LOW);
  }
  setBreakLStatus(strledOpt);
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

  
String out =  
"ledStatus("+strLedStatus+");"+
"lightStatus("+strLightStatus+");"+
"breakLStatus("+strBreakLStatus+");"+
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

void setLightStatus(String newValue){
  strLightStatus=newValue;
}

void setBreakLStatus(String newValue){
  strBreakLStatus=newValue;
}

void setMotorStatus(String newValue){
  strMotorStatus=newValue;
}



void setup(){
  pinMode(PinLight,   OUTPUT);
  pinMode(PinBreakL,  OUTPUT);
  pinMode(PinBuzzer,  OUTPUT);
  pinMode(PinLed,     OUTPUT);
  pinMode(PinBridH1,  OUTPUT);
  pinMode(PinBridH2,  OUTPUT);
  pinMode(PinBridH3,  OUTPUT);
  pinMode(PinBridH4,  OUTPUT);
  pinMode(PinLDR,     INPUT);
  pinMode(PinTrig,    OUTPUT);
  pinMode(PinEcho,    INPUT);
  Serial.begin(9600);

  setLedStatus("off");
    setLightStatus("off");
    setBreakLStatus("off");
    setBuzzerStatus("off");
    setMotorStatus("stopped");

}

void powerOff() {
  // Define todos os pinos digitais de 2 a 13 (Arduino Uno) e 2 a 53 (Arduino Mega) como LOW.
  for (int i = 2; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
  
  // Se estiver usando um Arduino Mega, também configure os pinos adicionais.
#ifdef ARDUINO_AVR_MEGA
  for (int i = 22; i <= 53; i++) {
    digitalWrite(i, LOW);
  }
#endif
}
