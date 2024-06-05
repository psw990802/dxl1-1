#include "dxl1-1/pub.hpp"
Pub::Pub() : Node("node_dxlpub")
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    pub_ = this->create_publisher<geometry_msgs::msg::Vector3>("topic_dxlpub", qos_profile);
    timer_ = this->create_wall_timer(50ms, std::bind(&Pub::publish_msg, this));
    vel_.x = 0;
    vel_.y = 0;
    vel_.z = 0;
    vel1 = vel2 = 0;
    goal1 = goal2 = 0;
}
void Pub::publish_msg()
{
    if (Dxl::kbhit())
    {
        char c = Dxl::getch();
        switch(c)
        {
        case 's': goal1 = 0; goal2 = 0; break;
        case ' ': goal1 = 0; goal2 = 0; break;
        case 'f': goal1 = 50; goal2 = -50; break;
        case 'b': goal1 = -50; goal2 = 50; break;
        case 'l': goal1 = -50; goal2 = -50; break;
        case 'r': goal1 = 50; goal2 = 50; break;
        default : goal1 = 0; goal2 = 0; break;
        }         
    }
    
    // generate accel and decel motion
    if(goal1>vel1) vel1 += 5;
    else if(goal1<vel1) vel1 -= 5;
    else vel1 = goal1;
    if(goal2>vel2) vel2 += 5;
    else if(goal2<vel2) vel2 -= 5;
    else vel2 = goal2;
    vel_.x = vel1;
    vel_.y = vel2; 
                  
    RCLCPP_INFO(this->get_logger(), "Publish: %lf,%lf", vel_.x, vel_.y);
    pub_->publish(vel_);

}