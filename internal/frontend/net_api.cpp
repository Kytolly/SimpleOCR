#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // For JSON parsing
#include <zmq.hpp> 

using json = nlohmann::json;

struct Record {
    int rId;
    std::string result;
    float confidence;

    static Record from_json(const json& j) {
        return { j.at("rId"), j.at("result"), j.at("confidence") };
    }
};


struct Output {
    int oId;
    bool statusOK;
    int msgCode;
    std::vector<Record> records;

    // Deserialize from JSON
    static Output from_json(const std::string& json_str) {
        json j = json::parse(json_str);
        Output output;
        output.oId = j.at("oId");
        output.statusOK = j.at("statusOK");
        output.msgCode = j.at("msgCode");
        for (const auto& record_json : j.at("records")) {
            output.records.push_back(Record::from_json(record_json));
        }
        return output;
    }
};


Output receiveOcrOutput(zmq::socket_t& socket) {
    zmq::message_t request;
    socket.recv(request, zmq::recv_flags::none);

    std::string received_data(static_cast<char*>(request.data()), request.size());
    return Output::from_json(received_data);
}
