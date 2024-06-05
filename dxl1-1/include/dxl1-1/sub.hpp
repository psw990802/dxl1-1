#ifndef _SUB_HPP_
#define _SUB_HPP_
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "dxl1-1/dxl.hpp"
#include <functional>
#include <memory>
using namespace std::placeholders;
class Sub : public rclcpp::Node
{
    private:
        rclcpp::Subscription<geometry_msgs::msg::Vector3>::SharedPtr sub_;
        void mysub_callback(Dxl& dxl, const geometry_msgs::msg::Vector3::SharedPtr msg) const;
        
    public:
        Sub();
        Dxl dxl;
};
#endif //_SUB_HPP_


