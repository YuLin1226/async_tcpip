echo "Manually compile tcp server and client codes."
g++ server_node.cpp server.cpp session.cpp -o server_node.exe -lpthread