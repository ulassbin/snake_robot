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


#include <cstdlib>


void alignrobot(ros::ServiceClient aClient,std::vector<double> angles) {
  gazebo_msgs::SetModelConfiguration initConfig;
  std::string base = "joint";
  std::string tempstring;
  initConfig.request.model_name = "snake_robot";
  std::vector< std::basic_string<char>> names;
  //names.push_back(te);
  std::vector<std::string> testingstring;
  for(int i = 0;i < 9; i++) {
  	tempstring = base;
  	tempstring.append(std::to_string(i+1));
  	testingstring.push_back(tempstring);
  }
  std::vector<double> anglealloc;
  ros::service::waitForService("gazebo/set_model_configuration");
  initConfig.request.joint_names = testingstring;
  initConfig.request.joint_positions = angles;
  aClient.call(initConfig);
  return;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "robot_motion_client");


  ros::NodeHandle n;
  gazebo_msgs::GetLinkState base_link_state;
  gazebo_msgs::SetLinkState base_link_new_state;
  gazebo_msgs::SetModelConfiguration jointConfig;
  ros::service::waitForService("gazebo/get_link_state");
  ros::ServiceClient gls_srv = n.serviceClient<gazebo_msgs::GetLinkState>("gazebo/get_link_state");
  ros::ServiceClient sls_srv = n.serviceClient<gazebo_msgs::SetLinkState>("gazebo/set_link_state");
  ros::ServiceClient joint_srv = n.serviceClient<gazebo_msgs::SetModelConfiguration>("gazebo/set_model_configuration");
  ros::Rate myrate(2);
  double xstep = 0.01;

  std::string base = "joint";
  std::string tempstring;
  //Now first align the robot
  std::vector<double> angles;
  for(int i=0;i<9;i++)
  	angles.push_back(0);
  alignrobot(joint_srv,angles);
  while(ros::ok()) {
  	for(int i = 0; i<9; i++)  {
  		angles[i] = angles[i]+0.001;
    }
  	alignrobot(joint_srv,angles);
	base_link_state.request.link_name ="base_link" ;
	base_link_state.request.reference_frame ="link" ;
	if (gls_srv.call(base_link_state)) {
	  ROS_INFO_STREAM(base_link_state.response);
	  if(base_link_state.response.success) {
	    base_link_new_state.request.link_state = base_link_state.response.link_state;
      	base_link_new_state.request.link_state.pose.position.x = base_link_new_state.request.link_state.pose.position.x + xstep;
      }
	} else {
	  continue;
	}
	if(sls_srv.call(base_link_new_state))  {
		ROS_INFO("Success");
	}
    myrate.sleep();
    ros::spinOnce();
  }
  return 0;
}
