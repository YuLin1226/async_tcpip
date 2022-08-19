#include <iostream>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(){}

    Session(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr)
    : socket_ptr_(std::move(socket_ptr))
    , timer_ptr_(std::move(timer_ptr))
    {
    }

    /**
     * @brief Write data to client. Child sessions need to design their own function.
     */
    virtual void writeMessage() = 0;
    virtual void writeMessage(const int) = 0;

    /**
     * @brief Read data from client. Child sessions need to design their own function.
     */
    virtual void readMessage() = 0;
    virtual void readMessage(const int) = 0;

protected:
    
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr_;
    std::shared_ptr<boost::asio::deadline_timer> timer_ptr_;

};