#include <opencv2/highgui/highgui.hpp>
#include <ros/package.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>




int main(int argc, char **argv) {
  ros::init(argc, argv, "numbers_aranyadan");
    ros::NodeHandle node_handle;
    image_transport::ImageTransport image_transport(node_handle);
    image_transport::Publisher lanes_publisher= image_transport.advertise("/test", 2);
    cv_bridge::CvImage message;
    sensor_msgs::ImagePtr msg;
    message.encoding = sensor_msgs::image_encodings::MONO8;

ros::Rate loop_rate(5);


    while (ros::ok())
    {
      cv::Mat img = cv::imread(ros::package::getPath("imtest") + "/include/1.jpg",CV_LOAD_IMAGE_COLOR);
      msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();
      lanes_publisher.publish(msg);
      if( img.empty() ) {
      ROS_INFO("Error occured, image not read correctly");
            }
      ROS_INFO("printing:\n");
      ros::spinOnce();
      loop_rate.sleep();

    }
    return 0;
}
