# Description

* Windows/MacOS port for OLED/Buzzer/keyboard functions.
* The '(include)' folder in the Emulator is coded based on CH32V003J4M6 Game console driver and implement it on Windows/MacOS terminal
* 'Emulator' folder is for compiling Windows and MacOs version, '(Game_name)' folder is for compiling the RISC-V version

## Notes

* Highly recommended to use dark theme terminal for best user experience
* Extra functions for Win/MacOS is needed compare to the RISC-V version. However, filler functions has been implemented in the RISC-V driver of this repository. Simply copy the function from the emulator to the RISC-V driver will run fine.
* For Windows, Disable "Device default effects" before using the `JOY_sound()` function.
* For MacOS version, go to settings -> Privacy & Security -> Accessibility and allow terminal/your IDE to control your computer to enable keyboard control (will pop up during first run, need to restart the program after enable)