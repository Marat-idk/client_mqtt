#include "ClientMqtt.h"
#include <cstdio>
#include <cstring>

#ifdef DEBUG
#include <iostream>
#endif

// using namespace mosqpp;

/**
 * @brief Конструктор создает новый клиентский интерфейс
 * @details mosquittopp вызывает функцию mosquitto_new
 * @param id - идентификатор клиента
 * @param host 
 * @param port 
 */
ClientMQTT::ClientMQTT(const char *id, const char *topic, int maxPayload) 
:mosquittopp(id)
,mTopic(topic)
,mMaxPayload(maxPayload)
{}

ClientMQTT::~ClientMQTT(){

}

/**
 * @brief 
 * @details mosquittopp::connect вызывает mosquitto_connect 
 * @param host 
 * @param port 
 * @return int 
 */
int ClientMQTT::connect(const char *host, UINT port) {
    return mosquittopp::connect(host, port);
}

/**
 * @brief Устанавлиет on_connect как вызываемую фунцию для mosquitto_connect_callback_set
 * @details mosquitto_connect_callback_set(mosquitto *mosq, void(*on_connect)(mosquitto *, void *, int)
 * вызывается, когда брокер отправляет тип сообщения CONNACK (Подтверждение успешного подключения)
 * @param rc - код возврата ответа соеденения. Значение rc равное 0 сигнализирует об успешном подключении
 */
void ClientMQTT::on_connect(int rc) {
    if (!rc) {
        #ifdef DEBUG
            std::cout << "Connected - code " << rc << std::endl;
        #endif
    }
}

/**
 * @brief Устанавлиет on_message как вызываемую фунцию для mosquitto_message_callback_set
 * @detailsmosquitto_message_callback_set(mosquitto *mosq, void (*on_message)(mosquitto *, void *, const mosquitto_message *)
 * вызывается при получении сообщения от брокера
 * @param message - данные сообщения. Эта переменная и связанная с ней память будут освобождены библиотекой после завершения обратного вызова. Клиент должен сделать копии всех необходимых ему данных
 */
void ClientMQTT::on_message(const mosquitto_message *message) {
    int payloadSize = mMaxPayload + 1;
    char buf[payloadSize];

    if(!strcmp(message->topic, mTopic.c_str()))
    {
        memcpy(buf, message->payload, mMaxPayload * sizeof(char));

        #ifdef DEBUG
            std::cout << buf << std::endl;
        #endif

        // Examples of messages for M2M communications...
        if (!strcmp(buf, "STATUS"))
        {
            snprintf(buf, payloadSize, "This is a Status Message...");
            publish(nullptr, mTopic.c_str(), strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Status Request Recieved." << std::endl;
            #endif
        }

        if (!strcmp(buf, "ON"))
        {
            snprintf(buf, payloadSize, "Turning on...");
            publish(nullptr, mTopic.c_str(), strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Request to turn on." << std::endl;
            #endif
        }

        if (!strcmp(buf, "OFF"))
        {
            snprintf(buf, payloadSize, "Turning off...");
            publish(nullptr, mTopic.c_str(), strlen(buf), buf);
            #ifdef DEBUG
                std::cout << "Request to turn off." << std:: endl;
            #endif
        }
    }
}

/**
 * @brief Устанавлиет on_subscribe как вызываемую фунцию для mosquitto_subscribe_callback_set
 * @details mosquitto_connect_callback_set(mosquitto *mosq, void(*on_connect)(mosquitto *, void *, int)
 * вызывается, когда брокер отвечает на запрос подписки
 * @param mid - идентификатор сообщения
 * @param qos_count - количество предоставленных подписок (размер granted_qos)
 * @param granted_qos - ассив целых чисел, указывающий предоставленное QoS для каждой из подписок
 */
void ClientMQTT::on_subscribe(int mid, int qos_count, const int *granted_qos) {
    #ifdef DEBUG
        std::cout << "Subscription succeeded." << std::endl;
    #endif
}