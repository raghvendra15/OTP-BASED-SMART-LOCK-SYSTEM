OTP BASED SMART LOCKER SYSTEM
It is a higher level security system based on arduino nano via Bluetooth connectivity.
Components used :-
Arduino nano , HC05(Bluetooth module),  4x4 keypad, 16*2 LCD  WITH I2C  , BUZZER, LED, Breadboard , Jumper Wires , Solenoid lock, 12 v AC adaptor ,  8*8 inch Box with handle  , 12v DC male female jack,  12v Relay .
DESCRIPTION : 
This project comprises higher level security system. Like it have Bluetooth pairing password then unlocking through OTP only  and also  there is one master code which can be  used when something wrong suspects with unlocking through OTP .
Starting with uploading the code in arduino nano then the application in the device (i.e. mobile) has  to be intstalled ( i have used SERIAL BLUETOOTH TERMINAL). Then  the power is to the system through adapter.
 Suppose the door is locked .  The application  on the device need to be opened , so the device will ask form pairing  with HC05 bluetooth module , for this it will ask for password to pair (the default password of HC05 is 0000 or 1234), or you may change it via AT commands through arduino ide ,  after this for unlocking it will ask for otp.  For this send the command i.e. OTP through the application which is to be sent to arduino which generate a 5 digit random one time password.then press (*) through keypad to enter OTP  , then enter the OTP through the keypad you can see it on lcd screen. And then press ( # ) to confirm the OTP.  If the OTP is correct then red LED will glow for some time then the solenoid lock  will be unlocked . And if the OTP is wrong then the lock will remain locked  and the buzzer will beep for 2 seconds .  Once  the otp is used ,then after this that OTP will expire and you will be asked for new OTP for unlocking another time. Now due to some errors like if the device is not pairing with Bluetooth or error in OTP, or any other , there is one more type of security i.e. MASTER CODE , which is a 5 digit no. password  . You can also unlock the system through this password which is a secret code which can be changed if the old password is known . for master code press ( A ) to enter the master code and press  (#) to confirm . If the master code will be entered correctly then the system will be unlocked otherwise it will remain as locked. For changing the master code press ( B ) then it will ask for old password to create a new one . If the old code will be correct then it will ask for the new password two times and then press ( # ) to confirm .



