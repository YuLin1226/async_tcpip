#include "session.hpp"

class SessionPlatform : public Session
{
private:
    


public:
    SessionPlatform(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr);

    ~SessionPlatform();

    void writeMessage() override;

    void readMessage() override;

};



