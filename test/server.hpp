#if !defined(_SERVER_HPP_)
#define _SERVER_HPP_

#include "session/session_ex.hpp"


namespace TCP
{
    class Server
    {
    private:
        
        const unsigned int PLATFORM_PORT = 8888;

        boost::asio::io_context& io_context_;
        boost::asio::ip::tcp::acceptor platform_acceptor_;
        std::shared_ptr<boost::asio::ip::tcp::socket> platform_socket_ptr_;


    public:
        Server(boost::asio::io_context& io_context);
        ~Server();

        void accept();
        void platform_accept();

    };
    
    
} // namespace TCP

#endif // _SERVER_HPP_
