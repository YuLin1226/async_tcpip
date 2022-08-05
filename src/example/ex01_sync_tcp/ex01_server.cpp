#include <iostream>
#include <boost/asio.hpp>

using namespace std;
namespace io = boost::asio;
namespace ip = io::ip;
// using tcp = io::ip::tcp;
// using error_code = boost::system::error_code;

int main()
{
    typedef ip::tcp::acceptor acceptor_type;
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;

    try
    {
        cout << ">>> Server starts." << endl;
        io::io_service io_srv;
        acceptor_type acceptor(io_srv, endpoint_type(ip::tcp::v4(), 6688));
        for(;;)
        {
            socket_type skt(io_srv);
            acceptor.accept(skt);

            cout << ">>> client: " << skt.remote_endpoint().address() << endl;

            skt.send(io::buffer("Hello asio client, this is asio server."));
        }
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}