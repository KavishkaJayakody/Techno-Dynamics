/*tasks.h = header file for all the tasks in SLRC 2025.
last updated on 5/4/2025 (Nilakna)*/

#ifndef TASKS_H
#define TASKS_H

// #include <Arduino.h>
#include "robot.h"
#include "encoders.h"
#include "raspi.h"
#include <vector>
#include "sensors.h"

# define GOOD 1
# define BAD 0

class Tasks; // Forward declaration of the tasks class

extern Tasks tasks; // Declare the tasks object

class Tasks
{
public:
    // robotigation robot; // robotigation object
    // encodersoders encoders; // encodersoders object
    // raspi raspi; // Raspberry Pi object
    // tasks(); // Constructor with robotigation object;
    bool task1(); // IMPLEMENTED
    bool task2(); // IMPLEMENTED
    bool task3(); // IMPLEMENTED
    bool task4(); // returns end position of the robot facing task 5.
    float task4temp(); // returns end position of the robot facing task 5.
    bool task5();
    bool task6(); // IMPLEMENTED

    bool task2nodist(); // just in case...

private:
    // task 2
    bool task2_done = false; // Flag to indicate if task 2 is done
    bool goodRed = false; // Flag to indicate if the red box is good
    bool armHasBox = false; // Flag to indicate if the arm has a box
};

// FINAL FINAL SIDE OF THE CAM - RIGHT SIDE

bool Tasks::task1()
{   
    int potatoJuncs = 0;
    bool potatoFound = false;

    robot.move_till_junction(1000); // Pass the first junction
    robot.move_till_junction(1000); // Stop at second junction
    robot.turn(RIGHT);

    // iterate through first 3 rows on right.
    for (int junc = 0; junc < 5; junc++) {
        // reset values
        potatoJuncs = 0;
        potatoFound = false;
        // Serial.println("Junction= " + String(junc)); // Debugging line
        
        // move to the potato
        while(!potatoFound && (potatoJuncs < 3)) { // Continue moving until a potato is found or 2 junctions are crossed
            // move till potatoFound 
            // Serial.println("PotatoFound= " + String(potatoFound) + " PotatoJunctions= " + String(potatoJuncs)); // Debugging line
            sensors.led_indicator(true);
            potatoFound = robot.move_till_potato(1000); // Move until a potato is detected. false if junction.
            sensors.led_indicator(false);
            if (!potatoFound) {
                potatoJuncs++; // Increment the junction count if a junction is found
            } else {
                break;
            }
        } 

        // take the potato
        // raspi.takeRightPotato(); // Ask the Raspberry Pi to take the potato
        
        if (junc >= 3) {
            // at the last junction we continue till the end of the field
            for (int rest = 0; rest < 3 - potatoJuncs; rest++) {
                robot.move_till_junction(1000); // Move until a junction is found
            }
            if (junc == 3) {
                robot.turn(ABOUTTURN); // about turn to return
            } else {
                robot.turn(RIGHT); // turn right
                break;
            }
            continue; // continue to the next row (return side)
        }


        // move back to the row start
        robot.turn(ABOUTTURN); // about turn to return
        for (int i = 0; i < potatoJuncs; i++) {
            robot.move_till_junction(350); // Move back the distance came in.
        }
        robot.turn(RIGHT);

        // move to the next row
        robot.move_till_junction(1000); // Move to the next row junction
        robot.turn(RIGHT); // Turn 90 degrees clockwise
    }
    
    // go to the start of task 2
    robot.move_till_junction(1000); // Move until a junction is found
    return true; // Return true to indicate task 1 is done
}

