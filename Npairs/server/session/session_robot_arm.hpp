#include "session.hpp"

class SessionRobotArm : public Session
{

private:

public:

    SessionRobotArm(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr);

    ~SessionRobotArm();

    void writeMessage() override;

    void readMessage() override;




};

