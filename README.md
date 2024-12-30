# Robotic Design Project - Multi-Task Robot EN2533

## project overview 
This project is focused on designing and building a robot capable of performing various tasks in an autonomous environment. The robot is equipped with sensors and actuators to handle tasks such as bar counting, line navigation, maze navigation, box manipulation, and more. This robot is designed for use in the EN2533 - Robot Design and Competition module and follows a modular design approach to handle different tasks sequentially.

![WhatsApp Image 2024-12-21 at 21 46 30_15445ea4](https://github.com/user-attachments/assets/7a56f363-59bf-4437-a68b-79eaba67c594)



## Features

- 🚗 **Line Navigation:** Navigate predefined paths using IR sensor arrays and color sensors.
- 🔢 **Bar Counting:** Detect and count horizontal bars placed along a predefined path.
- 🧭 **Maze Navigation:** Grab a virtual box and navigate through a maze to place it in the target location.
- 🤖 **Box Arrangement:** Arrange a set of boxes in ascending or descending order of height using a custom SolidWorks-designed mechanical robot arm powered by servo motors. A Sharp IR sensor integrated into the robotic gripper allows for height differentiation.
- 🌈 **Color Line Following:** Follow a colored line on the ground using color sensors.
- 📏 **Dashed Line Following:** Follow a dashed line using the IR sensors.
- 🚪 **Portal Navigation:** Detect and navigate through portals or gateways.
- 🕵️‍♂️ **Hidden Task and Chamber Insertion:** Solve a hidden task and insert a box inside a chamber.
- 🪙 **Coin Drop:** Drop a coin into a specific target area.

## Task-2024
The full Task Documentation can be found in:
[Task 2024 v1.1](https://online.uom.lk/mod/resource/view.php?id=432368)

![image](https://github.com/user-attachments/assets/4f7ffe4b-5368-4e45-8c46-ff8df11e428c)



## Design Overview

### Hardware requirements:
Sensors

The robot employs various sensors for accurate detection and navigation, including:

- **Ultrasonic Sensors:** Employed for detecting walls and chambers.
- **Sharp IR Sensor:** Mounted on top for measuring distance, especially during portal navigation and for box height differentiation.
- **TCS34725 Color Sensor:** Used for color detection in line following tasks.
- **REKHA TCRT5000 Reflectance Sensor Array:** For precise line tracking.

 **Actuators**
- Robotic arm and gripper: Gripper mechanism and slider operations for lifting boxes are performed using two MG90S servo motors.

**JGA25-370 DC motor**
- integrated to the wheels of the robot.

 **Microcontrollers**
- Arduino Mega 2560- The microcontroller that controls all the functionalities of the robot



### Mechanical Design

The mechanical design of the robot was fully customized using SolidWorks, encompassing both the chassis and the robotic arm. The robotic arm, equipped with a gripper, utilizes a rack-and-pinion mechanism for precise linear movement, enabling efficient box grabbing, lifting, and dropping operations.

The chassis features a two-layer acrylic board structure, mounted with spacers for stability. This compact design was carefully crafted to optimize space and ensure the robot can effectively carry out its tasks.
![WhatsApp Image 2024-12-29 at 15 23 47_e17c57a6](https://github.com/user-attachments/assets/486dd6bb-67a7-4aad-bec2-bbbca92b563e)

![WhatsApp Image 2024-12-29 at 15 19 25_0207914a](https://github.com/user-attachments/assets/3f2d229a-93eb-4e14-bb0d-99c6b06aea9a)

![WhatsApp Image 2024-12-29 at 15 19 25_487d0368](https://github.com/user-attachments/assets/ad90bc2f-506b-4973-aa41-bd4042350150)

## Algorithms

The robot’s navigation algorithms rely on real-time data from the sensors. Each task follows a defined sequence, enabling the robot to adapt its actions based on sensor inputs. The algorithms include:

###task 01
###Counting and Line Navigation
The robot will travel along a straight path at a steady pace, guided by encoder feedback. As it encounters a barcode, it will measure the duration that the central IR sensor is exposed to white segments. This duration will be compared to a predetermined threshold, and if it exceeds the threshold, the value 1 will be recorded; otherwise, 0 will be stored. The robot will continue this detection process until three consecutive 0s are detected, indicating the end of the barcode.

###task 02
###Virtual Box Movement
If the Output is 0: The robot approaches the virtual box, grabs it, and moves forward to place it at a specific location. 

The robot identifies which of the two squares (blue or red) is free from gate, grabs the box, and navigates through the maze, ensuring it places the box at the appropriate location.

Movements are carefully controlled accoriding to the given constraints. The optimal path will be hardcoded and the encoders and sensor array with PD will be used for correct navigation.


###task 03
###Color line following
We use the TCS34725 color sensor alongside the REKHA TCRT5000 reflectance sensor array for accurate tracking. 

First, we calibrate the REKHA array to differentiate between the line and the background. The TCS34725 is calibrated to detect the hue of the colored line and this value will be stored for the future use in task 6.

The REKHA array keeps the robot centered on the path, while the TCS34725 verifies it's following the correct color.


###task 04
###Dotted Line Navigation
The robot follows a white dashed line using an 8-IR sensor array, dynamically adjusting its speed based on sensor input.

It maintains a forward stare when detecting black, and upon detecting the white line, it follows the path accordingly.

The robot stops when all sensors detect the white line simultaneously, signaling the end of the dashed line segment

###task 05
###Portal Navigation
For portal navigation, the ToF sensor is mounted on top of the robot (which we are going to use for height mesuring), continuously reading the distance to the gate. 

As the gate is opening and the distance starts to decrease, the robot uses this data to determine when to move forward. 
The frequent readings from the ToF sensor allow the system to  passes through the gate without collision. 
And for more accuracy we will use the ultrasonic sensor reading which is mounted in front of the robot as an additional data whether there is no obstacle in front of it.

###task 06
###Box Arrangement
When robot moves near to boxes it measures the height of each box using sharp IR sensor which is attached to the up down mechanism of the robot arm. It can differenciate the heights of 5,10,15 boxes.

Then accoring to the paths we define robot will grab the each box and place them according to the ascending or descending order depending on the colour it detected.


###task 07
###Hidden Task and Chamber Insertion
The line following robot will navigate along a the path and grab the box at stage 7 using the gripper, an ultra sonic sensor will detect the chamber and the robot will stop precisely right infront of it, release the box, will close the gripper and push the box inside the chamber using the closed gripper.

### task 08
### Coin Drop and Task Completion
The robot will move in the uneven terrain and detect walls using an ultra sonic sensor and move while avoiding the walls, until a black cross is detected to the IR sensor array.

once a cross is detected the robot will and the coin will be released on the cross using a sliding mechanism thats inbuilt in to the chassis of the robot


##Demo



## Task Allocation
Provide an overview of the tasks allocated to different team members. This section can be organized by team member or task type. Example:

- **Team Member 1**: [Eshan S.G.S 220148G]
  - Tasks: [Task 2,Coding for Line following ,Implement the alogorithm for maze solving,Task 8,Testing robot behavior,coding for task 3,and 4]

- **Team Member 2**: [Manawadu M.D-220381M]
  - Tasks: [task 6,task 7,Desinging the robot arm and chasis,implement the alogorithm for box arrangement,mounting the robot mechanism]

- **Team Member 3**: [Wickramasinghe S.D-220701X]
  - Tasks: [task 1,Power circuit designing and soldering,Assembling the robot ,Testing the robot behavior]
  - 
- **Team Member 4**: [Gunasekara V.G.V-220193M]
  - Tasks: [Solidworks drawing for robot arm and chisis,Coding for task 6 and 7,assembling the robot arm]
 
- **Team Member 5**: [Ravishan B.B.N-220533H]
   - Tasks: [task 5,circuit designing and robot assembling,Testing the robot behavior]
