## Description

* `(Todo)` Windows/MacOS port for OLED/Buzzer/keyboard functions.
* The '(include)' folder in the emulator is coded based on CH32V003J4M6 Game console driver and implement it on Windows/MacOS terminal

## Notes

* Disable "Device default effects" before using the `JOY_sound()` function on Windows.
* For MacOS version, there are issues on the `(is_keyboard_pressed())` where it cannot be triggered too fast 
  (ie. do not chain them to run at a time with `if else` statements or `||` operators)