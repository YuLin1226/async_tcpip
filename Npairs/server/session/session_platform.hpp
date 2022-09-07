#if !defined(_SESSION_PLATFORM_HPP_)
#define _SESSION_PLATFORM_HPP_

#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include "frame/frame_platform.hpp"


namespace Session
{

class SessionPlatform : public std::enable_shared_from_this<SessionPlatform>
{
    public:
        SessionPlatform(boost::asio::io_context& ioContext, boost::asio::ip::tcp::socket &&socket);
        ~SessionPlatform();

        enum class ConnectionStatus {CONNECTED, STOPPING, STOPPED};

        using OnReadCallback = std::function<void(const Frame::FramePlatform&)>;
        using OnBrokenCallback = std::function<void()>;
        using OnDisConnectedCallback = std::function<void()>;
        
        void start(OnReadCallback onReadCallback, OnBrokenCallback onBrokenCallback);

        void stop(OnDisConnectedCallback callback);

        void write(unsigned char *pStart, size_t dataSize);

    private:
        static const int PREPARE_READ_BUFFER_SIZE = 1024;

        ConnectionStatus connectStatus_;
        boost::asio::ip::tcp::socket socket_;
        boost::asio::io_context::strand writeStrand_, readStrand_;
        boost::asio::streambuf incoming_;
        std::mutex mtxOutgoingQueue_;
        boost::asio::streambuf outgoing_, outgoingQueue_;
        int isAsyncWriteCompleteHandlerCalled_, isAsyncReadCompleteHandlerCalled_;

        OnReadCallback onReadCallback_;
        OnDisConnectedCallback  onDisConnectedCallback_;
        OnBrokenCallback onBrokenCallback_;

        //should be run in io_contex thread
        void issueDisConnect();

        //should be called in io_context thread
        void read();
        void onRead(boost::system::error_code error, std::size_t bytesTransferred);

        //should be called in io context thread
        void moveFromQueueAndWrite();
        void onWrite(boost::system::error_code error, std::size_t bytesTransferred);

        bool start_decode_data_;
};


} // namespace Session

#endif // _SESSION_PLATFORM_HPP_
