#include "menu.h"
#include <Arduino.h>
#include "OLED_Display.h"
#include "MotorControl.h"
#include "SensorControl.h"
#include "AdvancedMotorControl.h"
#include "MovementControl.h"
#include "OLED_Display.h"
#include "BarcodeDetection.h"
#include "Buzzer.h"
#include "ColorSensor.h"
#include "LineFollowAndTurn.h"
#include "task2.h"
#include "button.h"

// Extern the oled object defined in main.ino
extern OLEDDisplay oled;

// Menu items
static const char* menuItems[] = {
    "Item One",
    "Item Two",
    "Item Three",
    "Item Four",
    "Item Five",
    "Item Six",
    "Item Seven",
    "Item Eight",
    "Item Nine"
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
    {"Task Seven", "Working on Task Seven"},
    {"Task Eight", "Task Eight Busy..."},
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
        if (taskIndex ==1){
          runForwardWithSensorPID();
        }
        if (taskIndex ==2){
          runBackwardWithEncoderPID();
        }
        if (taskIndex ==3){
          turnByAngleWithPID(90);
          currentState = MENU_STATE_MAIN;

        }
        if (taskIndex ==4){
        task_2();
        currentState = MENU_STATE_MAIN;
        }

         else {
            oled.drawTaskScreen("Unknown Task", "No Data");
        }
    }
}
