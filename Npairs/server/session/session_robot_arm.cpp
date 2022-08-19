#include "session_robot_arm.hpp"

SessionRobotArm::SessionRobotArm(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr)
{
    std::cout << ">>> Session <ROBOTARM> created." << std::endl;
}

SessionRobotArm::~SessionRobotArm()
{
    std::cout << ">>> Session <ROBOTARM> destroyed." << std::endl;
}

void SessionRobotArm::writeMessage()
{
    // TODO: command if as arg.
    // if the command id does not exist, throw error.
}

void SessionRobotArm::readMessage()
{
}