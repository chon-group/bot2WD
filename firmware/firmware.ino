#include <Javino.h>               //Available at: https://github.com/chon-group/javino2arduino
#include <HCSR04.h>               //Available at: https://www.arduinolibraries.info/libraries/hcsr04

#define PinBreakL  2               // BreakLight
#define PinHeadL   3               // HeadLight 
#define PinFLRight 4               // Right Flashlight
#define PinBridH1  5               // HBridge IN1
#define PinBridH2  6               // HBridge IN2
#define PinEcho    7               // Ultrasonic sensor ECHO
#define PinTrig    8               // Ultrasonic sensor TRIG
#define PinBridH3  9               // HBridge IN3
#define PinBridH4  10              // HBridge IN4
#define PinBuzzer  11              // Buzzer
#define PinFLLeft  12              // Left Flashlight
#define PinLDR     A0              // LDR sensor
#define PinLineFR  A1              // Right infrared reflective sensor
#define PinLineFL  A2              // Left infrared reflective sensor

Javino javino;
HCSR04 hc(PinTrig, PinEcho);
String strFlashLStatus, strLightStatus, strBreakLStatus, strBuzzerStatus, strMotorStatus, strSpeedStatus;
int intSpeed;

void serialEvent(){
  javino.readSerial();
}

void setup(){
  javino.start(9600);
  pinMode(PinBreakL,  OUTPUT);
  pinMode(PinHeadL,   OUTPUT);
  pinMode(PinFLRight, OUTPUT);
  pinMode(PinBridH1,  OUTPUT);
  pinMode(PinBridH2,  OUTPUT);
  pinMode(PinEcho,    INPUT);
  pinMode(PinTrig,    OUTPUT);  
  pinMode(PinBridH3,  OUTPUT);
  pinMode(PinBridH4,  OUTPUT);
  pinMode(PinBuzzer,  OUTPUT);  
  pinMode(PinFLLeft,  OUTPUT);
  pinMode(PinLDR,     INPUT);
  pinMode(PinLineFR,  INPUT);
  pinMode(PinLineFL,  INPUT);

  breakL("off");
  light("off");
  flashlight("alert","off");
  stopRightNow();
  buzzer("off");
  setMotorSpeed("default");
}



void loop(){
if(javino.availableMsg()){
  String strMsg = javino.getMsg();
  if(strMsg=="getPercepts")javino.sendMsg(getStatus());
    else if(strMsg=="buzzerOnH")buzzer("high");
    else if(strMsg=="buzzerOn")buzzer("on");
    else if(strMsg=="buzzerOnL")buzzer("low");
    else if(strMsg=="buzzerOff")buzzer("off");
    else if(strMsg=="lightOnH")light("high");
    else if(strMsg=="lightOn")light("on");
    else if(strMsg=="lightOnL")light("low");
    else if(strMsg=="lightOff")light("off");
    else if(strMsg=="breakLOn")breakL("on");
    else if(strMsg=="breakLOff")breakL("off");
    else if(strMsg=="stop")stopRightNow();
    else if(strMsg=="goLeft")turnLeft();
    else if(strMsg=="goRight")turnRight();
    else if(strMsg=="goAhead")goAhead();
    else if(strMsg=="goBack")goBack();
    else if(strMsg=="speedH")setMotorSpeed("high");
    else if(strMsg=="speedM")setMotorSpeed("default");
    else if(strMsg=="speedL")setMotorSpeed("low");
    else if(strMsg=="alertOn") flashlight("alert","on");
    else if(strMsg=="flashROn") flashlight("right","on");
    else if(strMsg=="flashLOn") flashlight("left","on");
    else if(strMsg=="flashLightOff") flashlight("all","off");
  }
}

void flashlight(String strFLight, String strOpt){
  if(strOpt=="off"){
    digitalWrite(PinFLLeft, LOW);
    digitalWrite(PinFLRight, LOW);
    setFlashLStatus("off");
  }else{
    if(strFLight=="right"){
      digitalWrite(PinFLLeft, LOW);
      digitalWrite(PinFLRight, HIGH);
      setFlashLStatus("right");      
    }else if(strFLight=="left"){
      digitalWrite(PinFLLeft, HIGH);
      digitalWrite(PinFLRight, LOW);
      setFlashLStatus("left");            
    }else{
      digitalWrite(PinFLLeft, HIGH);
      digitalWrite(PinFLRight, HIGH);
      setFlashLStatus("alert");       
    }
  }
}

