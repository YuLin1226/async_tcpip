#include "frame_ex1.hpp"

namespace Frame
{

    FrameEX::FrameEX(boost::asio::streambuf &streambuf)
    : streambuf_(streambuf)
    {
    }


    bool FrameEX::trimToLeadingChars() 
    {
        int matchStatus = -1;   //not matched
        if (streambuf_.size() >= 4) 
        {
            size_t startPosition = -1;
            auto d = boost::asio::buffers_begin(streambuf_.data());
            auto dend = boost::asio::buffers_end(streambuf_.data());
            for (size_t i=0;d!=dend; ++d, ++i) 
            {
                if (matchStatus == -1) 
                {
                    if (static_cast<unsigned char>(*d) == ('$' & 0xFF)) 
                    {
                        matchStatus = 0;
                        startPosition = i;
                        break;
                    } 
                    // else 
                    // {
                    //     matchStatus = -1;
                    // }
                } 
                // else if (matchStatus == 0) 
                // {
                //     if (static_cast<unsigned char>(*d) == 0x0b) 
                //     {
                //         matchStatus = 1;
                //     } 
                //     else 
                //     {
                //         matchStatus = -1;
                //     }
                // } 
                // else if (matchStatus == 1) 
                // {
                //     if (static_cast<unsigned char>(*d) == 0x0c) 
                //     {
                //         matchStatus = 2;
                //     } 
                //     else 
                //     {
                //         matchStatus = -1;
                //     }
                // } 
                // else if (matchStatus == 2) 
                // {
                //     if (static_cast<unsigned char>(*d) == 0x0d) 
                //     {
                //         matchStatus = 3;
                //         break;
                //     } 
                //     else 
                //     {
                //         matchStatus = -1;
                //     }
                // }
            }
            if (matchStatus == 0) 
            {
                //give up data before startPosition
                streambuf_.consume(startPosition);
            }
        }
        return matchStatus == 0;
    }

    size_t FrameEX::parseFrameSize() const 
    {
        // size_t frameSize = std::numeric_limits<size_t>::max();
        // if (streambuf_.size() >=4) 
        // {
        //     auto d = boost::asio::buffers_begin(streambuf_.data());
        //     d += 4;
        //     frameSize = static_cast<unsigned char>(*d);
        //     ++d;
        //     size_t highByte = static_cast<unsigned char>(*d);
        //     frameSize += highByte * 256;

        //     //note: according to spec. we should modify frameSize
        // }

        int matchStatus = -1;
        size_t startPosition = -1;
        auto d = boost::asio::buffers_begin(streambuf_.data());
        auto dend = boost::asio::buffers_end(streambuf_.data());
        for (size_t i=0; d!=dend; ++d, ++i) 
        {
        
            if (static_cast<unsigned char>(*d) == ('$' & 0xFF)) 
            {
                matchStatus += 1;
                startPosition = i;
            }
            
            if (matchStatus == 1)
            {
                break;
            }
        }

        size_t frameSize = startPosition +1 +2;
        return frameSize;
    }

    void FrameEX::print(size_t frameSize, std::ostream &out) const
    {
        auto d = boost::asio::buffers_begin(streambuf_.data());
        out << "frameSize: " << std::dec << frameSize << ", all frame data: ";
        for (size_t i=0; i<frameSize; ++i) 
        {
            out << std::hex << static_cast<int>(*d) << " ";
            d++;
        }
        out << std::endl;
    }

    void FrameEX::writeFrameContent(unsigned char *pStart, size_t dataSize) 
    {
        size_t frameSize = dataSize + 6;
        boost::asio::mutable_buffer view = streambuf_.prepare(frameSize);
        auto pwrite = static_cast<unsigned char*>(view.data());
        //write leading
        *pwrite++ = 0x0a;
        *pwrite++ = 0x0b;
        *pwrite++ = 0x0c;
        *pwrite++ = 0x0d;

        //write size
        size_t sizeLowByte = frameSize & 0xFF;
        size_t sizeHighByte = (frameSize >> 8) & 0xFF;
        *pwrite++ = static_cast<unsigned char>(sizeLowByte);
        *pwrite++ = static_cast<unsigned char>(sizeHighByte);

        //write data
        for (size_t i=0; i<dataSize; ++i) 
        {
            *pwrite++ = pStart[i];
        }

        streambuf_.commit(frameSize);
    }





} // namespace Frame