bool Tasks::task2()
{
    bool wallDone = false;
    float side = 1; // right line (should turn left)
    
    float startDist = encoders.robotDistance(); // Get the initial distance from the encodersoders
    float turnDist = 0; // Initialize the end distance
    float tempDist; // Initialize the temporary distance
    float task2Dist = 0; // Initialize the task 2 distance

    robot.move_straight(150); // Move straight for 150 mm
    robot.turn(RIGHT); // Turn 90 degrees clockwise

    // WITH DISTANCE MEASUREMENT BUT CANNOT CHECK TASK 2 END =(. NOW CAN. YAY.
    while (!wallDone) {
        
        // MOVE TILL THE RIGHT WALL
        task2Dist = encoders.robotDistance() - startDist - turnDist; // Calculate the distance travelled

        wallDone = robot.move_till_wall_task2(task2Dist); // Move straight until wall or line is found
        if (wallDone) {
            break;
        }
        


        // CHANGE TO LEFT SIDE

        // if (foundWall) {
        // turn left
        robot.turn(90); // Turn 90 degrees anticlockwise 
        
        //  move forward
        tempDist = encoders.robotDistance();
        robot.move_straight(300); // Move straight for 150 mm
        turnDist = turnDist + (encoders.robotDistance() - tempDist);
        
        //turn right to original direction
        robot.turn(RIGHT); // Turn 90 degrees clockwise
        

        

        // MOVE TILL THE LEFT WALL
        task2Dist = encoders.robotDistance() - startDist - turnDist; // Calculate the distance travelled

        wallDone = robot.move_till_wall_task2(task2Dist); // Move straight until wall or line is found
        if (wallDone) {
            side = -1; // Set wall to true
            break; // Exit the loop if task 2 is done
        }



        // CHANGE TO RIGHT SIDE
        // turn right
        robot.turn(RIGHT); // Turn 90 degrees clockwise
        
        // move forward
        tempDist = encoders.robotDistance();
        robot.move_straight(300); // Move straight for 150 mm
        turnDist = turnDist + encoders.robotDistance() - tempDist;
        
        // turn left to original direction
        robot.turn(LEFT); // Turn 90 degrees clockwise
        // }
    }

    // LETS GO RAMP!!!!

    // turn right if on left line.
    // robot.turn((float)90*side); // Turn 90 degrees clockwise if on left line
    if (side==1){
        robot.turn(LEFT); // Turn 90 degrees clockwise if on left line
    } else {
        robot.turn(RIGHT); // Turn 90 degrees clockwise if on right line
    }
    robot.move_straight(150); // Move straight for 150 mm
    // robot.turn((float)(-90)*side);
    if (side==1){
        robot.turn(RIGHT); // Turn 90 degrees clockwise if on left line
    } else {
        robot.turn(LEFT); // Turn 90 degrees clockwise if on right line
    }
    // robot.move_till_line(); 
    robot.move_till_wall(1500); // Move straight until wall is found
    task2_done = true; // Set task 2 done to true

    return task2_done; // Return the task 2 status
}


// bool tasks::task2nodist()
// {
//     // Task 2 implementation without distance measurement
//     robot.move_straight(150); // Move straight for 150 mm
//     robot.turn(-90); // Turn 90 degrees clockwise
//     bool foundLine = false; // Initialize foundLine to false

//     while (!task2_done) {
//         // CANNOT FIND TASK 2 DONEEEEEEEEEEEEEEEEEEEEEE
//         foundLine = robot.move_till_wallorLine(); // Move straight until wall or line is found
//         if (!foundLine) {
//             // turn left
//             robot.turn(90); // Turn 90 degrees anticlockwise 
//             //  move forward
//             robot.move_straight(300); // Move straight for 150 mm
//             //turn right to original direction
//             robot.turn(-90); // Turn 90 degrees clockwise
//             // move again till left wall found
//             foundLine = robot.move_till_wallorLine();
//             if (!foundLine) {
//                 task2_done = true; // Set task 2 done to true
//                 break; // Exit the loop if task 2 is done
//             }
//             // turn right
//             robot.turn(-90); // Turn 90 degrees clockwise
//             // move forward
//             robot.move_straight(300); // Move straight for 150 mm
//             // turn left to original direction
//             robot.turn(90); // Turn 90 degrees clockwise
//         }
//         if (!foundLine) {
//             task2_done = true; // Set task 2 done to true
//             break; // Exit the loop if task 2 is done
//         }
//     }
//     return task2_done; // Return the task 2 status
// }


