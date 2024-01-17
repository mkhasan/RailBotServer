#include <mosquittopp.h>
#include <pthread.h>

#include <unistd.h>

#include <string>
#include <memory>
#include <fstream>
#include <iostream>

#include <string.h>

using namespace std;

class myMosq : public mosqpp::mosquittopp
{
private:
    const char     *     host;
    const char    *     id;
    const char    *     topic;
    int                port;
    int                keepalive;

    void on_connect(int rc);
    void on_disconnect(int rc);
    void on_publish(int mid);
public:
    myMosq(const char *id, const char * _topic, const char *host, int port);
    ~myMosq();
    bool send_message(const char * _message, int len);
};

myMosq::myMosq(const char * _id,const char * _topic, const char * _host, int _port) : mosquittopp(_id)
{
    mosqpp::lib_init();        // Mandatory initialization for mosquitto library
    this->keepalive = 60;    // Basic configuration setup for myMosq class
    this->id = _id;
    this->port = _port;
    this->host = _host;
    this->topic = _topic;
    connect_async(host,     // non blocking connection to broker request
    port,
    keepalive);
    loop_start();            // Start thread managing connection / publish / subscribe
};

myMosq::~myMosq() {
    loop_stop();            // Kill the thread
    mosqpp::lib_cleanup();    // Mosquitto library cleanup
}

bool myMosq::send_message(const  char * _message, int _lenght)
{
    // Send message - depending on QoS, mosquitto lib managed re-submission this the thread
    //
    // * NULL : Message Id (int *) this allow to latter get status of each message
    // * topic : topic to be used
    // * lenght of the message
    // * message
    // * qos (0,1,2)
    // * retain (boolean) - indicates if message is retained on broker or not
    // Should return MOSQ_ERR_SUCCESS
    int ret = publish(NULL,this->topic,_lenght,_message,1,false);
    return ( ret == MOSQ_ERR_SUCCESS );
}

void myMosq::on_disconnect(int rc) {
    std::cout << ">> myMosq - disconnection(" << rc << ")" << std::endl;
}

void myMosq::on_connect(int rc)
{
    if ( rc == 0 ) {
        std::cout << ">> myMosq - connected with server" << std::endl;
    } else {
        std::cout << ">> myMosq - Impossible to connect with server(" << rc << ")" << std::endl;
    }
}

void myMosq::on_publish(int mid)
 {
    std::cout << ">> myMosq - Message (" << mid << ") succeed to be published " << std::endl;
 }

 int main(int argc, char* argv[]) {

    unique_ptr<myMosq> mqttInterface = make_unique<myMosq>("mqtt_receiver_test", "irimage", "192.168.0.34", 1883);

    char * str = "hello";
    //mqttInterface->send_message(str, strlen(str));

    ifstream fs = ifstream("example.bin", std::ios::out | std::ios::binary);

    bool flag = true;

    const int length = 221184;
    char buffer[length];

    int count = 0;
    while(flag) {

        fs.read (buffer,length);
        if (fs) {
            cout << "all characters read successfully." << endl;
            mqttInterface->send_message(buffer, length);
        }

        else {
            cout << "error: only " << fs.gcount() << " could be read" << endl;
            fs.clear();
            fs.seekg(ios::beg);
            count ++;
            if (count >= 15)
                flag = false;
        }

        usleep(100000);

    }

    int key;
    cin >> key;
    fs.close();
    mqttInterface->disconnect();

    return 0;

}