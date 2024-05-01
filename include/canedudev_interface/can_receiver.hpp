#include "rclcpp/rclcpp.hpp"
#include <can_msgs/msg/frame.hpp>
#include <stdint.h>
#include <memory>
#include <string>
#include <autoware_auto_vehicle_msgs/msg/gear_command.hpp>
#include <autoware_auto_vehicle_msgs/srv/control_mode_command.hpp>
#include <tier4_vehicle_msgs/msg/actuation_command_stamped.hpp>
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
namespace canedudev_interface
{
class VehicleReport : public rclcpp::Node
{
    public:
        //Constructor
        VehicleReport();
    private:
        double loop_rate_;
        std::string frame_id_;
        rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;
        void can_frame_callback(const can_msgs::msg::Frame::SharedPtr msg);
        float bytesToFloat(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3);


};  
} // namespace canedudev_interface