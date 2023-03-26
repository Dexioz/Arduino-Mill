#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_RA8875.h>
#include <Wire.h>
#include <GSL1680.h>

// RA8875 connections
#define RA8875_INT 4
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
GSL1680 touchscreen = GSL1680();

// Joystick connections
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_Z 2
#define JOYSTICK_SW 3
#define JOYSTICK_DEADZONE 20

// Manual encoders connections
#define ENCODER1_CLK 4
#define ENCODER1_DT 5
#define ENCODER1_SW 6
#define ENCODER2_CLK 7
#define ENCODER2_DT 8
#define ENCODER2_SW 12
#define ENCODER3_CLK 13
#define ENCODER3_DT 22
#define ENCODER3_SW 23

// Emergency stop button connection
#define EMERGENCY_STOP 11

// Stepper motors connections
#define MOTOR1_STEP 24
#define MOTOR1_DIR 25
#define MOTOR2_STEP 26
#define MOTOR2_DIR 27
#define MOTOR3_STEP 28
#define MOTOR3_DIR 29

// Initialize joystick state variables
int joystickX = 0;
int joystickY = 0;
int joystickZ = 0;
int joystickSW = 0;

// Initialize manual encoder state variables
int encoder1Pos = 0;
int encoder2Pos = 0;
int encoder3Pos = 0;
int encoder1Last = 0;
int encoder2Last = 0;
int encoder3Last = 0;
int encoder1Scale = 1;
int encoder2Scale = 1;
int encoder3Scale = 1;


