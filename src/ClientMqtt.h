#pragma once

#include <cstdint>
#include <mosquittopp.h>
#include <string>

typedef uint32_t UINT;

class ClientMQTT : public mosqpp::mosquittopp {
private:
    std::string mTopic;
    int mMaxPayload;
public:
    static const int portDefault = 1883;

    ClientMQTT(const char *id, const char *topic, int maxPayload = 128);
    ~ClientMQTT();
    
    int connect(const char *host, UINT port = portDefault);
    void on_connect(int rc);
    void on_message(const mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
};