// test_zmq.cpp
#include <zmq.hpp>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");
    std::cout << "ZMQ library is working!" << std::endl;
    return 0;
}