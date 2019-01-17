#include <ros/ros.h>
#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <gazebo_msgs/ModelState.h>
#include <gazebo_msgs/GetLinkState.h>
#include <gazebo_msgs/SetLinkState.h>
#include <gazebo_msgs/SetModelConfiguration.h>
#include <sensor_msgs/JointState.h>

#include <cstdlib>


void alignrobot(ros::Publisher joint_pub, std::vector<double> angles) {
  sensor_msgs::JointState myJoints;
  myJoints.header.stamp = ros::Time::now();
  std::vector<std::string> j_names;
  j_names.push_back("joint1");
  j_names.push_back("joint2");
  j_names.push_back("joint3");
  j_names.push_back("joint4");
  j_names.push_back("joint5");
  j_names.push_back("joint6");
  j_names.push_back("joint7");
  j_names.push_back("joint8");
  j_names.push_back("joint9");
  j_names.push_back("joint9");
  myJoints.position = angles;
  joint_pub.publish(myJoints);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_motion_client");


  ros::NodeHandle n;
  
  sensor_msgs::JointState myJoints;
  std::vector<double> angles;

  for(int i=0; i<11; i++) {
    angles.push_back(0);
  }

  ros::service::waitForService("gazebo/get_link_state");
  ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 5);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 5);
  ros::rate myRate(5);
  while(ros::ok())  {

    alignrobot(joint_pub, angles);

  }
  


  return 0;
}
