#pragma once
#include <queue>
#include <vector>
#include <memory>
#include <iostream>

#include "server.hpp"
#include "peer.hpp"

class System;

class Message{

public:
    Message(Peer* sender_init, double t_init, int receiver_init, bool upwards_init, const std::vector<int>& args_init);

    Peer* sender;
    int receiver;
    bool upwards;
    std::vector<int> args;
    double t;
};

class Network{

public:
    Network();

    void dequeue();

    int limit;

    System* sys;

    std::vector<std::shared_ptr<Peer>> processes;

    std::queue<std::shared_ptr<Message>> p2n;
};
