/**
 @page  PWR_STOP example
 @verbatim
  * File   : PWR/STOP/readme.txt
  * Version: V1.3.2
  * Date   : 2021-08-08
  * Brief  : Description of the PWR_STOP mode example.
  ********************************************************************************************
 @endverbatiom

@par Example Desctiption
  This demo is based on the AT-START-F415 board.
  in this demo, shows how to exit stop mode by interrupt of ertc alarm.

  Three leds led2,led3 and led4 are used to monitor the system state as following:
    - led2 on: system in run mode
    - led2 off: system in stop mode
    - led4 is toggled if exti line17(ertc alarm) is used to exit from stop 
 
  */


