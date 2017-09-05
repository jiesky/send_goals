#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>

#include<stdio.h>
#define N 4
#define M 3

struct Point{
  double x;
  double y;
  double yaw;
} point[N];

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "send_goals");
  MoveBaseClient ac("move_base", true);

  FILE *fp;
  int i = 0,j=0;
  if ( fp=fopen("/home/jie/test_ws/src/send_goals/data.txt","r") )
  { 
    while(3 == fscanf(fp,"%lf,%lf,%lf\n",&point[i].x,&point[i].y,&point[i].yaw))
    {
      i++;
    }
    for(j=0; j<N; j++)
      printf("%lf,%lf,%lf\n",point[j].x,point[j].y,point[j].yaw);
  fclose(fp);
  }

  //tell the action client that we want to spin a thread by default

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  move_base_msgs::MoveBaseGoal goal;
  int q = 0;
  while(ros::ok() && q < 4)
  {
    q++;
  //send goals
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromYaw(point[q].yaw);
    
    goal.target_pose.pose.position.x = point[q].x;
    goal.target_pose.pose.position.y = point[q].y;
    goal.target_pose.pose.position.z = 0.0;
    goal.target_pose.pose.orientation = quat;

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Hooray, the base reached the %d point\n",i);
    else
      ROS_INFO("Hooray, the base failed to reach the %d point for some reason",i);
  }

  return 0;
}
