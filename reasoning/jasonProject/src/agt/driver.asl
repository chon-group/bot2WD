// Agent bob in project jasonProject
/* Initial beliefs and rules */
serialPort(ttyACM0).
/* Initial goals */
!start.

/* Plans */
+!start : true <- 
    .print("hello world.");
    ?serialPort(SP);
    argo.port(SP);
    argo.percepts(open).

+motor(M) <-    .print("Motor Status -> ",M).
+flashLight(FL) <- .print("FlashLight Status -> ",FL).
+light(L) <- .print("Light Status -> ",L).
+buzzer(B)  <- .print("Buzzer Status -> ",B).
+speed(S) <- .print("Speed Status -> ",S).
+breakL(BL) <- .print("Break Light Status -> ",BL).
+luminosity(Lu) <- .print("Luminosity Status -> ",Lu).
+distance(D) <- .print("Distance Status -> ",D).
+lineL(LL) <- .print("Line-following Left Status -> ",LL). 
+lineR(LR) <- .print("Line-following Right Status -> ",LR).  

+port(P,S): S=off & serialPort(SP) <- .print("Serial Port ",SP, " offline!").                                             
