#include "sentry_bt/blackboard.hpp"

Blackboard::Blackboard(rclcpp::Node::SharedPtr node) : node_(node)
{
    auto blood_sub_ = node_->create_subscription<std_msgs::msg::Int32>(
        "/sentry_blood",
        10,
        [this](const std_msgs::msg::Int32::SharedPtr msg)
        {
            this->blood = msg->data;
        });
}

void Blackboard::setDestination(Point destination)
{
    current_dest_ = destination;
}

Point Blackboard::getDestination() const
{
    return current_dest_;
}

int Blackboard::getBlood() const
{
    return blood;
}

