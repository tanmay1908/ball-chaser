#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
#include <iostream>
#include <string>

class Client_Sub
{
private:
ros::ServiceClient client;
ros::Subscriber image_sub;

public:

Client_Sub(ros::NodeHandle &n)
{
	client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
	image_sub=n.subscribe("camera/rgb/image_raw",10,&Client_Sub::HandleImage,this);
}

void HandleImage(const sensor_msgs::Image img)
{
	bool isBall=0;
	int i;
	int white_pixel=255;
	//ROS_INFO("Entering loop");


	//find ball in image
	for(i=0; i<img.height*img.step;i=i+3)
	{

		if(img.data[i]==white_pixel)
		{
			
			if(img.data[i+1]==255&&img.data[i+2]==255)
				{
					isBall=1;
					break;
				}

		}
	}	
							

	float lin_x,ang_z;

	if(isBall)
	{
		//if ball is in the left 45% of image width, designate position of ball as "Left"
		//if ball is in the right 45% of image width, designate position of ball as "right"
		//if ball is in the middle 10% of image width, then designate position of ball as "center"
		int LeftBound=(img.step)*0.30;
		int RightBound=(img.step)*0.70;
		
		//img.data[] elements with index 0,1,2 give info about pixel 1, indices 3,4,5 give info about pixel 2 and so on..Number of pixel is therefore given as (int) [i/3]+1
		//i=(i/3)+1; 
		i=i%img.step;
		//Check if ball is in left, right or center and assign appropriate velocities
		if(i>=0 && i<LeftBound)
		{
			lin_x=0;
			ang_z=1.0;
			//ROS_INFO("left");
		}

		if(i>=LeftBound&&i<RightBound)
		{
			lin_x=0.5;
			ang_z=0;
			//ROS_INFO("center");
		}

		if(i>=RightBound&&i<img.step)
		{
			lin_x=0;
			ang_z=-1.0;
			//ROS_INFO("right");
		}
	}
	
	else
	{
		lin_x=0;
		ang_z=0;
		//ROS_INFO("not in frame");
	}

	drive_robot(lin_x,ang_z);
}

void drive_robot(float lin_x, float ang_z)
{
	ball_chaser::DriveToTarget srv;
	
	srv.request.linear_x=lin_x;
	srv.request.angular_z=ang_z;	

	if(!client.call(srv))
	{
		ROS_ERROR("Failed to call service command_robot");
	}
	else
	{
		//ROS_INFO("client req sent");
	}

	//ROS_INFO("drive_robot called");
}

};

int main(int argc,char** argv)
{
	ros::init(argc,argv,"process_image");
	ros::NodeHandle n;

	Client_Sub Client_sub_obj(n);
	ROS_INFO("Running code for process_image");
	ros::spin();
	//ROS_INFO("Post Spin");
	return 0;

}
