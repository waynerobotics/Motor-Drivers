
#include <ros.h>
#include <geometry_msgs/Twist.h>

#define PWM_RIGHT 5
#define DIR_RIGHT 3
#define PWM_LEFT 6
#define DIR_LEFT 2
#define MIN_PWM 50
#define MAX_PWM 150
void setup() {
  // put your setup code here, to run once:
  pinMode(PWM_RIGHT, OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(PWM_LEFT, OUTPUT);
  pinMode(DIR_LEFT, OUTPUT);
  analogWrite(PWM_LEFT, 255);
  analogWrite(PWM_RIGHT, 255);
  digitalWrite(DIR_LEFT, HIGH);
  digitalWrite(DIR_RIGHT, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
