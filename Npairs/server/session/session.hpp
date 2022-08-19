#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <iostream>
#include <boost/asio.hpp>

class Session : public std::enable_shared_from_this<Session>
{
public:
    enum class ActionStatus {SUCCESS, FAILURE, UNKNOWN};

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

    /**
     * @brief Check action completed successfully or not.
     */
    virtual ActionStatus checkActionStatus() = 0;
    virtual ActionStatus checkActionStatus(const int) = 0;
    
protected:
    
    std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr_;
    std::shared_ptr<boost::asio::deadline_timer> timer_ptr_;
    std::vector<char> received_data_;

};

#endif