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
#include <std_msgs/Float64.h>

#include <cstdlib>

std::vector<double> angles;

void alignrobot(std::vector<ros::Publisher> aContainer, std::vector<double> angles) {
  std_msgs::Float64 temp;
  for(int i = 0; i < 15; i++) {
  	temp.data = angles[i];
    aContainer[i].publish(temp);
  }
}

void moveForward(std::vector<ros::Publisher> aContainer) {
  ros::Rate extractRate(100);
  ros::Rate pushRate(300);
  int myCount = 150;
  for(int i = 0; i<myCount; i++) {
  	angles[1] = 0.001*i;
  	angles[5] = -0.001*i;
  	angles[9] = 0.002*i;
  	angles[13] = -0.003*i;

  	alignrobot(aContainer,angles);
  	extractRate.sleep();
  	ros::spinOnce();
  }


  for(int i = 0; i<myCount*2; i++) {
  	angles[1] = 0.001*myCount - 0.001*i;
  	angles[5] = -0.001*myCount + 0.001*i;
  	angles[9] = 0.002*myCount - 0.002*i;
  	angles[13] = -0.003*myCount + 0.003*i;

  	alignrobot(aContainer,angles);
  	if(i<myCount)
  		pushRate.sleep();
  	else
  		extractRate.sleep();
  	ros::spinOnce();
  }
   for(int i = 0; i<myCount; i++) {
  	angles[1] = -0.001*myCount + 0.001*i;
  	angles[5] = +0.001*myCount - 0.001*i;
  	angles[9] = -0.002*myCount + 0.002*i;
  	angles[13] = 0.003*myCount - 0.003*i;

  	alignrobot(aContainer,angles);
  	pushRate.sleep();
  	ros::spinOnce();
  }

}

void moveForward2(std::vector<ros::Publisher> aContainer) {
  //std::vector<double> angles;
  ros::Rate extractRate(1000);
  ros::Rate pushRate(3000);
  int myCount = 1507;
  for(int i = 0; i<myCount; i++) {
  	angles[0] = 0.001*i;
  	angles[2] = -0.001*i;
  	angles[4] = -0.001*i;
  	angles[6] =	0.001*i;
  	angles[8] = 0.001*i;
  	angles[10] = -0.001*i;
  	angles[12] = -0.001*i;
  	angles[14] = 0.001*i;
  	alignrobot(aContainer,angles);
  	extractRate.sleep();
  	ros::spinOnce();
  }
  // for(int i = 0; i < myCount; i++)  {
  // 	angles[0] = myCount*0.001-0.001*i;
  // 	angles[2] = -myCount*0.001+0.001*i;
  // 	angles[4] = -myCount*0.001+0.001*i;
  // 	angles[6] = myCount*0.001-0.001*i;
  // 	// if(j == 2) {
  // 	//     angles[6] = myCount*0.001-0.001*i;
  // 	//     angles[8] = myCount*0.001-0.001*i;
  // 	//   }
  // 	//   if(j == 3) {
  // 	//     angles[10] = -myCount*0.001+0.001*i;
  // 	//     angles[12] = -myCount*0.001+0.001*i;
  // 	//   }
  // 	//   if(j == 4)
  // 	//     angles[14] = myCount*0.001-0.001*i;
  // 	alignrobot(aContainer,angles);
  // 	if(i<myCount)
  // 	  pushRate.sleep();
  // 	else
  // 	  extractRate.sleep();
  // 	ros::spinOnce();
  // }
  // for(int i=0; i<15;i++)  {
  // 	std::cout<<"Angle "<<i<<" is "<<angles[i]<<std::endl;
  	
  // }
  // std::cout<<"myCount is "<<myCount<<std::endl;
  // int tempval;

  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	angles[0] = angles[0] - (0.001);
  	angles[2] = angles[2] + (0.001);
  	//angles[8] = 10.001*myCount-0.001*i;
  	// angles[8] = 0.001*myCount-0.001*i;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }

  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	angles[0] = angles[0] - (0.001);
  	angles[2] = angles[2] + (0.001);
  	angles[4] = angles[4] + (0.001);
  	angles[6] = angles[6] - (0.001);
  	//angles[8] = 10.001*myCount-0.001*i;
  	// angles[8] = 0.001*myCount-0.001*i;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }
  
  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	//angles[0] = angles[0] - (0.001);
  	//angles[2] = angles[2] + (0.001);
  	angles[4] = angles[4] + (0.001);
  	angles[6] = angles[6] - (0.001);
  	angles[8] = angles[8] - (0.001);
  	angles[10] = angles[10] + (0.001);
  	//angles[8] = 10.001*myCount-0.001*i;
  	// angles[8] = 0.001*myCount-0.001*i;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }
  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	//angles[0] = angles[0] - (0.001);
  	//angles[2] = angles[2] + (0.001);
  	angles[8] = angles[8] - (0.001);
  	angles[10] = angles[10] + (0.001);
  	angles[12] = angles[12] + (0.001);
  	angles[14] = angles[14] - (0.001);
  	//angles[8] = 10.001*myCount-0.001*i;
  	// angles[8] = 0.001*myCount-0.001*i;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }

  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	//angles[0] = angles[0] - (0.001);
  	//angles[2] = angles[2] + (0.001);
  	angles[12] = angles[12] + (0.001);
  	angles[14] = angles[14] - (0.001);
  	//angles[8] = 10.001*myCount-0.001*i;
  	// angles[8] = 0.001*myCount-0.001*i;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }

  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	angles[0] = angles[0] + (0.001);
  	angles[2] = angles[2] - (0.001);
  	//angles[12] = angles[12] + (0.001);
  	//angles[14] = angles[14] - (0.001);
  	//angles[8] = 10.001*myCount-0.001*i;
  	// angles[8] = 0.001*myCount-0.001*i;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }
  for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	angles[0] = angles[0] + (0.001);
  	angles[2] = angles[2] - (0.001);
  	angles[4] = angles[4] - (0.002);
  	angles[6] = angles[6] + (0.002);
  	angles[8] = angles[8] + (0.001);
  	angles[10] = angles[10] - 0.001;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }
    for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	angles[8] = angles[8] + (0.001);
  	angles[10] = angles[10] - 0.001;
  	angles[12] = angles[12] - (0.002);
  	angles[14] = angles[14] + 0.002;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }

 //  for(int i = 0; i < myCount; i++)  {
 //  	angles[0] = +0.001*i;
 //  	angles[2] = -0.001*i;
 //  	angles[4] = -myCount*0.001+0.001*i;
	// angles[6] = myCount*0.001-0.001*i;
 //  	// if(j == 2) {
 //  	//     angles[6] = myCount*0.001-0.001*i;
 //  	//     angles[8] = myCount*0.001-0.001*i;
 //  	//   }
 //  	//   if(j == 3) {
 //  	//     angles[10] = -myCount*0.001+0.001*i;
 //  	//     angles[12] = -myCount*0.001+0.001*i;
 //  	//   }
 //  	//   if(j == 4)
 //  	//     angles[14] = myCount*0.001-0.001*i;
 //  	alignrobot(aContainer,angles);
 //  	if(i<myCount)
 //  	  pushRate.sleep();
 //  	else
 //  	  extractRate.sleep();
 //  	ros::spinOnce();
 //  }

  // for(int i = 0; i<myCount*2; i++) {
  // 	angles[0] = 0.0;
  // 	angles[8] = -0.001*myCount + 0.001*i;
  // 	angles[10] = 0.001*myCount - 0.001*i;
  // 	angles[14] = -0.0;

  // 	alignrobot(aContainer,angles);
  // 	if(i<myCount)
  // 		pushRate.sleep();
  // 	else
  // 		extractRate.sleep();
  // 	ros::spinOnce();
  // }
  //  for(int i = 0; i<myCount; i++) {
  // 	angles[0] = -0.0;
  // 	angles[8] = +0.001*myCount - 0.001*i;
  // 	angles[10] = -0.001*myCount + 0.001*i;
  // 	angles[14] = 0.0;
  // 	alignrobot(aContainer,angles);
  // 	pushRate.sleep();
  // 	ros::spinOnce();
  // }

}