bool Tasks::task3()
{   
    // READ APRILTAG
    // robot start facing the wall
    // robot.move_straight(-150); // Move back to make space to turn if move till wall doesnt handle this.
    robot.turn(RIGHT);
    robot.move_till_wall(2000);
    robot.turn(RIGHT); // Turn 90 degrees clockwise
    robot.move_till_line(1500);
    robot.move_straight(-50); // Move straight for 150 mm
    robot.turn(LEFT);
    robot.move_till_potato(700); // align also // potato = sign board
    // robot.move_straight(-150);
    // robot.move_straight(0); // Move straight for 150 mm
    // robot.turn(RIGHT);
    goodRed = raspi.isRedGood(); // ask raspberry to find tag


    // BASKETING POTATOES 

    // go to the basket and find colour
    robot.move_straight(-300); // reverse to the first basket
    // robot.turn(-90);
    // robot.move_till_line(500); // align also
    // // robot.move_straight(300);
    // robot.move_straight(-150);
    // robot.turn(90); // turn towards the basket to read 
    bool redBox = raspi.findBoxColour(); // ask raspberry to find box color. true if red, false if blue

    // turn rear to put the potatoes
    robot.turn(LEFT);
    robot.move_straight(-50);
    
    bool openGood = false;

    if ((goodRed && redBox)||(!goodRed && !redBox)) {
        raspi.openGate(GOOD); //ASK OSHANI ABOUT SERVO CONTROLLING
        openGood = true;
    } else {
        // goodRed && !redBox || !goodRed && redBox
        raspi.openGate(BAD);
    }

    // go to the next basket
    robot.move_straight(50);
    robot.turn(RIGHT);
    // robot.move_till_line(1500); // and align
    // robot.move_straight(-150); // move towards the box
    // robot.turn(90); // turn rear towards the box
    // robot.move_straight(-50); // move a bit back to align with the box
    robot.move_till_junction(1500); // Move to side line of task 4 and align.
    robot.move_straight(-150); // move towards the box
    robot.turn(LEFT); // turn rear towards the box
    robot.move_straight(-50); // move a bit back to align with the box

    // put the other set of potatoes
    if (openGood) {
        raspi.openGate(BAD);
    } else { 
        raspi.openGate(GOOD);
    }

    // go to the start of task4
    robot.move_straight(50);
    robot.turn(RIGHT);
    robot.move_till_line(350); // go to side line of task 4 and align.

    return true; // Return true to indicate task 3 is done
}

