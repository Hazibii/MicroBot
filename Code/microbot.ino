//Build Your Own Robot: MicroBot Version2
// ATTRIBUTION and LICENSE

#include <AFMotor.h> //import your motor shield library
#include <NewPing.h> //import your ultrasonic sensor library 

// motor settings
#define MOTOR_SPEED 200
#define MOTOR_2_PIN 2
#define MOTOR_3_PIN 3

// sonar settings
#define TRIG_PIN A4 // define trigPin to A3 on the Motor Shield
#define ECHO_PIN A5 // define echoPin to A5 on the Motor Shield
#define MAX_DISTANCE 200 //sets maximum useable sensor measuring distance to 200cm
#define DETECT_DISTANCE_MM 250 // 
#define PING_MS_TO_MM = 5.82F // convert ping time to approximate mm distance

// why motor 2 and 3, should they be left and right?
AF_DCMotor motor2(MOTOR_2_PIN, MOTOR12_1KHZ); // set up motor 1
AF_DCMotor motor3(MOTOR_3_PIN, MOTOR12_1KHZ); // set up motor 2
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  //set the speed of the motors, between 0-255
  motor2.setSpeed(MOTOR_SPEED);
  motor3.setSpeed(MOTOR_SPEED);
}

void loop() {
  long duration; // start the scan
  int distanceMM = 0;

can_this_be_replaced_by_a_sonar_call:
  {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2); // delays are required for a succesful sensor operation.

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10); //this delay is required as well!

    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);
  }

  distanceMM = (int)(duration / PING_MS_TO_MM);// convert the distance to ,millimeters.

  //if there's an obstacle 250 mm ahead, do the following:
  if (distanceMM > DETECT_DISTANCE_MM) {
    // Turn as long as there's an obstacle ahead
    motor2.run(FORWARD);
    motor3.run(BACKWARD);

    // alternate avoidance heuristics:
    // * stop one motor,  reverse the other
    // * slow one motor and turn in a curve
    // * etc
  }
  else {
    //if there's no object in front, Go Forward!
    delay (15);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
  }
}
