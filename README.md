This repository contains *all* the code developed for the rv-ecu project. So
far, this includes - 

+ can-bridge: An MDK-ARM project for the STM3210C-Eval boards that writes over
  the CAN port, for use in reverse engineering  
+ utils: Currently contains a frame decoder that takes logs of car CAN activity
  and finds the frames that most likely cause a given action. The frame decoder
  also generates C code that can be included in can-bridge to write these frames
+ logs: contains logs of car activity used to reverse engineer functionality.
  Included for the purposes of reproducibility. 

My workflow for reverse engineering is as follows - 

1. Hook up the USB-CANII tool to the CAN wires in the driver window controller
   in Grigore's minivan (see Mitchell wiring diagram)
2. In the USB-CANII GUI tool select 'Save Real Time', start the car, and wait
   for a few minutes. Then turn the car off. Save this log as 'idle.txt'
3. Do the same as above, but instead of waiting, use the component whose traffic
   you want to reverse engineer. 
4. Use `FrameDecoder.py` with the `-c` option and pipe the output to
   `can-bridge/Project/src`. Open `main.c` in that directory and #include the
    text file you just generated at the bottom of the main function.
5. Flash the board, hook it up to the CAN wires, and hit 'reset'

Maybe the CANbus Triple we bought will make this easier, but for now, this is
how we will create the demo.
