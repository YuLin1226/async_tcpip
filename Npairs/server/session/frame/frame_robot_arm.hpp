#if !defined(_FRAME_ROBOTARM_HPP_)
#define _FRAME_ROBOTARM_HPP_

#include <memory>
#include <iostream>
#include <boost/asio.hpp>

namespace Frame
{

class FrameRobotArm
{
    public:
        
        FrameRobotArm(boost::asio::streambuf &streambuf);

        //search leading characters, return true if leading is found
        bool trimToLeadingChars();

        //this is the whole size of frame
        //if size cannot be parsed, return max
        size_t parseFrameSize() const;

        //assume data there there
        void print(size_t frameSize, std::ostream &out) const;

        //pStart point to data without leading chars and size
        void writeFrameContent(unsigned char *pStart, size_t dataSize);

    private:
        boost::asio::streambuf &streambuf_;
        
};

} // namespace Frame

#endif // _FRAME_ROBOTARM_HPP_
