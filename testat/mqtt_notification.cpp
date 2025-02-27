#include "mqtt_notification.h"
#include <iostream>
#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS("tcp://mqtt.example.com:1883");
const std::string CLIENT_ID("mqtt_client_id");

void sendMQTTNotification(const std::string& topic, const std::string& message) {
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to the MQTT server..." << std::endl;
        auto connTok = client.connect(connOpts);
        connTok->wait();
        std::cout << "Connected" << std::endl;

        mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
        pubmsg->set_qos(1);

        std::cout << "Sending message..." << std::endl;
        auto pubTok = client.publish(pubmsg);
        pubTok->wait();
        std::cout << "Message sent" << std::endl;

        std::cout << "Disconnecting from the MQTT server..." << std::endl;
        auto discTok = client.disconnect();
        discTok->wait();
        std::cout << "Disconnected" << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << std::endl;
    }
}