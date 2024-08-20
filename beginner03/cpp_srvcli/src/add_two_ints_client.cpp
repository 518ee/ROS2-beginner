#include <chrono>
#include <cinttypes>
#include <memory>

#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"


using AddTwoInts = example_interfaces::srv::AddTwoInts;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  // std::cout << argc << std::endl;

  if(argc != 1){
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add three ints");
    return 1;
  }

  auto node = rclcpp::Node::make_shared("add_three_ints_client");
  auto client = node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");
  while (!client->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "client interrupted while waiting for service to appear.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "waiting for service to appear...");
  }
  auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
  request->a = 41;
  request->b = 1;
  request->c = 41;
  auto result_future = client->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node, result_future) != rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_ERROR(node->get_logger(), "service call failed :(");
    client->remove_pending_request(result_future);
    return 1;
  }
  auto result = result_future.get();
  RCLCPP_INFO(
    node->get_logger(), "result of %ld + %ld + %ld = %ld",
    request->a, request->b, request->c,result->sum);
  rclcpp::shutdown();
  return 0;
}