#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Bool.h>


#define R_PWM 5
#define R_BACK 3
#define L_BACK 2
#define L_PWM 6
#define DIR_LEFT 2
#define PWM_MIN 50
#define PWMRANGE 255

/* Angular velocity positive (turning counter clock wise) = 2 is high and 3 is low
*/
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
std_msgs::Bool handshake_msg;
ros::Publisher handshake("arduino_nano_handshake", &handshake_msg);

// Map x value from [0 .. 1] to [out_min .. out_max]
float mapPwm(float x, float out_min, float out_max)
{
  return x * (out_max - out_min) + out_min;
}

//this happens when cmd_vel message is recieved
void onTwist(const geometry_msgs::Twist &msg)
{
  digitalWrite(LED_BUILTIN, HIGH);

  // Cap values at [-1 .. 1]
  float x = max(min(msg.linear.x, 1.0f), -1.0f);
  float z = max(min(msg.angular.z, 1.0f), -1.0f);

  // Calculate the intensity of left and right wheels. Simple version.
  // Taken from https://hackernoon.com/unicycle-to-differential-drive-courseras-control-of-mobile-robots-with-ros-and-rosbots-part-2-6d27d15f2010#1e59
  float l = (msg.linear.x - msg.angular.z) / 2;
  float r = (msg.linear.x + msg.angular.z) / 2;

  // Then map those values to PWM intensities. PWMRANGE = full speed, while PWM_MIN = the minimal amount of power at which the motors begin moving.
  uint16_t lPwm = mapPwm(fabs(l), PWM_MIN, PWMRANGE);
  uint16_t rPwm = mapPwm(fabs(r), PWM_MIN, PWMRANGE);

  // Set direction pins and PWM
  digitalWrite(L_BACK, l < 0);
  digitalWrite(R_BACK, r < 0);
  analogWrite(L_PWM, lPwm);
  analogWrite(R_PWM, rPwm);
}

//subscribe to cmd_vel
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &onTwist);

void setup()
{
  pinMode(L_BACK, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  pinMode(L_PWM, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  digitalWrite(L_BACK, 0);
  digitalWrite(R_BACK, 0);
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
  pinMode(LED_BUILTIN, OUTPUT);
  nh.initNode();
  nh.advertise(handshake);
  nh.subscribe(sub);
  //Serial.begin (9600);
}

void loop()
{

  handshake_msg.data = true;
  handshake.publish(&handshake_msg);
  nh.spinOnce();
  delay(10);
}
