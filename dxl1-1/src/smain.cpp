#include "dxl1-1/sub.hpp"
using namespace std::placeholders;
int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Sub>();    
    rclcpp::spin(node);
    node->dxl.close();
    rclcpp::shutdown();
    return 0;
}