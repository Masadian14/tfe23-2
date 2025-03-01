#include "mqtt_notification.h"
#include <mqtt/client.h>
#include <iostream>

const std::string SERVER_ADDRESS = "tcp://broker.hivemq.com:1883"; // MQTT-Broker (kann geändert werden)
const std::string CLIENT_ID = "fuel_price_notifier";

void sendMQTTNotification(const std::string& topic, const std::string& message) {
    try {
        mqtt::client client(SERVER_ADDRESS, CLIENT_ID);
        client.connect();
        
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
        pubmsg->set_qos(1); // QoS 1: Mindestens einmal senden
        client.publish(pubmsg);
        
        client.disconnect();
        std::cout << "MQTT Notification sent to topic: " << topic << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "MQTT Error: " << e.what() << std::endl;
    }
}
