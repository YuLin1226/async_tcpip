#include "session.hpp"

class SessionRobotArm : public Session
{

private:
    unsigned int MOVE_WAIT_TIME = 20;

    std::string getMoveCommand(const int move_id);

    std::string getMoveFeedbackDefinition(const int move_id);

public:

    SessionRobotArm(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr);

    ~SessionRobotArm();

    void writeMessage(const int move_id) override;

    void readMessage(const int move_id) override;




};