void buzzer(String strOpt){
  if(strOpt=="on")analogWrite(PinBuzzer, 191);
  else if(strOpt=="high")analogWrite(PinBuzzer, 255);
  else if(strOpt=="low")analogWrite(PinBuzzer, 127);
  else digitalWrite(PinBuzzer, LOW);
  setBuzzerStatus(strOpt);
}

int getMotorSpeed(){
  return intSpeed;
}

void setMotorSpeed(String strSpeed){
  if(strSpeed=="default") intSpeed=191;
  else if(strSpeed=="high") intSpeed=255;
  else intSpeed=127;
  setSpeedStatus(strSpeed);
}



void light(String strledOpt){
  if(strledOpt=="on") analogWrite(PinHeadL, 127);
  else if(strledOpt=="high") analogWrite(PinHeadL, 255);
  else if(strledOpt=="low") analogWrite(PinHeadL, 63);
  else digitalWrite(PinHeadL, LOW);
  setLightStatus(strledOpt);
}

void breakL(String strledOpt){
  if(strledOpt=="on")digitalWrite(PinBreakL, HIGH);
  else digitalWrite(PinBreakL, LOW);
  setBreakLStatus(strledOpt);
}

void goBack(){
    analogWrite(PinBridH1, 255);
    analogWrite(PinBridH2, 0);
    analogWrite(PinBridH3, 255);
    analogWrite(PinBridH4, 0);
    setMotorStatus("backward");
    delay(200);
    analogWrite(PinBridH1, getMotorSpeed());
    analogWrite(PinBridH3, getMotorSpeed());
}

void goAhead(){
    analogWrite(PinBridH1, 0);
    analogWrite(PinBridH2, 255);
    analogWrite(PinBridH3, 0);
    analogWrite(PinBridH4, 255);
    setMotorStatus("running");
    delay(200);
    analogWrite(PinBridH2, getMotorSpeed());
    analogWrite(PinBridH4, getMotorSpeed());
}


void stopRightNow(){
  analogWrite(PinBridH1, 0);
  analogWrite(PinBridH2, 0);
  analogWrite(PinBridH3, 0);
  analogWrite(PinBridH4, 0);
  setMotorStatus("stopped");
}

void turnRight(){
  analogWrite(PinBridH1, 255);
  analogWrite(PinBridH2, 0);
  analogWrite(PinBridH3, 0);
  analogWrite(PinBridH4, 255);
  setMotorStatus("turningRight");
  delay(200);
  analogWrite(PinBridH1, getMotorSpeed());
  analogWrite(PinBridH4, getMotorSpeed());
}


void turnLeft(){
  analogWrite(PinBridH1, 0);
  analogWrite(PinBridH2, 255);
  analogWrite(PinBridH3, 255);
  analogWrite(PinBridH4, 0);
  setMotorStatus("turningLeft");
  delay(200);
  analogWrite(PinBridH2, getMotorSpeed());
  analogWrite(PinBridH3, getMotorSpeed());
}


void setSpeedStatus(String newValue){
  strSpeedStatus=newValue;
}


String getStatus(){
    int d = hc.dist();
    if(d==0){
      d=1024;
    }  
    String out =  
      "flashLight("+strFlashLStatus+");"+
      "light("+strLightStatus+");"+
      "breakL("+strBreakLStatus+");"+
      "buzzer("+strBuzzerStatus+");"+
      "luminosity("+String(analogRead(PinLDR))+");"+
      "distance("+String(d)+");"+
      "motor("+strMotorStatus+");"+
      "speed("+strSpeedStatus+");"+
      "lineL("+String(analogRead(PinLineFL))+");"+
      "lineR("+String(analogRead(PinLineFR))+");";
         
    return out;
}

void setBuzzerStatus(String newValue){
  strBuzzerStatus=newValue;
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

void setFlashLStatus(String newValue){
  strFlashLStatus=newValue;
}
