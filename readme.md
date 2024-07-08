# InspireLab Game

## Description

This repository discovers extra potential on the CH32V003 RISC-V Game console.
A link to the original repository is below.
<https://github.com/wagiminator/CH32V003-GameConsole>

## How to use

### Snake_Game

1. Install MounRiver Studio and add the following to `PATH`:
    * `$(YourInstallDirectory)/MounRiver_Studio/toolchain/RISC-V Embedded GCC 12/bin`
        * For `riscv-none-elf` compiler toolchain
    * `$(YourInstallDirectory)/MounRiver_Studio/toolchain/Build Tools/bin`
        * For `make` tool
2. Open terminal in the corresponding game folder (e.g. `Snake_Game`)
3. type `make hex` on the terminal to make the executable
4. flash the hex file into the game console (`CH32V003J4M6`) using WCH-LinkUtility (`Windows` only) or `todo`
5. Have fun!

### Emulator

* `Emulator/include` contains a port of the `Snake_Game/include` libraries
which allows code using such libraries to run on desktop platforms for ease of debugging
  * Currently only Windows are supported
  * See [Emulator/README.md](Emulator/README.md) for more information.

### utility

* Contains an [python script](utility/pixelConvert.py) that faciliates game texture conversion from 128x64 png file to C-array which the OLED monitor accepts

## Links

* Original Repository: <https://github.com/wagiminator/CH32V003-GameConsole>
* WCH-LinkUtility.exe: <https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html>
* MounRiver Studio Installer: <http://www.mounriver.com/download>
