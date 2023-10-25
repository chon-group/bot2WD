// Agent bob in project jasonProject
/* Initial beliefs and rules */

serialPort(ttyACM0).
/* Initial goals */
!start.

/* Plans */
+!start <- 
    ?serialPort(SP);
    .port(SP);
    .percepts(open);
    .limit(750).


+motorStatus(M) <-    .print("Motor Status -> ",M).

+distance(D) <- .print("Distance Status -> ",D).

+luminosity(Lu) <- .print("Luminosity Status -> ",Lu).

+buzzerStatus(B)  <- .print("Buzzer Status -> ",B).

+ledStatus(L) <- .print("Led Status -> ",L).

+port(P,S): S=off & serialPort(SP) <- .print("Serial Port ",SP, " offline!").      
