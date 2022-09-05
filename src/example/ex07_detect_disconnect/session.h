#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>

class session : public std::enable_shared_from_this<session>
{
public:

    session(boost::asio::ip::tcp::socket&& socket, boost::asio::io_context& io_context)
    : socket(std::move(socket))
    , io_context_(io_context)
    {
        initialization();
    }

    void initialization()
    {
        std::cout << "*** Session initialized. ***" << std::endl;
        timeout_ = std::shared_ptr<boost::asio::deadline_timer>{new boost::asio::deadline_timer(io_context_)};
        mutex_   = std::shared_ptr<boost::mutex>{new boost::mutex};
    }

    ~session()
    {
        std::cout << "Session destroyed" << std::endl;
    }

    void start()
    {   
        boost::asio::async_read_until(socket, 
                                      streambuf, 
                                      "e$", 
                                      [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
        {
            std::cout << std::istream(&self->streambuf).rdbuf();
        });
        
        timeout_->expires_from_now(boost::posix_time::seconds(3));
        timeout_->async_wait(  
            [&](const boost::system::error_code &error)
            {
                if (!error)
                {
                    socket.cancel();
                    std::cerr << "[Output] Read timeout." << std::endl;
                }
            });
    }

    void writeMsg()
    {
        boost::asio::async_write(
            socket,
            boost::asio::buffer("$1,safe,0,0,move$\n"),
            [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
            {
                std::cout << ">>> send message completed" << std::endl;
            });
    }

    void writeMsg1()
    {
        for(auto i = 0 ; i < received_data.size() ; i++)
            std::cout << received_data[i] << " ";
        boost::asio::async_write(
            socket,
            boost::asio::buffer(received_data, 10),
            [self = shared_from_this()](boost::system::error_code error, std::size_t bytes_transferred)
            {
                std::cout << ">>> send message completed" << std::endl;
            });
    }

    void readMsg(uint8_t data_size)
    {
        auto self(shared_from_this());
        boost::asio::async_read(
            socket,
            boost::asio::buffer(received_data, data_size),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    // send back to client
                    writeMsg1();
                }
            }
        );
        
    }
    

private:

    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
    std::vector<char> received_data = std::vector<char>(100);
    std::shared_ptr<boost::asio::deadline_timer> timeout_;
    std::shared_ptr<boost::mutex> mutex_;
    boost::asio::io_context& io_context_;
    
};