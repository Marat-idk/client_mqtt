#include <iostream>
#include "ClientMqtt.h"

int main(){
    const char *clietID = "Client_ID";
    const char *host = "localhost";
    const char *topic = "EXAMPLE_TOPIC";
    int rc;
    ClientMQTT *client = nullptr;

    // вызывает mosquitto_lib_init
    // mosquitto_lib_init должна быть вызвана прежде, чем будут вызваны какие-либо другие функции
    mosqpp::lib_init();

    client = new ClientMQTT(clietID, topic);
    client->connect(host);

    while(true){
        rc = client->loop();
        if (rc) {
            client->reconnect();
        }
        else {
            client->subscribe(NULL, topic);
        }
    }

    // вызывается mosquitto_lib_cleanup функция очистки
    mosqpp::lib_cleanup();
    return 0;
}