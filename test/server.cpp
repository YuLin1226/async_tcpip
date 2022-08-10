#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "session.h"

class Server
{
    typedef Server                          this_type;
    typedef boost::asio::ip::tcp::acceptor  acceptor_type;
    typedef boost::asio::ip::tcp::endpoint  endpoint_type;
    typedef boost::asio::ip::tcp::socket    socket_type;

private:
    boost::asio::io_context&        io_context_;
    acceptor_type                   acceptor_;
    std::unique_ptr<socket_type>    socket_;

public:
    std::shared_ptr<session> s_;

    Server(boost::asio::io_context& io_context):
    io_context_(io_context),
    acceptor_(io_context_, endpoint_type(boost::asio::ip::tcp::v4(), 6688))
    {
    }

    ~Server()
    {
    }

    void accept()
    {
        socket_ = std::make_unique<socket_type>(io_context_);
        acceptor_.async_accept(*socket_, [&](boost::system::error_code error)
        {
            s_ = std::make_shared<session>(std::move(*socket_));
            // sendData = true;
            accept();
        });
    }

    bool sendData = false;  
};


void run(boost::asio::io_context& io_context) 
{
    while(true) 
    {
        try 
        {
            io_context.run();
            break;
        }
        catch( std::exception& e)
        {
        }
    }
}

void test(Server& srv)
{
    while( true ) 
        {
            std::string line;
            std::getline(std::cin, line);
            if(line == "stop") 
            {
                break;
            }
            else 
            {
                srv.sendData = true;
            }
            if(srv.sendData)
            {
                srv.s_->start();
                // std::cout<<"okok";
            }
        }
    
}

int main()
{
    try
    {
        std::cout << ">>> Server starts" << std::endl;
        boost::asio::io_context io_context;
        Server server(io_context);
        server.accept();
        // auto io_thread = std::thread(&run, std::ref(io_context));
        auto t = std::thread(&test, std::ref(server));
        io_context.run();
        // while( true ) 
        // {
        //     std::string line;
        //     std::getline(std::cin, line);
        //     if(line == "stop") 
        //     {
        //         io_context.stop();
        //         break;
        //     }
        //     else 
        //     {
        //     }
        // }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}