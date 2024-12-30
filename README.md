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

### Barcode Detection
- Measures duration exposed to white segments to determine the end of the barcode.

### Box Handling
- Includes height measurement, grabbing, lifting, and placing based on color-coded signals.

### Path Navigation
- Controls the robot’s movement along predefined paths while avoiding obstacles.

##Overall Strategy
The full documentation for the Overall strategy can be found in:



## Specifications
- **Dimensions**: [e.g., 30 cm x 25 cm x 10 cm]
- **Weight**: [e.g., 1.5 kg]
- **Power**: 12V rechargeable battery
- **Speed**: Max speed of 1 m/s
- **Sensor Range**: Ultrasonic sensors up to 400 cm

##Demo



## Task Allocation
Provide an overview of the tasks allocated to different team members. This section can be organized by team member or task type. Example:

- **Team Member 1**: [Name]
  - Tasks: [e.g., designing the chassis, integrating motors, debugging sensor code]

- **Team Member 2**: [Name]
  - Tasks: [e.g., implementing the control algorithm, testing robot behavior]

- **Team Member 3**: [Name]
  - Tasks: [e.g., developing the user interface, working on communication protocols]

