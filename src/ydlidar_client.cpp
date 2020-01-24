/*
 *  YDLIDAR SYSTEM
 *  YDLIDAR ROS Node Client 
 *
 *  Copyright 2015 - 2018 EAI TEAM
 *  http://www.ydlidar.com
 * 
 */

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <bits/stdc++.h>
#include <iostream>
#define RAD2DEG(x) ((x)*180./M_PI)
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
    float min_angle = (RAD2DEG(scan->angle_min)+180.);
    float max_angle = (RAD2DEG(scan->angle_max)+180.);
    float increment_angle = 5.0;
    printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", min_angle,max_angle);
   // printf("%f\n",increment_angle);  
    for(float i = min_angle; i < max_angle; i++) {
        float degree = min_angle + increment_angle * i;
	if((degree > 90. && degree< 270.)||(degree > 0. && degree<45.)||(degree>315. && degree<360. )){
        printf("[YDLIDAR INFO]: angle-distance : [%f, %f]\n", degree, scan->ranges[i]);
	if(scan->ranges[i]>0.&& scan->ranges[i]<0.75){
	printf("System Alert.Vehicle in blind spot at %f\n",degree);
	//turn on led when vehicle is in blind spot
	system("python3 ~/ydlidar_ws/src/ydlidar_ros/src/Led.py");
	}
        }
	else{
	//turn off led when vehicle is not in blind spot
	system("python3 ~/ydlidar_ws/src/ydlidar_ros/src/Led1.py");
	}
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}
