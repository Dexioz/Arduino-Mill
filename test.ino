#include <AccelStepper.h>

// Define the pins for the stepper motor driver
#define STEP_PIN 9
#define DIR_PIN 8
#define ENABLE_PIN 10

// Define the pins for the manual encoder
#define ENCODER_A_PIN 2
#define ENCODER_B_PIN 3

// Define the number of steps per revolution for the stepper motor
#define STEPS_PER_REV 200

// Define the number of microsteps per step for the stepper driver
#define MICROSTEPS 1000

// Define the maximum speed and acceleration for the stepper motor
#define MAX_SPEED 5000
#define ACCELERATION 500

// Define the movement scale values for the encoder
#define SCALE_1 1
#define SCALE_2 5
#define SCALE_3 25

// Initialize the stepper motor object
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Initialize variables for the manual encoder
volatile int encoderPosition = 0;
volatile int lastEncoderPosition = 0;
volatile int encoderDirection = 0;
volatile int encoderScale = SCALE_1;

// Interrupt service routine for the manual encoder
void encoderISR() {
  int a = digitalRead(ENCODER_A_PIN);
  int b = digitalRead(ENCODER_B_PIN);
  if (a == b) {
    encoderDirection = 1;
  } else {
    encoderDirection = -1;
  }
}

// Setup function
void setup() {
  // Set up the stepper motor driver pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW);

  // Set up the manual encoder pins
  pinMode(ENCODER_A_PIN, INPUT_PULLUP);
  pinMode(ENCODER_B_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), encoderISR, CHANGE);

  // Set up the serial port
  Serial.begin(9600);

  // Set up the stepper motor object
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(ACCELERATION);

  // Move the stepper motor to the home position
  stepper.moveTo(0);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

// Main loop
void loop() {
  // Check if the encoder direction has changed
  if (encoderDirection != 0) {
    // Calculate the number of steps to move the stepper motor
    int steps = encoderDirection * encoderScale * MICROSTEPS;
    // Move the stepper motor by the calculated number of steps
    stepper.move(steps);
    // Update the last encoder position and direction
    lastEncoderPosition = encoderPosition;
    encoderDirection = 0;
  }

  // Run the stepper motor
  stepper.run();
}
