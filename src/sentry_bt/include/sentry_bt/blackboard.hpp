#ifndef SENTRY_BT__BLACKBOARD_HPP_
#define SENTRY_BT__BLACKBOARD_HPP_

#include <iostream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

struct Point{
    double x = 0.0;
    double y = 0.0;
};


class Blackboard{
public:
    Blackboard(rclcpp::Node::SharedPtr node);
    ~Blackboard() = default;

    void setDestination(Point destination);

    Point getDestination() const;

    void setBlood(int blood);

    int getBlood() const;

    bool isLowBlood(int threshold = 20) const;

    void setRobotStatus(const std::string &status);

    std::string getRobotStatus() const;

private:
    Point current_dest_;
    rclcpp::Node::SharedPtr node_;
    int blood = 100;
};

#endif // SENTRY_BT__BLACKBOARD_HPP_