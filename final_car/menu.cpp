#include "menu.h"
#include <Arduino.h>
#include "OLED_Display.h"
#include "MotorControl.h"
#include "SensorControl.h"
#include "OLED_Display.h"
#include "Buzzer.h"
#include "ColorSensor.h"
#include "LineFollowAndTurn.h"
#include "task2.h"
#include "button.h"
#include "PIDControl.h"
// Extern the oled object defined in main.ino
extern OLEDDisplay oled;

// Menu items
static const char* menuItems[] = {
    "tasK_1",
    "task_2",
    "task_3",
    "task_4",
    "task_5",
    "task_6",
    "task_7",
    "task_8",
    "task_all",
    "task_HIDDEN",
    "task__",
    "task__",
    "task__",
};
static const int numItems = sizeof(menuItems)/sizeof(menuItems[0]);

// Task structure
typedef struct {
    const char *taskName;
    const char *taskMessage;
} Task;

static Task tasks[] = {
    {"Task One", "detectBarcode"},
    {"Task Two", "Virtual_box"},
    {"Task Three", "Color_line_following"},
    {"Task Four", "dotted_line_following"},
    {"Task Five", "task_2()"},
    {"Task Six", "Task Six Doing Its Thing"},
    {"Task Seven", "Working on Task Seven"},
    {"Task Eight", "Task Eight Busy..."},
    {"Task Nine", "Ninth Task Rolling"},
    {"Task Nine", "Ninth Task Rolling"},
    {"Task Nine", "Ninth Task Rolling"},
    {"Task Nine", "Ninth Task Rolling"},
    {"Task Nine", "Ninth Task Rolling"}
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
                else currentIndex=12;
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
          //detectBarcode();
        }
        if (taskIndex ==1){
        task_2();
        currentState = MENU_STATE_MAIN;
        }
        if (taskIndex ==2){
          //runForwardWithSensorPID();
        }
        if (taskIndex ==3){
          runForwardWithSensorPID();
          //currentState = MENU_STATE_MAIN;

        }
        if (taskIndex ==4){
          followLineAndTurnWithSquareDetection();}
        

        if (taskIndex ==5){
          //runBackwardWithEncoderPID();
        }
         else {
            oled.drawTaskScreen("Unknown Task", "No Data");
        }
    }
}
