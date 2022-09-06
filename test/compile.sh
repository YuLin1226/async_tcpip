echo "Manually compile tcp server and client codes."
g++ server_node.cpp server.cpp session/session_ex.cpp frame/frame_ex1.cpp -o server_node.exe -lpthread