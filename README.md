# SHOE-RIFFIC README
Please upload SR_Final.ino to any existing prototype with an Arduino Namo board connected to 2 relays connected to a motor that pumps the water and a fan.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
The code provides a user interface for the control box with 3 buttons. If it is uploaded to the correct prototype, the control box will be able to send 3 types of signals, wash, dry, and reset.

Reset: Reset the wash counter and dry counter back to 0.
Wash: Pressing the wash button sends a command to relay 1 for 30 seconds. The time could be changed by changing the global variable called washTime. 
Dry:  Pressing the dry button sends a command to relay 2 for 30 seconds. The time could be changed by changing the global variable called dryTime.
After the wash or dry function is finished, the wash counter or dry counter gets increased by 1.
The wash and dry signals actives both relays that turn on either the motor to pump the water which navigates through the nozzles and moist the brushes, or actives the fan that blows strong wind to dry off water drops on the user's shoe. 
The code also includes 2 counters each for wash and dry count, as well as a maximum threshold for both wash and dry. If either counter reaches 10, which is the set maximum threshold that the programmer could change, the entire system enters the maintenance stage and it requires a reset.
