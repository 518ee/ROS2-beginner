#include <cinttypes>
#include <memory>

#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"


using AddTwoInts = example_interfaces::srv::AddTwoInts;
rclcpp::Node::SharedPtr g_node = nullptr;

// void handle_service(
//   const std::shared_ptr<rmw_request_id_t> request_header,
//   const std::shared_ptr<AddTwoInts::Request> request,
//   const std::shared_ptr<AddTwoInts::Response> response)
// {
//   (void)request_header;
//   RCLCPP_INFO(
//     g_node->get_logger(),
//     "request: %" PRId64 " + %" PRId64, request->a, request->b);
//   response->sum = request->a + request->b;
// }

// int main(int argc, char ** argv)
// {
//   rclcpp::init(argc, argv);
//   g_node = rclcpp::Node::make_shared("minimal_service");
//   auto server = g_node->create_service<AddTwoInts>("add_two_ints", handle_service);
//   rclcpp::spin(g_node);
//   rclcpp::shutdown();
//   g_node = nullptr;
//   return 0;
// }

void addThreeInts(
  const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,
  std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response> respond)
{
  respond->sum = request->a + request->b + request->c;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request: %ld, %ld, %ld",request->a, request->b, request->c);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back message: the sum is %ld",respond->sum);
}

int main(int argc, char ** argv){
  rclcpp::init(argc, argv);
  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("add_three_int_service");
  auto server = node->create_service<tutorial_interfaces::srv::AddThreeInts>("add_three_ints",addThreeInts);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints."); 
  rclcpp::spin(node);
  rclcpp::shutdown();
  node = nullptr;
  return 0;
}