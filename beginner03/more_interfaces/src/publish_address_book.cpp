#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
    AddressBookPublisher()
    :Node("address_book")
    {
        publisher_ = this->create_publisher<more_interfaces::msg::AddressBook>("address_book_publish",10);

        auto timer_callback = [this](){
            auto message = more_interfaces::msg::AddressBook();

            message.first_name = "Fall";
            message.last_name = "Chen";
            message.phone_number = "234568";
            message.phone_type = message.PHONE_TYPE_WORK;

            // RCLCPP_INFO(this->get_logger(),"Publishing: \n the first name is %s, \n the last name is %s, \n the phone number is %s, the type is %ld",
            //     message.first_name, message.last_name, message.phone_number, message.phone_type);
            std::cout << "Publishing" << std::endl 
            << "the first name is: " << message.first_name <<std::endl 
            << "the second name is: " << message.last_name << std::endl
            << "the phone number is: " << message.phone_number << std::endl
            << "the type of phone is: " << message.phone_type << std::endl;
            publisher_->publish(message);
        };

        timer_ = this->create_wall_timer(1s, timer_callback);
    }
private:
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr publisher_;
};

int main(int argc, char * argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddressBookPublisher>());
    rclcpp::shutdown();
}