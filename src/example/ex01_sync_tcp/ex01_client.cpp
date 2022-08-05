#include <iostream>
#include <boost/asio.hpp>
#include <vector>

using namespace std;
namespace io = boost::asio;
namespace ip = io::ip;
// using tcp = io::ip::tcp;
// using error_code = boost::system::error_code;

int main()
{
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;
    typedef ip::address address_type;

    try
    {
        cout << ">>> Client starts." << endl;
        io::io_service io_srv;
        socket_type skt(io_srv);
        endpoint_type ep(address_type::from_string("127.0.0.1"), 6688);
        skt.connect(ep);
        vector<char> str_vec(skt.available()+1, 0);
        boost::system::error_code ec;
        cout << ">>> receive from " << skt.remote_endpoint().address() << endl;
        cout << ">>> Server: ";
        for(;;)
        {
            skt.read_some(io::buffer(str_vec), ec);
            if(ec) break;
            cout << &str_vec[0];
        }
        cout << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}