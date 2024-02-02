/* Initial beliefs and rules */
serialPort(ttyACM0).
/* Initial goals */
!start.

/* Plans */
+!start: serialPort(SerialPort) <- 
    .print("I am Max the Road Warrior!"); 
    argo.port(SerialPort);
	argo.limit(1000);
    argo.percepts(open).

+luminosity(Lu) <- .print("Luminosity Status -> ",Lu).
+flashLight(FL) <- .print("FlashLight Status -> ",FL).
+distance(D)    <- .print("Distance Status -> ",D).
+breakL(BL)     <- .print("Break Light Status -> ",BL).
+buzzer(B)      <- .print("Buzzer Status -> ",B).
+lineL(LL)      <- .print("Line-following Left Status -> ",LL). 
+lineR(LR)      <- .print("Line-following Right Status -> ",LR).
+motor(M)       <- .print("Motor Status -> ",M).
+light(L)       <- .print("Light Status -> ",L).
+speed(S)       <- .print("Speed Status -> ",S).  

+port(P,S): (S=off | S=timeout) & serialPort(SP) & P=SP <- 
    .print("Serial Port ",SP, " is ",S,"!");
    .stopMAS.                                         
