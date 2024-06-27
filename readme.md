# InspireLab Game

## Description

This repository discovers extra potential on the CH32V003 RISC-V Game console.
A link to the original repository is below.
<https://github.com/wagiminator/CH32V003-GameConsole>

## How to use

1. Install MounRiver Studio and add the following to `PATH`:
    * `$(YourInstallDirectory)/MounRiver_Studio/toolchain/RISC-V Embedded GCC 12/bin`
        * For `risc-none-embed-` compiler toolchain
    * `$(YourInstallDirectory)/MounRiver_Studio/toolchain/Build Tools/bin`
        * For `make` tool
2. Open terminal in the corresponding game folder (e.g. `Snake_Game`)
3. type `make hex` on the terminal to make the executable
4. flash the hex file into the game console (`CH32V003J4M6`) using WCH-LinkUtility (`Windows` only) or `todo`
5. Have fun!

## Links

* Original Repository: <https://github.com/wagiminator/CH32V003-GameConsole>
* WCH-LinkUtility.exe: <https://www.wch.cn/downloads/WCH-LinkUtility_ZIP.html>
* MounRiver Studio Installer: <http://www.mounriver.com/download>
