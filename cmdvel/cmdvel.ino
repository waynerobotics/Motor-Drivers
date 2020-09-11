#include <ros.h>
#include <geometry_msgs/Twist.h>

#define PWM_RIGHT 5
#define DIR_RIGHT 3
#define PWM_LEFT 6
#define DIR_LEFT 2
#define MIN_PWM 50
#define MAX_PWM 150
#define KP 238 //proportional multiplier - adjust as needed. PWM = KP*cmd_vel.linear.x + PWM_MIN
#define KA 100 //this was a guess.. adjust as needed for turning responsiveness

//left and right offset are a crude way of making robot drive straight
//without feedback if robot turns right instead of going straight, increase left offset
//if robot turns left instead of going straight, increase right offset
#define LEFT_OFFSET 0
#define RIGHT_OFFSET 0

ros::NodeHandle nh;

geometry_msgs::Twist cmd_msg;
ros::Publisher chatter("test_cmd", &cmd_msg);

//this happens when cmd_vel message is recieved
void messageCb(const geometry_msgs::Twist& cmdVel)
{
  //Serial.println(cmdVel.angular.z );
  //nh.loginfo(cmdVel.angular.z );
  //set direction pins - switch the 1's and 0's if results are backwards on actual motors
  //chatter.publish(&cmdVel);
  //digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(DIR_LEFT, HIGH);
  digitalWrite(DIR_RIGHT, LOW);
  analogWrite(PWM_LEFT, 255);
  analogWrite(PWM_RIGHT, 255);
  delay(10);
//  if (cmdVel.linear.x > 0) // going forward
//  {
//    digitalWrite(DIR_LEFT, 1);
//    digitalWrite(DIR_RIGHT, 1);  if (cmdVel.linear.x > 0) // going forward
//  {
//    digitalWrite(DIR_LEFT, 1);
//    digitalWrite(DIR_RIGHT, 1);
//  }
//  else if (cmdVel.linear.x < 0) //going reverse
//  {
//    digitalWrite(DIR_LEFT, 0);
//    digitalWrite(DIR_RIGHT, 0);
//  }
//  else if (cmdVel.linear.x == 0 && cmdVel.angular.z > 0) //pivot to the left
//  {
//    digitalWrite(DIR_LEFT, 0);
//    digitalWrite(DIR_RIGHT, 1);
//  }
//  else //pivot to the right
//  {
//    digitalWrite(DIR_LEFT, 1);
//    digitalWrite(DIR_RIGHT, 0);
//  }
//
//  //set initial PWM values - start them equal according to linear.x
//  int leftPwmReq = KP * cmdVel.linear.x + MIN_PWM - LEFT_OFFSET;
//  int rightPwmReq = KP * cmdVel.linear.x + MIN_PWM - RIGHT_OFFSET;
//  //to turn, we simply slow one of them down by a multiplier of the angular .z
//  if (cmdVel.angular.z > 0) //turning to the left
//  {
//    leftPwmReq -= abs(cmdVel.linear.x * KA);
//  }
//  else if (cmdVel.angular.z < 0) //turning to the right by slowing right motor
//  {
//    rightPwmReq -= abs(cmdVel.linear.x * KA);
//  }
//
//  //ensure values at or below maximum allowable
//  leftPwmReq = (leftPwmReq > MAX_PWM) ? MAX_PWM : leftPwmReq;
//  rightPwmReq = (rightPwmReq > MAX_PWM) ? MAX_PWM : rightPwmReq;
//  }
//  else if (cmdVel.linear.x < 0) //going reverse
//  {
//    digitalWrite(DIR_LEFT, 0);
//    digitalWrite(DIR_RIGHT, 0);
//  }
//  else if (cmdVel.linear.x == 0 && cmdVel.angular.z > 0) //pivot to the left
//  {
//    digitalWrite(DIR_LEFT, 0);
//    digitalWrite(DIR_RIGHT, 1);
//  }
//  else //pivot to the right
//  {
//    digitalWrite(DIR_LEFT, 1);
//    digitalWrite(DIR_RIGHT, 0);
//  }
//
//  //set initial PWM values - start them equal according to linear.x
//  int leftPwmReq = KP * cmdVel.linear.x + MIN_PWM - LEFT_OFFSET;
//  int rightPwmReq = KP * cmdVel.linear.x + MIN_PWM - RIGHT_OFFSET;
//  //to turn, we simply slow one of them down by a multiplier of the angular .z
//  if (cmdVel.angular.z > 0) //turning to the left
//  {
//    leftPwmReq -= abs(cmdVel.linear.x * KA);
//  }
//  else if (cmdVel.angular.z < 0) //turning to the right by slowing right motor
//  {
//    rightPwmReq -= abs(cmdVel.linear.x * KA);
//  }
//
//  //ensure values at or below maximum allowable
//  leftPwmReq = (leftPwmReq > MAX_PWM) ? MAX_PWM : leftPwmReq;
//  rightPwmReq = (rightPwmReq > MAX_PWM) ? MAX_PWM : rightPwmReq;

  //actually output pwm values
  //  analogWrite(PWM_LEFT, leftPwmReq);
  //  analogWrite(PWM_RIGHT, rightPwmReq);

}

//subscribe to cmd_vel
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);

void setup()
{
  pinMode(PWM_RIGHT, OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(PWM_LEFT, OUTPUT);
  pinMode(DIR_LEFT, OUTPUT);
  analogWrite(PWM_LEFT, 0);
  analogWrite(PWM_RIGHT, 0);
  digitalWrite(DIR_LEFT, 0);
  digitalWrite(DIR_RIGHT, 0);
  pinMode(LED_BUILTIN, OUTPUT);
  //  analogWrite(PWM_LEFT, 255);
  //  analogWrite(PWM_RIGHT, 255);
  //  digitalWrite(DIR_LEFT, HIGH);
  //  digitalWrite(DIR_RIGHT, LOW);
  //nh.getHardware->setBaud(115200);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
  //Serial.begin (9600);
}

void loop()
{

  nh.spinOnce();
  delay(10);
}
