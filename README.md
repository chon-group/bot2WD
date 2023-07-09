# ChonBot 2WD
ChonBots are low-cost basic prototype models, part of a [Toolkit for teaching AI supported by robotic-agents](https://doi.org/10.5753/wei.2023.229753).
### _A low-cost 2WD prototype model for Embedded Multi-agent Systems_
![Untitled design-min](https://github.com/chon-group/bot2WD/assets/32855001/7e33eacd-4964-4752-9baf-10cd005d50ef)

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
### How to cite?
LAZARIN, Nilson Mori; PANTOJA, Carlos Eduardo; VITERBO, José. Towards a Toolkit for Teaching AI Supported by Robotic-agents: Proposal and First Impressions. _In: WORKSHOP SOBRE EDUCAÇÃO EM COMPUTAÇÃO (WEI)_, 31. , 2023, João Pessoa/PB. Anais [...]. Porto Alegre: Sociedade Brasileira de Computação, 2023 . p. 20-29. ISSN 2595-6175. DOI: https://doi.org/10.5753/wei.2023.229753. 
