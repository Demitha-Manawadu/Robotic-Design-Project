#include "menu.h"
#include <Arduino.h>
#include "OLED_Display.h"
#include "MotorControl.h"
#include "SensorControl.h"
#include "roboArm.h"
#include "OLED_Display.h"
#include "RobotControl.h"
#include "Buzzer.h"
#include "ColorSensor.h"
#include "LineFollowAndTurn.h"
#include "PIDControl.h"
#include "task2.h"
#include "button.h"
#include "coindrop.h"
#include "Barcode.h"
#include "ColorSensor.h"
ColorSensor c1;
// Extern the oled object defined in main.ino
extern OLEDDisplay oled;

// Menu items
static const char* menuItems[] = {
    "Task All",
    "Calibrate sensors",
    "looping",
    "virtual",
    "color",
    "dotted",
    "door",
    "box",
    "chamber",
    "lastone"
 
};
static const int numItems = sizeof(menuItems)/sizeof(menuItems[0]);

// Task structure
typedef struct {
    const char *taskName;
    const char *taskMessage;
} Task;

static Task tasks[] = {
    {"Task One", "Doing Task One Stuff"},
    {"Task Two", "runForwardWithSensorPID"},
    {"Task Three", "Running Task Three"},
    {"Task Four", "This is Task Four"},
    {"Task Five", "Task Five in progress"},
    {"Task Six", "Task Six Doing Its Thing"},
    {"Task Seven", "portal nav"},
    {"Task Eight", "Task Eight Busy..."},
    {"Task Nine", "Ninth Task Rolling"},
    {"Task ten", "Ninth Task Rolling"}
};

// Ensure tasks and items match in count
static_assert(sizeof(tasks)/sizeof(tasks[0]) == sizeof(menuItems)/sizeof(menuItems[0]), "tasks and menuItems size mismatch");

static int currentIndex = 0;
static const int ITEMS_PER_PAGE = 3;
static menu_state_t currentState = MENU_STATE_MAIN;
static int taskIndex = -1;

void menu_init() {
    currentIndex = 0;
    currentState = MENU_STATE_MAIN;
    taskIndex = -1;
}

void menu_update(button_t btn) {
    switch (currentState) {
    case MENU_STATE_MAIN:
        switch(btn) {
            case BTN_FORWARD:
                if (currentIndex > 0) currentIndex--;
                else currentIndex=8;
                break;
            case BTN_BACKWARD:
                if (currentIndex < numItems - 1) currentIndex++;
                else currentIndex=0;
                break;
            case BTN_SELECT:
                // Enter task mode
                taskIndex = currentIndex;
                currentState = MENU_STATE_TASK;
                break;
            case BTN_INTERRUPT:
                // Reset to top of menu
                moveForward(0, 0);
                currentIndex = 0;
                break;
            case BTN_NONE:
            default:
                // no action
                break;
        }
        break;

    case MENU_STATE_TASK:
        if (btn == BTN_INTERRUPT) {
            currentState = MENU_STATE_MAIN;
            currentIndex = 0;
            taskIndex = -1;
        }
        break;
    }
}

void menu_draw() {
    if (currentState == MENU_STATE_MAIN) {
        moveForward(0, 0);
        oled.drawMenu("MENU", menuItems, numItems, currentIndex, ITEMS_PER_PAGE);
    } else if (currentState == MENU_STATE_TASK) {


        if (taskIndex >= 0 && taskIndex < numItems) {
            oled.drawTaskScreen(tasks[taskIndex].taskName, tasks[taskIndex].taskMessage);
        }
        if (taskIndex ==0){
          // turnByAngleWithPID(-90); 
          // delay(1000);
          task_2(2);
          c1.detectColor();
          runForwardWithoutPID(1000);
          followLineAndTurnWithSquareDetection();
          runForwardWithoutPID(1000);
          moveForwardUntilWhiteSquare();
          checkBarrier();
          task6();
          chamber();
          looping();
          currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==1){
          calibrateSensors();
          currentState = MENU_STATE_MAIN;
          //runBackwardWithEncoderPID();
        }
        if (taskIndex ==2){
          
          //moveForwardWithEncoders();
          looping();
          currentState = MENU_STATE_MAIN;
          //runBackwardWithEncoderPID();
        }


        if (taskIndex ==3){
          task_2(3);
          currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==4){
          c1.detectColor();
          followLineAndTurnWithSquareDetection();
          currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==5){
          runForwardWithoutPID(1000);
          moveForwardUntilWhiteSquare();
          currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==6){                 
          checkBarrier();
          currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==7){
          task6();
          currentState = MENU_STATE_MAIN;

        }
        if (taskIndex ==8){
          chamber();
          currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==9){
          liftGripper();
          looping();
          //checkBarrier();
          currentState = MENU_STATE_MAIN;
        }
 
        if (taskIndex ==11){
          leftEncoderCount=0;
          rightEncoderCount=0;
          while(true){
          runBackwardWithEncoderPID();}
          currentState = MENU_STATE_MAIN;
        }
         else {
            oled.drawTaskScreen("Unknown Task", "No Data");
        }
    }
}
