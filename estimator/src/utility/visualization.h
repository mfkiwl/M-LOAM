/*******************************************************
 * Copyright (C) 2019, Aerial Robotics Group, Hong Kong University of Science and Technology
 *
 * This file is part of VINS.
 *
 * Licensed under the GNU General Public License v3.0;
 * you may not use this file except in compliance with the License.
 *******************************************************/

#pragma once

#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PointStamped.h>
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>

#include <eigen3/Eigen/Dense>
#include <pcl/common/transforms.h>

#include "common/publisher.hpp"
#include "../estimator/estimator.h"
#include "../estimator/parameters.h"
#include "mloam_msgs/Extrinsics.h"

// point cloud
extern ros::Publisher pub_laser_cloud;
extern ros::Publisher pub_laser_cloud_proj;
extern ros::Publisher pub_corner_points_sharp;
extern ros::Publisher pub_corner_points_less_sharp;
extern ros::Publisher pub_surf_points_flat;
extern ros::Publisher pub_surf_points_less_flat;

// local map
extern std::vector<ros::Publisher> v_pub_surf_points_local_map;
extern std::vector<ros::Publisher> v_pub_surf_points_cur;

extern std::vector<ros::Publisher> v_pub_corner_points_local_map;

// odometry
extern std::vector<ros::Publisher> v_pub_laser_odometry;
extern std::vector<ros::Publisher> v_pub_laser_path;

// extrinsic
extern ros::Publisher pub_extrinsics;

void clearPath();

void registerPub(ros::NodeHandle &nh);

void printStatistics(const Estimator &estimator, double t);

void pubOdometry(const Estimator &estimator, const double &time);

void pubPointCloud(const Estimator &estimator, const double &time);

void pubCar(const Estimator &estimator, const std_msgs::Header &header);



//
