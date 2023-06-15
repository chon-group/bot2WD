![Chon2WD](https://sourceforge.net/p/chonos/bots/ci/master/tree/models/2WD/images/2wd.png?format=raw "Chon2WD")
# ChonBot 2WDv1
### _A low-cost 2WD prototype model for Embedded Multi-agent Systems_
## Reasoning Layer
### Actions
```sh
.act(buzzerOn | buzzerOnH | buzzerOnL | buzzerOff);                 // Buzzer
.act(lightOn | lightOnH | lightOnL | lightOff);                     // HeadLight
.act(breakLOn | breakLOff);                                         // BreakLight
.act(goAhead | goLeft | goRight | goBack | stop );                  // Motor direction
.act( speedH | speedM | speedL);                                    // Motor speed
.act(alertOn | flashROn | flashLOn | flashLightOff);                // FlashLight
```
### Perceptions
```sh
+luminosity(N).                                                     // LDR sensor
+distance(N).                                                       // Ultrasonic sensor
+motor(stopped | running | turningRight | turningLeft | backward).  // Motor Status
+speed(default | high | low).                                       // Motor Speed
+lineL(N). +lineR(N).                                               // Line-following sensors
+flashLight(off | right | left | alert).                            // Flashlights LED
+light( off | on | high | low).                                     // HeadLight LED
+breakL(off | on).                                                  // BreakLight LED
+buzzer(off | on | high | low).                                     // Buzzer
```