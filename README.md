# Rock Creek Outdoors - Target System

### Description
This repo contains several target programs that can be run on the Arduino Uno platform. They are designed as a prototype of different target systems that could then be mass produced in an application specific board.

### Tools
We used several tools to create these programs.

* Arduino IDE - http://arduino.cc/en/Main/Software
* Ino, command line Arduino toolkit - https://github.com/amperka/ino
* Fritzing, circuit diagramming tool (uses *.fz files) - http://fritzing.org
* Falstad Circuit Simulator, helpful java applet - http://www.falstad.com/circuit/

## Single Dot Target
### 1 target
This is a target design for a single dot (and single target). It is very basic and to use it you simply shoot the target while the light is on, and don't shoot it when the light is off.

## Follow The Dot Target
### 2 or more targets
This program is designed for the shooter to start in a holstered position and then draw and fire at whichever target is currently lit (do not reholster until completely finished with the drill). Basically, shoot the dot.

## Memory Target
### 3 or more targets
This program is designed to use the shooter's memory to determine which targets to shoot. A pattern will be flashed using the target dots and then an audible buzzer will sound and the shooter should then shoot the pattern they saw into the targets. The buzzer will sound again (if you haven't finished shooting, stop) and the next pattern will be displayed.

## Four Rules Of Gun Safety
1. All guns are always loaded
2. Never point a gun at something you are unwilling to destroy
3. Keep your finger off the trigger until your sights are on the target
4. Be sure of your target (and what's behind it)