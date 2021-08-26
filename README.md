# usbtiny-ATtiny2313-upgrade-ISP-modification

usbtiny clone and modify the 6pin ISP header for upgrade firmware


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
