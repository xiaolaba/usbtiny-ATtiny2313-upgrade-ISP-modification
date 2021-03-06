# usbtiny-ATtiny2313-upgrade-ISP-modification

usbtiny clone and modify the 6pin ISP header for upgrade firmware  


![ISP_upgrade_schematic.JPG](ISP_upgrade_schematic.JPG)  


firmware clone, https://learn.adafruit.com/usbtinyisp/download  
source code clone, https://dicks.home.xs4all.nl/avr/usbtiny/  

### burn.bat
```
:: by xiaolaba, 2021-AUG-10 update, used Microchip tool set after Atmel acquired

:: download https://www.microchip.com/en-us/development-tools-tools-and-software/gcc-compilers-avr-and-arm
:: AVR 8-bit Toolchain v3.62 – Windows
:: installed as,
:: gcc version 5.4.0 (AVR_8_bit_GNU_Toolchain_3.6.2_1778)

:: add tool chain to path
path=%PATH%;C:\avr8-gnu-toolchain-win32_x86\utils\bin;C:\avr8-gnu-toolchain-win32_x86\bin

:: show gcc version 5.4.0 (AVR_8_bit_GNU_Toolchain_3.6.2_1778)
avr-gcc -v


:: clean up old project file
make clean

:: build hex firmware
:: display redirect to file of std, speeding up, no screen showing
make hex >> std

:: use makefile to burn hex
make writeflash

:: remove files after hex build
rm std
rm *.o
rm *.ee.hex
rm *.out
rm *.map

::goto end
:: burn firmware, compile with mega328p
:: 2008-OCT-09
set mcu=attiny2313
set target=main.hex
set lfuse=0xff
set hfuse=0xdf
set efuse=0xff
avrdude -c usbtiny -p %mcu% -U flash:w:%target%:a -U lfuse:w:%lfuse%:m -U hfuse:w:%hfuse%:m -U efuse:w:%efuse%:m

:end
pause
```
  
  
### dump.bat
```
:: by xiaolaba, 2021-AUG-10

:: download https://www.microchip.com/en-us/development-tools-tools-and-software/gcc-compilers-avr-and-arm
:: AVR 8-bit Toolchain v3.62 – Windows
:: installed as,
:: gcc version 5.4.0 (AVR_8_bit_GNU_Toolchain_3.6.2_1778)

:: add tool chain to path
path=%PATH%;C:\avr8-gnu-toolchain-win32_x86\utils\bin;C:\avr8-gnu-toolchain-win32_x86\bin

:: show gcc version 5.4.0 (AVR_8_bit_GNU_Toolchain_3.6.2_1778)
avr-gcc -v


:: clean up old project file
make clean

:: build hex firmware
:: display redirect to file of std, speeding up, no screen showing
make hex >> std

:: use makefile to burn hex
make writeflash

:: remove files after hex build
rm std
rm *.o
rm *.ee.hex
rm *.out
rm *.map

::goto end
:: burn firmware, compile with mega328p
set mcu=attiny2313
::set target=dumpflash.hex
::set lfuse=0xff
::set hfuse=0xdf
avrdude -c usbtiny -p %mcu% -U flash:r:flashdump.hex:i
avrdude -c usbtiny -p %mcu% -U lfuse:r:lfuse.txt:i
avrdude -c usbtiny -p %mcu% -U hfuse:r:hfuse.txt:i
avrdude -c usbtiny -p %mcu% -U efuse:r:efuse.txt:i

:end
pause
```
  
  
### terminal.bat
```
:: by xiaolaba

@echo off
set path=

set mcu=attiny2313
set ac=C:\avr8-gnu-toolchain-win32_x86

path %ac%\bin;%ac%\utils\bin;%path%;

avr-gcc.exe -dumpversion

:::: avrdude terminal only
avrdude -c usbtiny -p %mcu% -t

pause
:end
```

### ISP header heritage
the design was not so good as far as I had found, but it was. change the design a bit, easy for the job, no hardware build but bought some well cloned in the market. [atmel-2521-avr-hardware-design-considerations_applicationnote_avr042.pdf](atmel-2521-avr-hardware-design-considerations_applicationnote_avr042.pdf), page 6 is describing the ISP header for avr8 MCU. SPI interface.  
![avr8_ISP.JPG](avr8_ISP.JPG)  

### the clone modification to match my design of 2008  
removed all junk headers pin, it is prone to bad contact and intermittent loose electrical connection thus weird ISP programming problem, soldering is always own preference, it is being proof since my 1st build prototype and working good so far till today, but not those clone.
![ISP_upgrade_design_mod.JPG](ISP_upgrade_design_mod.JPG)  

### cut 5 traces for modifiaction
![ISP_upgrade_design_cut_5_traces.JPG](ISP_upgrade_design_cut_5_traces.JPG)  

this is original design circuit, copy from internet, 74HC125D is used as buffer
![usbtinyisp2sch.png](usbtinyisp2sch.png)  



### wiring 6 wires to build ISP header to burn Attiny2312
![ISP_upgrade_design_6wiring_mod.JPG](ISP_upgrade_design_6wiring_mod.JPG)  


