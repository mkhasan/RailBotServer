#include "mqtt_receiver.h"

#include <assert.h>

#include <iostream>
#include <memory>
#include <string.h>

using namespace std;

myMosq::myMosq(const char * _id,const char * _topic, const char * _host, int _port) : mosquittopp(_id){

    mosqpp::lib_init();        // Mandatory initialization for mosquitto library
    this->keepalive = 60;    // Basic configuration setup for myMosq class
    this->id = _id;
    this->port = _port;
    this->host = _host;
    this->topic = _topic;

    fs = ofstream("example.bin", std::ios::out | std::ios::binary | std::ios::app);

    connect_async(host,     // non blocking connection to broker request
        port,
        keepalive
    );
    loop_start();            // Start thread managing connection / publish / subscribe} 

    

}

myMosq::~myMosq() {
    loop_stop();            // Kill the thread
    mosqpp::lib_cleanup();    // Mosquitto library cleanup

    fs.close();
}

void myMosq::on_disconnect(int rc) {
    std::cout << ">> myMosq - disconnection(" << rc << ")" << std::endl;
}

void myMosq::on_connect(int rc)
{
    if ( rc == 0 ) {
       std::cout << ">> myMosq - connected with server" << std::endl;
       subscribe(NULL, topic);

    } else {
        std::cout << ">> myMosq - Impossible to connect with server(" << rc << ")" << std::endl;
    }
}

void myMosq::on_message(const mosquitto_message * message) {
    const char *p;
    if(!strcmp(message->topic, this->topic)) {
		p = (const char *) message->payload;
        cout << message->payloadlen << endl;
        fs.write(p, message->payloadlen);
        
	}
}


MqttReceiver::MqttReceiver() {
    mqttInterface = make_unique<myMosq>("mqtt_receiver", "irimage", "192.168.0.35", 8500);

}

MqttReceiver::~MqttReceiver() {

}

void MqttReceiver::Close() {
    mqttInterface->disconnect();
}

