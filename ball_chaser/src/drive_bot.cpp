#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include "geometry_msgs/Twist.h"


class Pub_service
{
private:
	ros::ServiceServer service;
	ros::Publisher motor_pub;

public:
	Pub_service(ros::NodeHandle &n)
		{
			motor_pub=n.advertise<geometry_msgs::Twist>("/cmd_vel",10);
			service=n.advertiseService("/ball_chaser/command_robot",&Pub_service::MoveRobot,this);
		}

	bool MoveRobot(ball_chaser::DriveToTarget::Request &req, ball_chaser::DriveToTarget::Response &res)
		{
			//ROS_INFO("GoToTarget Request Received - j1:%1.2f, j2:%1.2f",(float)req.linear_x,(float)req.angular_z);
		
			
			geometry_msgs::Twist msg;
			msg.linear.x=req.linear_x;
			msg.angular.z=req.angular_z;

			motor_pub.publish(msg);

			res.msg_feedback = "Linear velocity set - j1: " + std::to_string(req.linear_x)+", Angular velocity set - j2: " + std::to_string(req.angular_z);
			ROS_INFO_STREAM(res.msg_feedback);

			return true;
		}

};

int main(int argc, char** argv)
{
	ros::init(argc,argv,"drive_bot");
	ros::NodeHandle n;

	Pub_service PubServ(n);
	ROS_INFO("Ready to send commands");

	ros::spin();

	return 0;

}

