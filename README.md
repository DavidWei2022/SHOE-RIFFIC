# SHOE-RIFFIC 
The two-minute solution to your sole's problems
-
The colisted files were created to test and debug the SHOE-RIFFIC prototype for full functionality.
* SR_TrialOne.ino - original test file, used to model expected functionalities of complete prototype on LCD
* PushButtonPullUpTesting.ino - test file checking the proper declaration for push buttons
* SR_TRIAL_GND_ERR_PINS.ino - test file to check functionality of push buttons and associated error checking pins
* SHOE_RIFFIC_RELAY_BUTTON_TEST.ino - test file testing codeflow from push button to relay
* 11_04_2023_test_file - full functionality final test
* SR_Final.ino - full functionality test, updated with final UI
  
## **TO RUN SHOE-RIFFIC**
Upload SR_Final.ino via the SHOE_RIFFIC prototype's USB port to update the functionality. 

## CODE DESCRIPTION

The code provides user interface commands for the control box with 3 buttons. When uploaded to the prototype, the control box functions with 3 types of signals: reset, wash, and dry.

* Reset: Reset the wash counter and dry counter back to 0.

* Wash: Pressing the wash button sends a command to relay 1 for 30 seconds. Additionally, it updates the wash counter by 1. The cycle's duration can be changed by modifying the global variable, washTime. 

* Dry: Pressing the dry button sends a command to relay 2 for 30 seconds.  Additionally, it updates the dry counter by 1. The cycle's duration can be changed by modifying the global variable, dryTime.


### When the maxWash or maxDry values are reached, the unit must be reset via the reset button
These values are predefined in the code, SR_Final.ino defines them as:
* int maxWash = 10;
* int maxDry = 10;


## CONTROL BOX WIRING DIAGRAMS
<img width="385" alt="Screen Shot 2023-12-05 at 9 48 43 PM" src="https://github.com/DavidWei2022/SHOE-RIFFIC/assets/23131199/4e374a3f-4c03-499e-8bfb-ff618b8747b4">