bool Tasks::task4() {
    // this is like a sliding block puzzle. we need to find the best path to the good box.
    std::vector<std::vector<int>> boxColors = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}}; // Initialize the box array
    bool tempColor = -1; // set all to white
    float endPos = 0;
    bool tookGood = false;
    float goodLocation = -1;
    // FIND BOXES AND BOX COLORS

    // we go to the middle and look around =)

    while(!tookGood) {
        /////////////////////////////   STEP 0  //////////////////////
        // check the nearest box (0,1)
        robot.turn(LEFT);
        boxColors[0][1] = raspi.findBoxColour();
        if (boxColors[0][1] == 1 && goodRed || boxColors[0][1] == 0 && !goodRed) {
            // if good box is found, take it and break the loop.
            raspi.takeRightBox(); // ask raspberry to take the box 
            tookGood = true; // we have found the good box
            armHasBox = true; 
            boxColors[0][1] == -1; // set to empty
            break; // box found on (1,1) position
        }


        /////////////////////////////   STEP 1  //////////////////////
        // if good box is not found and bad box is found, take it and move to that location.
        if (boxColors[0][1] != -1) {
            raspi.takeRightBox(); // take the bad box
            armHasBox = true; // bad box in the arm
            // boxColors[0][1] == -1; // set to empty
        }
        robot.turn(RIGHT);
        robot.move_straight(150); // move to the white box
        
        // now we talking

        // we look around from the (0,1) position
        std::vector<int> u = {0,1,1,1,0};
        std::vector<int> v = {2,2,1,0,0};
        // std::vector<int> emp = {};
        for (int k = 0; k < 5; k++) {
            boxColors[u[k]][v[k]] = raspi.findBoxColour(); // ask raspberry to find box color. true (1) if red. false (0) if blue
            
            // save the good box location. cannot take because arm might have a box.
            if (boxColors[u[k]][v[k]] == 1 && goodRed || boxColors[u[k]][v[k]] == 0 && !goodRed) {
                goodLocation = k; // save the location of the good box
            }
            
            if (k<4) {
                robot.turn(LEFTQTR);
            }

            // if we find an empty box and if arm still has a box, place it there.
            if (armHasBox && boxColors[u[k]][v[k]] == -1){
                // keep the box there. if none are empty, no box was there.
                robot.turn(RIGHT);
                // move to the box
                if (k % 2 == 0) {
                    robot.move_straight(150); // move to the next box
                } else {
                    robot.move_straight(200); // move back to the previous box
                }
                // place the box
                raspi.placeFrontBox();
                boxColors[u[k]][v[k]] = boxColors[0][1]; // set the box color to the one we have
                boxColors[0][1] == -1; // set to empty
                // move back
                armHasBox = false; // we have placed the box
                if (k % 2 == 0) {
                    robot.move_straight(-150); // move to the next box
                } else {
                    robot.move_straight(-200); // move back to the previous box
                }
                robot.turn(LEFT);
            }
        }

        // we have looked around and might have found a good box.
        // now we align again.
        robot.move_till_junction(1000); // move to side of task 4 and align
        robot.turn(ABOUTTURN);
        robot.move_straight(150); // move to the (0,1) position facing (1,1)

        // if we have found a good box in last round, take it and go.
        if (goodLocation != -1) {
            if (goodLocation == 0) {
                robot.turn(RIGHT);
                robot.move_straight(150);
            } else if (goodLocation == 1) {
                robot.turn(RIGHTQTR);
                robot.move_straight(200);
            } else if (goodLocation == 3) {
                robot.turn(LEFTQTR);
                robot.move_straight(200);
            } else if (goodLocation == 4) {
                robot.turn(LEFT);
                robot.move_straight(150);
            }

            raspi.takeFrontBox(); // ask raspberry to take the box
            tookGood = true; // we have found the good box
            armHasBox = true; // we have found the good box

            if (goodLocation == 0) {
                robot.move_straight(-150);
                robot.turn(LEFT);
            } else if (goodLocation == 1) {
                robot.move_straight(-200);
                robot.turn(LEFTQTR);
            } else if (goodLocation == 3) {
                robot.move_straight(-200);
                robot.turn(RIGHTQTR);
            } else if (goodLocation == 4) {
                robot.move_straight(-150);
                robot.turn(RIGHT);
            }

            // we collected the good box from set 1. now return to end position.
            robot.turn(ABOUTTURN); // turn to the right
            robot.move_till_junction(1000);
            robot.turn(RIGHT); // turn to the right
            break; // box found on (0,2), (1,2), (1,1), (1,0), (0,0)
        }

        /////////////////////////////   STEP 2  //////////////////////

        // we didnt find a good box in the last round. we are at (0,1) now.
        // so move to the next box(1,1) which we already checked.  
        // if (1,1) has a box, take it and go to (1,2)
        if (boxColors[1][1] != -1) {
            robot.move_straight(150); // move to the next box (1,1)
            raspi.takeFrontBox(); // take the bad box
            armHasBox = true; // bad box in the arm
            robot.move_straight(150);
        } else {
            robot.move_straight(300);
        }

        // now we are at (1,1) facing (2,1)
        // we look around from the (0,1) position
        for (int k = 0; k < 3; k++) {
            robot.turn(LEFTQTR); // turn to the left
            boxColors[2][2-k] = raspi.findBoxColour(); // ask raspberry to find box color. true (1) if red. false (0) if blue
            
            // save the good box location. cannot take because arm might have a box.
            if (boxColors[2][2-k] == 1 && goodRed || boxColors[2][2-k] == 0 && !goodRed) {
                goodLocation = k; // save the location of the good box
            }
        }

        // if we find an empty box and if arm still has a box, place it there except on (0,1)
        if (armHasBox){
            if (boxColors[2][1] == -1) {
                robot.move_straight(150); // move to the next box (2,1)
                raspi.placeFrontBox(); // place the box
                robot.move_straight(-150); // move back to the previous box (1,1)
                armHasBox = false; // we have placed the box
            }
            else if (boxColors[2][2] == -1) {
                robot.turn(RIGHTQTR); // turn to the right
                robot.move_straight(200); // move to the next box (2,1)
                raspi.placeFrontBox(); // place the box
                robot.move_straight(-200); // move back to the previous box (1,1)
                robot.turn(LEFTQTR); // turn to the left
                armHasBox = false; // we have placed the box
            } 
            else if (boxColors[2][0] == -1) {
                robot.turn(LEFTQTR); // turn to the right
                robot.move_straight(200); // move to the next box (2,1)
                raspi.placeFrontBox(); // place the box
                robot.move_straight(-200); // move back to the previous box (1,1)
                robot.turn(RIGHTQTR); // turn to the left
                armHasBox = false; // we have placed the box
            }
            else if (boxColors[1][2] == -1) {
                robot.turn(RIGHT); // turn to the right
                robot.move_straight(200); // move to the next box (2,1)
                raspi.placeFrontBox(); // place the box
                robot.move_straight(-200); // move back to the previous box (1,1)
                robot.turn(LEFT); // turn to the left
                armHasBox = false; // we have placed the box
            } 
            else if (boxColors[1][0] == -1) {
                robot.turn(LEFT); // turn to the right
                robot.move_straight(200); // move to the next box (2,1)
                raspi.placeFrontBox(); // place the box
                robot.move_straight(-200); // move back to the previous box (1,1)
                robot.turn(RIGHT); // turn to the left
                armHasBox = false; // we have placed the box
            } else if (boxColors[0][2] == -1) {
                robot.turn(RIGHT3QTR); // turn to the right
                robot.move_straight(200); // move to the next box (2,1)
                raspi.placeFrontBox(); // place the box
                robot.move_straight(-200); // move back to the previous box (1,1)
                robot.turn(LEFT3QTR); // turn to the left
                armHasBox = false; // we have placed the box
            }
        }

        // now arm is free. take the good box.
        if (goodLocation != -1) {
            if (goodLocation == 2) {
                robot.move_straight(200); // move to the next box (2,0)
            } else if (goodLocation == 1) {
                robot.turn(RIGHTQTR);
                robot.move_straight(150); // move to the next box (2,1)
            } else if (goodLocation == 2) {
                robot.turn(RIGHTQTR);
                robot.move_straight(200); // move to the next box (2,2)
            }
            
            raspi.takeFrontBox(); // ask raspberry to take the box
            tookGood = true; // we have found the good box
            armHasBox = true; // we have found the good box

            if (goodLocation == 2) {
                robot.move_straight(-200); // move to the next box (2,0)
                robot.turn(RIGHTQTR);
            } else if (goodLocation == 1) {
                robot.move_straight(-150); // move to the next box (2,1)
            } else if (goodLocation == 2) {
                robot.move_straight(-200); // move to the next box (2,2)
                robot.turn(LEFTQTR);
            }

            robot.turn(ABOUTTURN); // turn to the right
            robot.move_till_junction(1500); // move to side of task 4 and align
            robot.turn(RIGHT); // turn to the right

            break; // box found on (0,2), (1,2), (1,1), (1,0), (0,0)
        }

        robot.move_straight(150); // move to the next box (1,2)
        // if all five are filled then 0,1 is empty for sure.
    }

    // if box is there take it and go to (0,1)
    if (tookGood){
        return true;
    }
    return false; // return the end position of the robot facing task 5
}

