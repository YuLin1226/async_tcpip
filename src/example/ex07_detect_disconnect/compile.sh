echo "Manually compile tcp server and client codes."
g++ ex07_server.cpp -o server.exe -lpthread
g++ ex07_client.cpp -o client.exe -lpthread