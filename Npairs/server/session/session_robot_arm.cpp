#include "session_robot_arm.hpp"

SessionRobotArm::SessionRobotArm(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr)
{
    std::cout << ">>> Session <ROBOTARM> created." << std::endl;
}

SessionRobotArm::~SessionRobotArm()
{
    std::cout << ">>> Session <ROBOTARM> destroyed." << std::endl;
}

void SessionRobotArm::writeMessage(const int move_id)
{
    // TODO: command if as arg.
    // if the command id does not exist, throw error.
}


void SessionRobotArm::readMessage(const int move_id)
{     
}