int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_motion_client");


  ros::NodeHandle n;

  ros::Publisher pub1 = n.advertise<std_msgs::Float64> ("snake_robot/joint1_control/command", 5);
  ros::Publisher pub2 = n.advertise<std_msgs::Float64> ("snake_robot/joint2_control/command", 5);
  ros::Publisher pub3 = n.advertise<std_msgs::Float64> ("snake_robot/joint3_control/command", 5);
  ros::Publisher pub4 = n.advertise<std_msgs::Float64> ("snake_robot/joint4_control/command", 5);
  ros::Publisher pub5 = n.advertise<std_msgs::Float64> ("snake_robot/joint5_control/command", 5);
  ros::Publisher pub6 = n.advertise<std_msgs::Float64> ("snake_robot/joint6_control/command", 5);
  ros::Publisher pub7 = n.advertise<std_msgs::Float64> ("snake_robot/joint7_control/command", 5);
  ros::Publisher pub8 = n.advertise<std_msgs::Float64> ("snake_robot/joint8_control/command", 5);
  ros::Publisher pub9 = n.advertise<std_msgs::Float64> ("snake_robot/joint9_control/command", 5);
  ros::Publisher pub10 = n.advertise<std_msgs::Float64> ("snake_robot/joint10_control/command", 5);
  ros::Publisher pub11 = n.advertise<std_msgs::Float64> ("snake_robot/joint11_control/command", 5);
  ros::Publisher pub12 = n.advertise<std_msgs::Float64> ("snake_robot/joint12_control/command", 5);
  ros::Publisher pub13 = n.advertise<std_msgs::Float64> ("snake_robot/joint13_control/command", 5);
  ros::Publisher pub14 = n.advertise<std_msgs::Float64> ("snake_robot/joint14_control/command", 5);
  ros::Publisher pub15 = n.advertise<std_msgs::Float64> ("snake_robot/joint15_control/command", 5);

  std::vector<ros::Publisher> pubContainer;
  pubContainer.push_back(pub1);
  pubContainer.push_back(pub2);
  pubContainer.push_back(pub3);
  pubContainer.push_back(pub4);
  pubContainer.push_back(pub5);
  pubContainer.push_back(pub6);
  pubContainer.push_back(pub7);
  pubContainer.push_back(pub8);
  pubContainer.push_back(pub9);
  pubContainer.push_back(pub10);
  pubContainer.push_back(pub11);
  pubContainer.push_back(pub12);
  pubContainer.push_back(pub13);
  pubContainer.push_back(pub14);
  pubContainer.push_back(pub15);
  ros::Rate speed(2);
  for(int i=0; i<15; i++) {
  	angles.push_back(0);
  }
  // moveForward2(pubContainer);
  // while(ros::ok()) {
  // 	int k = 5;
  // }
  while(ros::ok())  {
  	//moveForward(pubContainer);
  	//speed.sleep();
  	ros::spinOnce();
  	moveForward2(pubContainer);
  	speed.sleep();
  	ros::spinOnce();
  }

  return 0;
}
