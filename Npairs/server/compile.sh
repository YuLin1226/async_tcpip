echo "Manually compile tcp server and client codes."
g++ tcp_node.cpp server.cpp session/session_platform.cpp session/frame/frame_platform.cpp -o tcp_node -lpthread