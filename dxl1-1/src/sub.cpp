#include "dxl1-1/sub.hpp"
void Sub::mysub_callback(Dxl& dxl, const geometry_msgs::msg::Vector3::SharedPtr msg) const
{
    RCLCPP_INFO(this->get_logger(), "Received message: %lf,%lf", msg->x,msg->y);
    dxl.setVelocity((int)msg->x, (int)msg->y);
}
Sub::Sub() : Node("node_camsub")
{
    if(!dxl.open())
    {
        RCLCPP_ERROR(this->get_logger(), "dynamixel open error");
        rclcpp::shutdown();
        //return -1;
    } 
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    std::function<void(const geometry_msgs::msg::Vector3::SharedPtr msg)> fn;
    fn = std::bind(&Sub::mysub_callback, this, dxl, _1);
    sub_ = this->create_subscription<geometry_msgs::msg::Vector3>("topic_dxlpub", qos_profile,fn);
}