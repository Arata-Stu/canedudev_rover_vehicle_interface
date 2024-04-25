#include "rclcpp/rclcpp.hpp"
#include <can_msgs/msg/frame.hpp>
#include <stdint.h>
#include <memory>
#include <autoware_auto_vehicle_msgs/msg/gear_command.hpp>
#include <autoware_auto_vehicle_msgs/srv/control_mode_command.hpp>
#include <tier4_vehicle_msgs/msg/actuation_command_stamped.hpp>
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
namespace canedudev_interface
{
class ControlCommand : public rclcpp::Node
{
    public:
        //Constructor
        ControlCommand();

    private:
        rclcpp::Subscription<tier4_vehicle_msgs::msg::ActuationCommandStamped>::SharedPtr actuation_sub_;
        rclcpp::Subscription<autoware_auto_vehicle_msgs::msg::GearCommand>::SharedPtr gear_cmd_sub_;
        rclcpp::Service<autoware_auto_vehicle_msgs::srv::ControlModeCommand>::SharedPtr control_mode_server_;
        can_msgs::msg::Frame::ConstSharedPtr steer_ctrl_can_ptr_;
        can_msgs::msg::Frame::ConstSharedPtr throttle_ctrl_can_ptr_;
        bool is_engage_;
        bool is_drive_;
        bool is_reverse_;
        bool engage_cmd_;
        rclcpp::Publisher<can_msgs::msg::Frame>::SharedPtr can_frame_pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        uint16_t steer_cmd_;
        uint16_t throttle_cmd_;
        double loop_rate_;

        /**
         * @brief Actuation command callback (Include throttle, brake, steering)
         * 
         * @param msg tier4_vehicle_msgs::msg::ActuationCommandStamped
         */
        void actuation_callback(const tier4_vehicle_msgs::msg::ActuationCommandStamped::SharedPtr msg);
        /**
         * @brief Gear command callback (Drive or Reverse)
         * 
         * @param msg autoware_auto_vehicle_msgs::msg::GearCommand
         */
        void gear_cmd_callback(const autoware_auto_vehicle_msgs::msg::GearCommand::SharedPtr msg);
        /**
         * @brief Timer callback for publish CAN message 
         * 
         */
        void timer_callback();
        void onControlModeRequest(const autoware_auto_vehicle_msgs::srv::ControlModeCommand::Request::SharedPtr request,
                                  const autoware_auto_vehicle_msgs::srv::ControlModeCommand::Response::SharedPtr respons);



};
} // namespace canedudev_interface