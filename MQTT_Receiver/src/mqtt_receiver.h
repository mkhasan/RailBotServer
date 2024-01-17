#ifndef _MQTT_RECEIVER_H
#define _MQTT_RECEIVER_H

#include "abs_receiver.h"

#include <mosquittopp.h>
#include <pthread.h>

#include <string>
#include <memory>

class MqttReceiver;

class myMosq : public mosqpp::mosquittopp {

    friend class MqttReceiver;

    const char     *     host;
    const char    *     id;
    const char    *     topic;
    int                port;
    int                keepalive;


    void on_connect(int rc);
    void on_disconnect(int rc);
   	void on_subscribe(uint16_t mid, int qos_count, const uint8_t *grandted_qos);
    void on_message(const struct mosquitto_message *message);

public:
    myMosq(const char *id, const char * _topic, const char *host, int port);
    ~myMosq();

};

class MqttReceiver : public AbsReceiver {

    std::unique_ptr<myMosq> mqttInterface;
public:
    MqttReceiver();
    ~MqttReceiver();

    void Close();
};

#endif