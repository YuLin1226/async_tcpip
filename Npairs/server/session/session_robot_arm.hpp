#if !defined(_SESSION_ROBOTARM_HPP_)
#define _SESSION_ROBOTARM_HPP_

#include <memory>
#include <functional>
#include <boost/asio.hpp>
#include "frame/frame_robot_arm.hpp"


namespace Session
{

class SessionRobotArm : public std::enable_shared_from_this<SessionRobotArm>
{
    public:
        const int MOVE_WAIT_TIME = 20;

        SessionRobotArm(boost::asio::io_context& ioContext, boost::asio::ip::tcp::socket &&socket);
        ~SessionRobotArm();

        enum class ConnectionStatus {CONNECTED, STOPPING, STOPPED};

        using OnReadCallback = std::function<void(const Frame::FrameRobotArm&)>;
        using OnBrokenCallback = std::function<void()>;
        using OnDisConnectedCallback = std::function<void()>;
        
        void start(OnReadCallback onReadCallback, OnBrokenCallback onBrokenCallback);

        void stop(OnDisConnectedCallback callback);

        void write(unsigned char *pStart, size_t dataSize);

        bool start_decode_data_;
        void shutdownTimerWhenDataReceived();


    private:
        static const int PREPARE_READ_BUFFER_SIZE = 1024;

        ConnectionStatus connectStatus_;
        boost::asio::ip::tcp::socket socket_;
        boost::asio::deadline_timer timer_;
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

        void setTimerForReadingTimeout();
        

        
};


} // namespace Session

#endif // _SESSION_ROBOTARM_HPP_
