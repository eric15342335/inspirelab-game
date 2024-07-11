# InspireLab Game

## Description

This repository discovers extra potential on the CH32V003 RISC-V Game console.
A link to the original repository is below.
<https://github.com/wagiminator/CH32V003-GameConsole>

## How to use

### Snake Game

1. Install MounRiver Studio and add the following to `PATH`:
    * `$(YourInstallDirectory)/MounRiver_Studio/toolchain/RISC-V Embedded GCC 12/bin`
        * For `riscv-none-elf` compiler toolchain
    * `$(YourInstallDirectory)/MounRiver_Studio/toolchain/Build Tools/bin`
        * For `make` tool
2. Open terminal in the corresponding game folder (e.g. `snakegame`)
3. type `make` on the terminal to make the executable for CH32V003
4. flash the hex file into the game console (`CH32V003J4M6`) using WCH-LinkUtility (`Windows` only) or `todo`
5. Have fun!

* Notes:
* the driver in `riscv/include` has been modified (compared to [original implementation]()) to allow direct copy from the emulator to run the RISC-V controller
* buzzer function plays real frequency in Hz

### Emulator

* `Emulator/include` contains a port of the `Snake_Game/include` libraries
which allows code using such libraries to run on desktop platforms for ease of debugging
  * Windows / MacOS are supported
  * See [Emulator/README.md](Emulator/README.md) for more information.

### utility

* Contains an [python script](utility/pixelConvert.py) that faciliates game texture conversion from 128x64 png file to C-array which the OLED monitor accepts

![image](https://github.com/eric15342335/inspirelab-game/assets/70310617/66b99c52-8682-482c-8fdb-ba39357e72e0)


## Links

* Original Repository: <https://github.com/wagiminator/CH32V003-GameConsole>
* WCH-LinkUtility.exe: <https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html>
* MounRiver Studio Installer: <http://www.mounriver.com/download>
