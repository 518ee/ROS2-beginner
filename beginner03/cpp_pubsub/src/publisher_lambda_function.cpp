// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "tutorial_interfaces/msg/num.hpp"   

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0) //name the node, initialize count to 0
  {
    publisher_ = this->create_publisher<tutorial_interfaces::msg::Num>("topic", 10); // limit type,name of topic,queue size of publisher
    // auto timer_callback =
    //   [this]() -> void { //this means the node
    //     auto message = std_msgs::msg::String();
    //     message.data = "Hello, world! " + std::to_string(this->count_++);
    //     RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str()); // print message
    //     this->publisher_->publish(message);
    //   };

    auto timer_callback = [this](){
      auto message = tutorial_interfaces::msg::Num(); //use custom interface                                  // CHANGE
      message.num = this->count_++;                                                     // CHANGE
      RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: '" << message.num << "'");    // CHANGE
      publisher_->publish(message);
    };

    
    timer_ = this->create_wall_timer(500ms, timer_callback); // timer_callback executed twice a second
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<tutorial_interfaces::msg::Num>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv); //initialize ros2
  rclcpp::spin(std::make_shared<MinimalPublisher>());// processing data from node
  rclcpp::shutdown();
  return 0;
}
