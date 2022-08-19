#include "session.hpp"

class SessionRobotArm : public Session
{

private:

public:

    SessionRobotArm(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr);

    ~SessionRobotArm();

    void writeMessage(const int move_id) override;

    void readMessage(const int move_id) override;




};

