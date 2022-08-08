echo "Manually compile tcp server and client codes."
g++ chat_server.cpp -o chat_server.exe -lpthread
g++ chat_client.cpp -o chat_client.exe -lpthread