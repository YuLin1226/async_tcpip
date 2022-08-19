#include "session_platform.hpp"

SessionPlatform::SessionPlatform(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr)
{
    std::cout << ">>> Session <PLATFORM> created." << std::endl;
}

SessionPlatform::~SessionPlatform()
{
    std::cout << ">>> Session <PLATFORM> destroyed." << std::endl;
}

void SessionPlatform::writeMessage()
{
    // TODO: command if as arg.
    // if the command id does not exist, throw error.
}

void SessionPlatform::readMessage()
{

}