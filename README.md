# Autonomous Robot for the completion of the tasks for SLRC 2025

This repository contains the code developed for the robot **Hope** developed for **SLRC 2025** organized by the **University of Moratuwa**. The robot was designed to perform a variety of autonomous tasks, including:

- Line following  
- Box manipulation  
- Barcode reading  
- Maze solving
- ball collection
- color detection

The robot was made in 2 versions. 
 -4 wheel omni directional robot
 -2 wheeled robot

Microcontroller - ESP32 Devkit V1
Computer - Raspberry Pi 4
Motors used - JGB 37-520 /N20
Sensor array - Reykha module

---

## Project Highlights

- ✅ Modular object-oriented approach
- ✅ Abstracted `Robot` class to handle core motion and sensor control  
- ✅ Dedicated classes for high-level tasks (e.g., object manipulation, Path navigation)  
- ✅ Background and foreground task separation for concurrent task execution 

---


---

##  Features Implemented

- PID-based line following with calibration
- Grid and node-based maze traversal with direction memory
- Ball detection and color identification
- Basic box pickup and drop-off logic
- Modular task switching and state handling system

---

## Comments
The control profilling was implemented with close relation with ukmars/maze-runner-core 