float Tasks::task4temp()
{
    // this is like a sliding block puzzle. we need to find the best path to the good box.
    std::vector<std::vector<int>> boxColors = {{-1,-1,-1}, {-1,-1,-1}, {-1,-1,-1}}; // Initialize the box array
    bool tempColor = -1; // set all to white
    float endPos = 0;
    // FIND BOXES AND BOX COLORS

    // we go to the middle and look around =)

    // check the nearest box (0,1)
    robot.turn(LEFT);
    boxColors[0][1] = raspi.findBoxColour();

    // take the box if found
    if (boxColors[0][1] == 1 && goodRed || boxColors[0][1] == 0 && !goodRed) {
        raspi.takeRightBox(); // ask raspberry to take the box
        robot.move_till_line(1000); // move forward untill the line
        robot.turn(RIGHT);
        robot.move_straight(150); // move back a bit
        robot.turn(LEFT); // turn to the left
        robot.move_till_line(1000); // move forward untill the line
        endPos = 0;
        return endPos; // we have found the good box
    }

    // go to the start of task 4 (0,0)
    robot.move_till_junction(800); // Move until a junction is found
    robot.turn(RIGHT); // Turn 90 degrees clockwise

    // find colors of edge boxes. (0,0) (1,0) (2,0)
    for (int i = 0; i < 3; i++) {
        robot.move_straight(150);
        boxColors[i][0] = raspi.findBoxColour(); // ask raspberry to find box color. true (1) if red. false (0) if blue
        
        // bring the box if found
        if (boxColors[i][0] == 1 && goodRed || boxColors[i][0] == 0 && !goodRed) {
            raspi.takeRightBox(); // ask raspberry to take the box
            robot.turn(LEFT); // turn to the left
            robot.move_till_line(1000); // move forward untill the line
            endPos = i;
            return endPos; // we have found the good box
        }
        
        // break if the last box.
        if (i == 2) break; // break if last box
        robot.move_straight(150); // otherwise move to the next box
    }  

    // go to (2,0) and check (1,1) and (2,1)
    // if (2,0) is empty, just go. if not, take box and go.
    if (boxColors[2][0] != -1) {
        // if not empty, take the box and go to (2,1)
        raspi.takeRightBox(); // ask raspberry to take the box
    }
    robot.turn(RIGHT); // turn to the right
    robot.move_straight(150); // move to the next box (2,1)
    robot.turn(LEFTQTR);
    boxColors[1][1] = raspi.findBoxColour(); // ask raspberry to find box color. true (1) if red. false (0) if blue
    robot.turn(LEFTQTR); // turn back to the right
    boxColors[2][1] = raspi.findBoxColour(); // ask raspberry to find box color. true (1) if red. false (0) if blue

    // FIND ThE BEST POSSIBLE PATH

    // GO TO THE GOOD BOX AND TAKE IT
    raspi.takeRightBox();
    return true; // Return true to indicate task 4 is done
}

