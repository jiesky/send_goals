#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>

#include <fstream>
#include <iostream>

#include "ros/ros.h"  
#include "geometry_msgs/PoseWithCovariance.h"  
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "geometry_msgs/Pose.h"  
#include "geometry_msgs/Point.h"  
#include "geometry_msgs/Quaternion.h"
#include "tf/tf.h"
#include "send_goals/SavePoint.h"

using namespace std;

typedef struct{
  double x;
  double y;
  double yaw;
} Point;
Point p;

ros::Subscriber sub_pose;
ros::ServiceServer save_goals;
//int i=0;

void amclPoseCallback(const geometry_msgs::PoseWithCovarianceStamped& msgPose)
{
	
   p.x=msgPose.pose.pose.position.x;
   p.y=msgPose.pose.pose.position.y;
   p.yaw = tf::getYaw(msgPose.pose.pose.orientation);
}
  
bool saveGoalCallback(send_goals::SavePoint::Request  &req,
                      send_goals::SavePoint::Response &res)
{  
    ofstream outfile("goals.txt",ios::app);//ios::app表示在原文件末尾追加
    if(!outfile){
        cout << "Open the file failure...\n";
        exit(1);
    }
/*    switch(i)
    {
      case 0:outfile <<0.0 << 0.1 << 0.2 << '\n';//向文件写数据
             break;
      case 1:outfile << 1.0 << 1.1 << 1.2 << '\n';//向文件写数据
             break;
      case 2:outfile << 2.0 << 2.1 << 2.2 << '\n';//向文件写数据
             break;
      default:
	     break;
    }
    i++;
*/
    outfile << p.x << ',' << p.y << ',' << p.yaw << '\n';
    
    outfile.close();
  
  return true;  
}
  
int main(int argc, char **argv)  
{  
  ros::init(argc, argv, "save_goals");  
  ros::NodeHandle n;  

  sub_pose=n.subscribe("amcl_pose",1,amclPoseCallback);
  save_goals = n.advertiseService("save_goals", saveGoalCallback);
  ROS_INFO("Ready to save goal.");  
  ros::spin();  
  
  return 0;  
}  
