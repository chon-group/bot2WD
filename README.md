# ChonBot 2WD
### _A low-cost 2WD prototype model for Embedded Multi-agent Systems_
![2wd](https://github.com/chon-group/bot2WD/assets/32855001/b5a9442c-c064-492e-ac64-9c5a792cedb6)

## Reasoning Layer
### Actions
```sh
.act(goAhead  | goLeft    | goRight   | goBack  | stop ); // Motor direction
.act(buzzerOn | buzzerOnH | buzzerOnL | buzzerOff);       // Buzzer
.act(lightOn  | lightOnH  | lightOnL  | lightOff);        // HeadLight
.act(alertOn  | flashROn  | flashLOn  | flashLightOff);   // FlashLight
.act(speedH   | speedM    | speedL);                      // Motor speed
.act(breakLOn | breakLOff);                               // BreakLight
```
### Perceptions
```sh

+motor(stopped  | running | turningRight  | turningLeft | backward).  // Motor Status
+flashLight(off | right   | left          | alert).                   // Flashlights LED
+light( off     | on      | high          | low).                     // HeadLight LED
+buzzer( off    | on      | high          | low).                     // Buzzer
+speed(default  | high    | low).                                     // Motor Speed
+breakL( off    | on).                                                // BreakLight LED
+luminosity(N).                                                       // LDR sensor
+distance(N).                                                         // Ultrasonic sensor
+lineL(N).                                                            // Line-following sensors
+lineR(N).                                               
```
