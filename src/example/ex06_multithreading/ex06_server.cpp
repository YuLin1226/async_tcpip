#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "session.hpp"

class Server
{

private:
    boost::asio::io_context&                        io_context_;
    boost::asio::ip::tcp::acceptor                  acceptor_;
    std::unique_ptr<boost::asio::ip::tcp::socket>   socket_;
    std::vector<std::thread>                        threads_;

public:

    Server(boost::asio::io_context& io_context)
    : io_context_(io_context)
    , acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6688))
    {
    }

    ~Server()
    {
    }

    void accept()
    {
        socket_ = std::make_unique<boost::asio::ip::tcp::socket>(io_context_);
        acceptor_.async_accept(*socket_, [&](boost::system::error_code error)
        {
            
            // std::make_shared<session>(std::move(*socket_))->start();
            accept();
        });
    }

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

int main()
{
    try
    {
        std::cout << ">>> Server starts" << std::endl;
        boost::asio::io_context io_context;
        Server server(io_context);
        server.accept();
        // auto io_thread = std::thread(&run, std::ref(io_context));
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