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

#include <dynamic_reconfigure/DoubleParameter.h>
#include <dynamic_reconfigure/Reconfigure.h>
#include <dynamic_reconfigure/Config.h>
#include <dynamic_reconfigure/server.h>
#include <snake_robot/ParamsConfig.h>


std::vector<double> angles;
std::vector<double> joint_params;
bool use_gui = false;

void alignrobot(std::vector<ros::Publisher> aContainer, std::vector<double> angles) {
  std_msgs::Float64 temp;
  for(int i = 0; i < 15; i++) {
  	temp.data = angles[i];
    aContainer[i].publish(temp);
  }
}
void paramCallback(snake_robot::ParamsConfig &config,uint32_t level)  {
  joint_params.clear();
  joint_params.push_back(config.j_1);
  joint_params.push_back(config.j_2);
  joint_params.push_back(config.j_3);
  joint_params.push_back(config.j_4);
  joint_params.push_back(config.j_5);
  joint_params.push_back(config.j_6);
  joint_params.push_back(config.j_7);
  joint_params.push_back(config.j_8);
  joint_params.push_back(config.j_9);
  joint_params.push_back(config.j_10);
  joint_params.push_back(config.j_11);
  joint_params.push_back(config.j_12);
  joint_params.push_back(config.j_13);
  joint_params.push_back(config.j_14);
  joint_params.push_back(config.j_15);
  //usleep(1231231);
  ROS_DEBUG("Params are updated in scoring Node.");
  use_gui = config.use_gui;
}



void resetSnake(std::vector<ros::Publisher> aContainer)  {
  ros::Rate resetRate(100);
  int myCount = 100;
  std::vector<double> stepsizes;
  for(int i=0; i<15; i++)
  	stepsizes.push_back(angles[i]/myCount);
  for(int i=0; i<myCount; i++) {
  	angles[0] = angles[0] - stepsizes[0];
  	angles[1] = angles[1] - stepsizes[1];
  	angles[2] = angles[2] - stepsizes[2];
  	angles[3] = angles[3] - stepsizes[3];
  	angles[4] = angles[4] - stepsizes[4];
  	angles[5] = angles[5] - stepsizes[5];
  	angles[6] = angles[6] - stepsizes[6];
  	angles[7] = angles[7] - stepsizes[7];
  	angles[8] = angles[8] - stepsizes[8];
  	angles[9] = angles[9] - stepsizes[9];
  	angles[10] = angles[10] - stepsizes[10];
  	angles[11] = angles[11] - stepsizes[11];
  	angles[12] = angles[12] - stepsizes[12];
  	angles[13] = angles[13] - stepsizes[13];
  	angles[14] = angles[14] - stepsizes[14];
  	alignrobot(aContainer,angles);
  	resetRate.sleep();
  	ros::spinOnce();
  }
}

void moveWithGui(std::vector<ros::Publisher> aContainer)  {
  ros::Rate resetRate(100);
  int myCount = 100;
  std::vector<double> stepsizes;
  for(int i=0; i<15; i++)
  	stepsizes.push_back((-joint_params[i]+angles[i])/myCount);
  for(int i=0; i<myCount; i++) {
  	angles[0] = angles[0] - stepsizes[0];
  	angles[1] = angles[1] - stepsizes[1];
  	angles[2] = angles[2] - stepsizes[2];
  	angles[3] = angles[3] - stepsizes[3];
  	angles[4] = angles[4] - stepsizes[4];
  	angles[5] = angles[5] - stepsizes[5];
  	angles[6] = angles[6] - stepsizes[6];
  	angles[7] = angles[7] - stepsizes[7];
  	angles[8] = angles[8] - stepsizes[8];
  	angles[9] = angles[9] - stepsizes[9];
  	angles[10] = angles[10] - stepsizes[10];
  	angles[11] = angles[11] - stepsizes[11];
  	angles[12] = angles[12] - stepsizes[12];
  	angles[13] = angles[13] - stepsizes[13];
  	angles[14] = angles[14] - stepsizes[14];
  	alignrobot(aContainer,angles);
  	resetRate.sleep();
  	ros::spinOnce();
  }
}


void moveForward(std::vector<ros::Publisher> aContainer) {
  ros::Rate extractRate(100);
  ros::Rate pushRate(100);
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

void initSnake(std::vector<ros::Publisher> aContainer)  {
  ros::Rate extractRate(1000);
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
}

void moveForward2(std::vector<ros::Publisher> aContainer) {
  //std::vector<double> angles;
  ros::Rate extractRate(1000);
  ros::Rate pushRate(1000);
  int myCount = 100;
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
  	angles[0] = angles[0] - (0.015);
  	angles[2] = angles[2] + (0.015);
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
  	angles[0] = angles[0] - (0.015);
  	angles[2] = angles[2] + (0.015);
  	angles[4] = angles[4] + (0.015);
  	angles[6] = angles[6] - (0.015);
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
  	angles[4] = angles[4] + (0.015);
  	angles[6] = angles[6] - (0.015);
  	angles[8] = angles[8] - (0.015);
  	angles[10] = angles[10] + (0.015);
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
  	angles[8] = angles[8] - (0.015);
  	angles[10] = angles[10] + (0.015);
  	angles[12] = angles[12] + (0.015);
  	angles[14] = angles[14] - (0.015);
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
  	angles[12] = angles[12] + (0.015);
  	angles[14] = angles[14] - (0.015);
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
  	angles[0] = angles[0] + (0.015);
  	angles[2] = angles[2] - (0.015);
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
  	angles[0] = angles[0] + (0.015);
  	angles[2] = angles[2] - (0.015);
  	angles[4] = angles[4] - (0.03);
  	angles[6] = angles[6] + (0.03);
  	angles[8] = angles[8] + (0.015);
  	angles[10] = angles[10] - 0.015;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }
    for(int i = 0; i<myCount; i++) {
  	//std::cout<<i<<std::endl;
  	angles[8] = angles[8] + (0.015);
  	angles[10] = angles[10] - 0.015;
  	angles[12] = angles[12] - (0.03);
  	angles[14] = angles[14] + 0.03;
  	alignrobot(aContainer,angles);
  	if(i<myCount)
  	  pushRate.sleep();
  	else
  	  extractRate.sleep();
  	ros::spinOnce();
  }


}



int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_motion_client");

  dynamic_reconfigure::Server<snake_robot::ParamsConfig> server;
  dynamic_reconfigure::Server<snake_robot::ParamsConfig>::CallbackType f;

  f = boost::bind(&paramCallback, _1, _2);
  server.setCallback(f);


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
  ros::Rate speed(4);

  while(joint_params.size()<1)  {
  	ROS_INFO("Waiting for params");
  	speed.sleep();
  	ros::spinOnce();
  }

  for(int i=0; i<15; i++) {
  	angles.push_back(0);
  }
  // moveForward2(pubContainer);
  // while(ros::ok()) {
  // 	int k = 5;
  // }
  initSnake(pubContainer);
  while(ros::ok())  {
  	//moveForward(pubContainer);
  	//speed.sleep();
  	if(!use_gui) {
  	  ros::spinOnce();
  	  moveForward2(pubContainer);
  	  speed.sleep();
  	  ros::spinOnce();
  	  resetSnake(pubContainer);
  	  speed.sleep();
  	  initSnake(pubContainer);
  	}
  	else {
  	  moveWithGui(pubContainer);
  	  ros::spinOnce();
  	  speed.sleep();
  	}

  }

  return 0;
}
