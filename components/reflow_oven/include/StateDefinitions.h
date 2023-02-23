#include <stdint.h>
#include "../include/PID.h"


typedef enum REFLOW_STATE{

REFLOW_STATE_IDLE,
REFLOW_STATE_PREHEAT,
REFLOW_STATE_SOAK,
REFLOW_STATE_REFLOW,
REFLOW_STATE_COOL,
REFLOW_STATE_COMPLETE,
REFLOW_STATE_TOO_HOT,
REFLOW_STATE_ERROR

} reflow_state_t;

typedef enum REFLOW_STATUS{

REFLOW_STATUS_OFF,
REFLOW_STATUS_ON

}reflow_status_t;

typedef enum SWITCH{

SWITCH_NONE,
SWITCH_1,
SWITCH_2

}switch_t;

typedef enum DEBOUNCE_STATE {

DEBOUNCE_STATE_IDLE,
DEBOUNCE_STATE_CHECK,
DEBOUNCE_STATE_RELEASE

}debounce_state_t;

typedef enum REFLOW_PROFILE{

 REFLOW_PROFILE_LEADFREE,
 REFLOW_PROFILE_LEADED

}reflow_profile_t;

// ***** CONSTANTS *****
// ***** GENERAL *****
#define VERSION 2 // Replace with 1 or 2

// ***** GENERAL PROFILE CONSTANTS *****
#define PROFILE_TYPE_ADDRESS 0
#define TEMPERATURE_ROOM 50
#define TEMPERATURE_SOAK_MIN 150
#define TEMPERATURE_COOL_MIN 100
#define SENSOR_SAMPLING_TIME 1000
#define SOAK_TEMPERATURE_STEP 5

// ***** LEAD FREE PROFILE CONSTANTS *****
#define TEMPERATURE_SOAK_MAX_LF 200
#define TEMPERATURE_REFLOW_MAX_LF 250
#define SOAK_MICRO_PERIOD_LF 9000

// ***** LEADED PROFILE CONSTANTS *****
#define TEMPERATURE_SOAK_MAX_PB 180
#define TEMPERATURE_REFLOW_MAX_PB 224
#define SOAK_MICRO_PERIOD_PB 10000

// ***** SWITCH SPECIFIC CONSTANTS *****
#define DEBOUNCE_PERIOD_MIN 100

// ***** DISPLAY SPECIFIC CONSTANTS *****
#define UPDATE_RATE 100

// ***** PID PARAMETERS *****
// ***** PRE-HEAT STAGE *****
#define PID_KP_PREHEAT 100
#define PID_KI_PREHEAT 0.025
#define PID_KD_PREHEAT 20
// ***** SOAKING STAGE *****
#define PID_KP_SOAK 300
#define PID_KI_SOAK 0.05
#define PID_KD_SOAK 250
// ***** REFLOW STAGE *****
#define PID_KP_REFLOW 300
#define PID_KI_REFLOW 0.05
#define PID_KD_REFLOW 350
#define PID_SAMPLE_TIME 1000

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define X_AXIS_START 18 // X-axis starting position

// ***** LCD MESSAGES *****
const char* lcd_messages_reflow_status[] = {
  "idle",
  "pre",
  "soak",
  "reflow",
  "cool",
  "finished",
  "cooling(hot)",
  "error"
};

/*
// ***** DEGREE SYMBOL FOR LCD *****
unsigned char degree[8]  = {
  140, 146, 146, 140, 128, 128, 128, 128
};
*/


//set all pins to corresponding stm pins
// ***** PIN ASSIGNMENT *****
//uint8_t ssrPin = A0; //set this to stm analog pin 0
//uint8_t fanPin = A1; //set this stm analog pin 1
uint8_t thermocoupleCSPin = 10;
uint8_t ledPin = 4;
uint8_t buzzerPin = 5;
uint8_t switchStartStopPin = 3;
uint8_t switchLfPbPin = 2;

// ***** PID CONTROL VARIABLES *****
double setpoint = 0;
double input = 0;
double output = 0;
double kp = PID_KP_PREHEAT;
double ki = PID_KI_PREHEAT;
double kd = PID_KD_PREHEAT;
int32_t window_size;
uint64_t window_start_time;
uint64_t next_check;
uint64_t next_read;
uint64_t update_lcd;
uint64_t timer_soak;
uint64_t buzzer_period;
uint8_t soak_temperature_max;
uint8_t reflow_temperature_max;
uint64_t soak_micro_period;
uint64_t current_time;

// Reflow oven controller state machine state variable
reflow_state_t ReflowState;
// Reflow oven controller status
reflow_status_t ReflowStatus;
// Reflow profile type
reflow_profile_t ReflowProfile;
// Switch debounce state machine state variable
debounce_state_t debounceState;
// Switch debounce timer
int64_t lastDebounceTime;
// Switch press status
switch_t switchStatus;
switch_t switchValue;
switch_t switchMask;
// Seconds timer
uint32_t timer_update;
uint32_t timer_seconds;
// Thermocouple fault status
uint8_t fault;
uint8_t temperature[SCREEN_WIDTH - X_AXIS_START];
uint8_t x;
