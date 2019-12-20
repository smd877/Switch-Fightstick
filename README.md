# Auto-Pokemon-Breeder
Forked from [progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick)

[English](./README.md) / [日本語](./README_ja.md)

This tool supports Pokemon selection.  
A total of 30 eggs can be hatched automatically.

## Requirements

### Hardware/Software

- Arduino UNO R3 or see [shinyquagsire23/Switch-Fightstick's README](https://github.com/shinyquagsire23/Switch-Fightstick/blob/master/README.md)
- USB micro-b cable
- Nintendo Switch
- Pokemon Sword and Pokemon Shield

### Item/Pokemon

- Rotom Bike
- Oval Charm
- Pokemon with "Flame Body" (Coalossal, Chandelure, etc.)

## Build

- Build Joystick.hex

   ```sh
   $ sudo apt-get install git make gcc-avr avr-libc
   $ git clone https://github.com/Almtr/Switch-Fightstick.git
   $ cd Switch-Fightstick
   $ git clone https://github.com/abcminiuser/lufa.git
   $ make
   ```

- Write to Arduino UNO R3  
  See [Updating the Atmega8U2 and 16U2 on an Uno or Mega2560 using DFU](https://www.arduino.cc/en/Hacking/DFUProgramming8U2)

## Usage

1. Move "POKEMON" menu icon to the upper left.
1. Disconnect from the Internet.
1. Empty a pokemon box.
1. Have a Pokemon With "Flame Body" (and an egg).
1. Go to Nurserie in Wild Area.
1. Connect Arduino UNO R3 to your Nintendo Switch.

## Demo

[![](https://img.youtube.com/vi/oXnQt_Mbyzk/0.jpg)](https://www.youtube.com/watch?v=oXnQt_Mbyzk)

## (Option) Other Modules

### Loop Tournament Module

  This is a module for automatically circling tournaments.  
  Please compile with "loop-tournament" to use this module.

  ```sh
  $ make clean       # Run this command if Joystick.hex already exists.
  $ make loop-tournament
  ```
  
  Usage:  
  1. Have a Pokemon with one move (e.g. Zacian who only learns "Iron Head").
  1. Go to the reception of Shoot Stadium.
  1. Connect Arduino UNO R3 to your Nintendo Switch.

### Repeat A Module 

  This is a module that repeatedly presses the A button.  
  Please compile with "repeat-a" to use this module.

  ```sh
  $ make clean       # Run this command if Joystick.hex already exists.
  $ make repeat-a
  ```

## References

- [GitHub - progmem/Switch-Fightstick](https://github.com/progmem/Switch-Fightstick)
- [GitHub - shinyquagsire23/Switch-Fightstick](https://github.com/shinyquagsire23/Switch-Fightstick)
- [GitHub - bertrandom/snowball-thrower](https://github.com/bertrandom/snowball-thrower)
- [GitHub - kidGodzilla/woff-grinder](https://github.com/kidGodzilla/woff-grinder)
- [GitHub - ebith/Switch-Fightstick](https://github.com/ebith/Switch-Fightstick)
- [Updating the Atmega8U2 and 16U2 on an Uno or Mega2560 using DFU](https://www.arduino.cc/en/Hacking/DFUProgramming8U2)