bool Tasks::task5()
{
    // Task 5 implementation
    return true; // Return true to indicate task 5 is done
}

bool Tasks::task6()
{
    int dry = 0; // Initialize dry to false
    float startDist;
    float tempDist;
    int drypot;

    // iterate through all 3 boxes
    for (int pot = 0; pot < 3; pot++) {
        robot.move_till_potato(1000); // move untill a box is found
        robot.turn(LEFT); // turn to the left
        startDist = encoders.robotDistance(); // Get the initial distance from the encodersoders
        robot.move_till_line(1000);
        tempDist = encoders.robotDistance() - startDist; // Calculate the distance travelled
        dry = raspi.detectDryPot();
        if (dry) {
            raspi.ledOn(); // turn on the LED
            int drypot = pot; // Set the drypot to the current potato number
            // break; // if using break, dont use drypot
        }
        robot.turn(ABOUTTURN);
        robot.move(tempDist); // move back to the box
        robot.turn(LEFT); // turn to the left
    }

    // go to the well and take water
    robot.turn(ABOUTTURN);
    robot.move_till_potato(500); // move forward untill the water box
    robot.move_till_potato(500); // move forward untill the water box
    robot.turn(LEFT);
    robot.move_till_line(1000); // move forward untill the line
    raspi.takeWater(); // ask raspberry to take the water
    robot.move_straight(-50); // move back a bit
    robot.turn(ABOUTTURN);

    // water the dry potatoes
    robot.move_till_line(1000); // go infront of the middle potato
    robot.move_straight(-50); // move back a bit
    
    // // nice code but cannot use =(
    // robot.turn((float)(1-drypot)*90); //turn to the line of the drypot
    // robot.move_till_line(400);
    // robot.turn((float)(drypot-1)*90); // turn to the drypot
    // robot.move_till_line(400); // move forward untill the line

    if (drypot == 0) {
        robot.turn(LEFT); // turn to the left
        robot.move_till_line(400);
    } else if (drypot == 2) {
        robot.turn(RIGHT); // turn to the right
        robot.move_till_line(400);
    }
    if (drypot == 0) {
        robot.turn(RIGHT); // turn to the left
        robot.move_till_line(400);
    } else if (drypot == 2) {
        robot.turn(LEFT); // turn to the right
        robot.move_till_line(400);
    }
    raspi.waterPot(); // ask raspberry to water the potato

    // now tasks are finished
    raspi.ledOn(); 
    raspi.playStarman();

    // YAYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY!!!!!!!!!!!!!!!!!!!!
    return true; // Return true to indicate task 6 is done
}


#endif // TASKS_H


