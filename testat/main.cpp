/**
 * @file main.cpp
 * @brief Program to determine the cheapest gas station within a specified area.
 */
/*
 #include <iostream>
 #include <string>
 #include <curl/curl.h>
 #include <nlohmann/json.hpp>
 #include "sms_notification.h"
 #include "email_notification.h"
 #include "mqtt_notification.h"
 
/**
 * @brief Callback function for receiving HTTP responses with libcurl.
 * @param content Pointer to the received data.
 * @param size Size of each data unit.
 * @param nmemb Number of data units.
 * @param userData Pointer to the string where the response will be stored.
 * @return Total size of the received data.
 */
/*
 size_t handleresponse(void* contents, size_t size, size_t nmemb, void* userp) {
     ((std::string*)userp)->append((char*)contents, size * nmemb);
     return size * nmemb;
 }
 
 /**
 * @brief Sends an HTTP request to the Tankerkönig API and returns the response.
 * 
 * @param apiKey API key for the Tankerkönig API.
 * @param latitude Latitude of the search area.
 * @param longitude Longitude of the search area.
 * @param searchRadius Search radius in kilometers.
 * @param fuelType Type of fuel (e.g., diesel, e5, e10).
 * @return JSON string containing the API response.
 */
/*
 std::string fuelprices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType) {
     CURL* curl;
     CURLcode res;
     std::string readBuffer;
 
     curl = curl_easy_init();
     if (curl) {
         std::string url = "https://creativecommons.tankerkoenig.de/json/list.php?lat=" + lat 
                         + "&lng=" + lng + "&rad=" + radius + "&sort=price&type=" + fuelType + "&apikey=" + apiKey;
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
         res = curl_easy_perform(curl);
         curl_easy_cleanup(curl);
     }
     return readBuffer;
 }
 
/**
 * @brief Retrieves detailed information about a specific gas station.
 * 
 * @param apiKey API key for the Tankerkönig API.
 * @param stationId Unique ID of the gas station.
 * @return JSON string containing gas station details.
 */
/*
 std::string stationdetails(const std::string& apiKey, const std::string& stationId) {
     CURL* curl;
     CURLcode res;
     std::string readBuffer;
 
     curl = curl_easy_init();
     if (curl) {
         std::string url = "https://creativecommons.tankerkoenig.de/json/detail.php?id=" + stationId + "&apikey=" + apiKey;
         curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
         res = curl_easy_perform(curl);
         curl_easy_cleanup(curl);
     }
     return readBuffer;
 }
 
/**
 * @brief Main program to find the cheapest gas station and send notifications.
 * @return 0 if the program runs successfully, otherwise an error code.
 */
/*
 int main() {
     std::string apiKey = "6548316a-6bce-f3cc-b70d-5560b29485aa";
     std::string lat = "47.6561"; // latitude for friedrichshafen
     std::string lng = "9.4797";  // longitude for friedrichshafen
     std::string radius = "4"; // radius in kilometers
     std::string fuelType = "diesel"; // fueltype diesel, e5, e10
 
     // retrieving stationlist data
     std::string fuelpricesresponse = fuelprices(apiKey, lat, lng, radius, fuelType);
     auto fuelpricesjson = nlohmann::json::parse(fuelpricesresponse);
 
     if (fuelpricesjson.contains("ok") && fuelpricesjson["ok"]) {
         auto stations = fuelpricesjson["stations"];
         double minPrice = std::numeric_limits<double>::max();
         nlohmann::json cheapestStation;
 
         // Search for the station with the lowest price
         for (const auto& station : stations) {
             if (station.contains("price") && station["price"] < minPrice) {
                 minPrice = station["price"];
                 cheapestStation = station;
             }
         }
 
         if (!cheapestStation.empty()) {
             std::cout << "Cheapest Station: " << cheapestStation["name"] 
                       << " at " << cheapestStation["place"] 
                       << " with price: " << cheapestStation["price"] << std::endl;
 
             // Retrieve details of the cheapest gas station
             std::string stationId = cheapestStation["id"];
             std::string stationDetailsResponse = stationdetails(apiKey, stationId);
             auto stationDetailsJson = nlohmann::json::parse(stationDetailsResponse);
 
             if (stationDetailsJson.contains("ok") && stationDetailsJson["ok"]) {
                 std::cout << "Station Details: " << stationDetailsJson.dump(4) << std::endl;
                 
                 // Send SMS notification
                 std::string phoneNumber = "+491234567890"; // Beispiel-Telefonnummer
                 std::string smsMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                          " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                 smsnotification(phoneNumber, smsMessage);
 
                 // Send email notification
                 std::string emailRecipient = "sultantbl@icloud.com"; // Beispiel-E-Mail-Adresse
                 std::string emailSubject = "Günstigste Tankstelle gefunden";
                 std::string emailBody = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                         " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                 emailnotification(emailRecipient, emailSubject, emailBody);
 
                 // Send MQTT notification
                 std::string mqttTopic = "fuel/cheapest_station";
                 std::string mqttMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() +
                                           " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                 mqttnotification(mqttTopic, mqttMessage);
                 
             } else {
                 std::cerr << "Error: " << stationDetailsJson["message"] << std::endl;
             }
         } else {
             std::cout << "No stations found." << std::endl;
         }
     } else {
         std::cerr << "Error: " << fuelpricesjson["message"] << std::endl;
     }
 
     return 0;
 }
 */

 /*#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "sms_notification.h"
#include "email_notification.h"
#include "mqtt_notification.h"

size_t handleresponse(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fuelprices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/list.php?lat=" + lat 
                        + "&lng=" + lng + "&rad=" + radius + "&sort=price&type=" + fuelType + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::string stationdetails(const std::string& apiKey, const std::string& stationId) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/detail.php?id=" + stationId + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

int main() {
    std::string apiKey, phoneNumber, emailRecipient;
    
    // API Key vom Benutzer abfragen
    std::cout << "Bitte geben Sie Ihren Tankerkönig API Key ein: ";
    std::getline(std::cin, apiKey);
    
    // Benutzereingabe für Telefonnummer und E-Mail-Adresse
    std::cout << "Bitte geben Sie Ihre Telefonnummer für SMS-Benachrichtigungen ein: ";
    std::getline(std::cin, phoneNumber);
    
    std::cout << "Bitte geben Sie Ihre E-Mail-Adresse für Benachrichtigungen ein: ";
    std::getline(std::cin, emailRecipient);

    std::string lat = "47.6561"; 
    std::string lng = "9.4797";  
    std::string radius = "4"; 
    std::string fuelType = "diesel"; 

    std::string fuelpricesresponse = fuelprices(apiKey, lat, lng, radius, fuelType);
    auto fuelpricesjson = nlohmann::json::parse(fuelpricesresponse);

    if (fuelpricesjson.contains("ok") && fuelpricesjson["ok"]) {
        auto stations = fuelpricesjson["stations"];
        double minPrice = std::numeric_limits<double>::max();
        nlohmann::json cheapestStation;

        for (const auto& station : stations) {
            if (station.contains("price") && station["price"] < minPrice) {
                minPrice = station["price"];
                cheapestStation = station;
            }
        }

        if (!cheapestStation.empty()) {
            std::cout << "Cheapest Station: " << cheapestStation["name"] 
                      << " at " << cheapestStation["place"] 
                      << " with price: " << cheapestStation["price"] << " EUR" << std::endl;

            std::string stationId = cheapestStation["id"];
            std::string stationDetailsResponse = stationdetails(apiKey, stationId);
            auto stationDetailsJson = nlohmann::json::parse(stationDetailsResponse);

            if (stationDetailsJson.contains("ok") && stationDetailsJson["ok"]) {
                std::cout << "Station Details: " << stationDetailsJson.dump(4) << std::endl;

                std::string notificationMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                                  " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";

                // SMS-Benachrichtigung senden
                smsnotification(phoneNumber, notificationMessage);

                // E-Mail-Benachrichtigung senden
                std::string emailSubject = "Günstigste Tankstelle gefunden";
                emailnotification(emailRecipient, emailSubject, notificationMessage);

                // MQTT-Benachrichtigung senden
                std::string mqttTopic = "fuel/cheapest_station";
                mqttnotification(mqttTopic, notificationMessage);

            } else {
                std::cerr << "Error: " << stationDetailsJson["message"] << std::endl;
            }
        } else {
            std::cout << "No stations found." << std::endl;
        }
    } else {
        std::cerr << "Error: " << fuelpricesjson["message"] << std::endl;
    }

    return 0;
}
*/
/*
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "sms_notification.h"
#include "email_notification.h"
#include "mqtt_notification.h"



size_t handleresponse(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fuelprices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/list.php?lat=" + lat 
                        + "&lng=" + lng + "&rad=" + radius + "&sort=price&type=" + fuelType + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::string stationdetails(const std::string& apiKey, const std::string& stationId) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/detail.php?id=" + stationId + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

void countdown(int seconds) {
    for (int i = seconds; i > 0; --i) {
        std::cout << "\rNächste Anfrage in: " << i << " Sekunden...  " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\nSie können jetzt eine neue Anfrage senden!\n";
}

int main() {
    std::string apiKey, phoneNumber, emailRecipient;
    
    // API Key vom Benutzer abfragen
    std::cout << "Bitte geben Sie Ihren Tankerkönig API Key ein: ";
    std::getline(std::cin, apiKey);
    
    // Benutzereingabe für Telefonnummer und E-Mail-Adresse
    std::cout << "Bitte geben Sie Ihre Telefonnummer für SMS-Benachrichtigungen ein: ";
    std::getline(std::cin, phoneNumber);
    
    std::cout << "Bitte geben Sie Ihre E-Mail-Adresse für Benachrichtigungen ein: ";
    std::getline(std::cin, emailRecipient);

    std::string lat = "47.6561"; 
    std::string lng = "9.4797";  
    std::string radius = "4"; 
    std::string fuelType = "diesel"; 

    while (true) {
        std::string fuelpricesresponse = fuelprices(apiKey, lat, lng, radius, fuelType);
        auto fuelpricesjson = nlohmann::json::parse(fuelpricesresponse);
    
        if (fuelpricesjson.contains("ok") && fuelpricesjson["ok"]) {
            auto stations = fuelpricesjson["stations"];
            double minPrice = std::numeric_limits<double>::max();
            nlohmann::json cheapestStation;
    
            for (const auto& station : stations) {
                if (station.contains("price") && station["price"] < minPrice) {
                    minPrice = station["price"];
                    cheapestStation = station;
                }
            }
    
            if (!cheapestStation.empty()) {
                std::cout << "Cheapest Station: " << cheapestStation["name"] 
                          << " at " << cheapestStation["place"] 
                          << " with price: " << cheapestStation["price"] << " EUR" << std::endl;
    
                std::string stationId = cheapestStation["id"];
                std::string stationDetailsResponse = stationdetails(apiKey, stationId);
                auto stationDetailsJson = nlohmann::json::parse(stationDetailsResponse);
    
                if (stationDetailsJson.contains("ok") && stationDetailsJson["ok"]) {
                    std::cout << "Station Details: " << stationDetailsJson.dump(4) << std::endl;
    
                    std::string notificationMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                                      " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
    
                    // SMS-Benachrichtigung senden
                    smsnotification(phoneNumber, notificationMessage);
    
                    // E-Mail-Benachrichtigung senden
                    std::string emailSubject = "Günstigste Tankstelle gefunden";
                    emailnotification(emailRecipient, emailSubject, notificationMessage);
    
                    // MQTT-Benachrichtigung senden
                    std::string mqttTopic = "fuel/cheapest_station";
                    mqttnotification(mqttTopic, notificationMessage);
                } else {
                    std::cerr << "Error: " << stationDetailsJson["message"] << std::endl;
                }
            } else {
                std::cout << "No stations found." << std::endl;
            }
        } else {
            std::cerr << "Error: " << fuelpricesjson["message"] << std::endl;
        }
    
        // Countdown von 2 Sekunden für Tests
        countdown(2);
    
        // Puffer leeren, falls vorher noch Eingaben offen sind
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
        // Benutzer fragen, ob eine neue Anfrage gesendet werden soll
        std::string userInput;
        while (true) {
            std::cout << "Möchten Sie eine neue Anfrage senden? (ja/nein): ";
            std::getline(std::cin, userInput);
    
            // Leerzeichen entfernen, um Probleme zu vermeiden
            userInput.erase(std::remove_if(userInput.begin(), userInput.end(), ::isspace), userInput.end());
    
            if (userInput == "ja") {
                break;  // Neue Anfrage wird gesendet
            } else if (userInput == "nein") {
                std::cout << "Programm beendet.\n";
                return 0; // Beende das Programm
            } else {
                std::cout << "Ungültige Eingabe. Bitte 'ja' oder 'nein' eingeben.\n";
            }
        }
    }
    
    
}
    

*/

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "sms_notification.h"
#include "email_notification.h"
#include "mqtt_notification.h"

size_t handleresponse(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fuelprices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/list.php?lat=" + lat 
                        + "&lng=" + lng + "&rad=" + radius + "&sort=price&type=" + fuelType + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::string stationdetails(const std::string& apiKey, const std::string& stationId) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/detail.php?id=" + stationId + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

void countdown(int seconds) {
    for (int i = seconds; i > 0; --i) {
        std::cout << "\rNächste Anfrage in: " << i << " Sekunden...  " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\nSie können jetzt eine neue Anfrage senden!\n";
}

std::pair<std::string, std::string> getCoordinates(const std::string& location) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://nominatim.openstreetmap.org/search?format=json&q=" + location;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, handleresponse);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0"); // Nominatim braucht einen User-Agent
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    auto jsonResponse = nlohmann::json::parse(readBuffer);
    if (!jsonResponse.empty()) {
        std::string lat = jsonResponse[0]["lat"].get<std::string>();
        std::string lon = jsonResponse[0]["lon"].get<std::string>();
        return {lat, lon};
    } else {
        std::cerr << "Fehler: Ort konnte nicht gefunden werden!" << std::endl;
        return {"0", "0"};
    }
}

int main() {
    std::string apiKey, phoneNumber, emailRecipient, location;

    // API Key vom Benutzer abfragen
    std::cout << "Bitte geben Sie Ihren Tankerkönig API Key ein: ";
    std::getline(std::cin, apiKey);

    // Benutzereingabe für Telefonnummer und E-Mail-Adresse
    std::cout << "Bitte geben Sie Ihre Telefonnummer für SMS-Benachrichtigungen ein: ";
    std::getline(std::cin, phoneNumber);

    std::cout << "Bitte geben Sie Ihre E-Mail-Adresse für Benachrichtigungen ein: ";
    std::getline(std::cin, emailRecipient);

    // 🟢 NEU: Benutzereingabe für den Ort
    std::cout << "Bitte geben Sie den gewünschten Ort ein: ";
    std::getline(std::cin, location);

    // 🟢 NEU: Koordinaten aus Ortsnamen abrufen
    auto [lat, lng] = getCoordinates(location);
    
    // Falls der Ort ungültig ist, Programm beenden
    if (lat == "0" && lng == "0") {
        std::cerr << "Fehler: Ungültiger Ort! Bitte versuchen Sie es erneut." << std::endl;
        return 1;
    }

    std::cout << "Ermittelte Koordinaten für " << location << ": Latitude = " << lat << ", Longitude = " << lng << std::endl;

    std::string radius = "4"; 
    std::string fuelType = "diesel"; 

    while (true) {
        std::string fuelpricesresponse = fuelprices(apiKey, lat, lng, radius, fuelType);
        auto fuelpricesjson = nlohmann::json::parse(fuelpricesresponse);

        if (fuelpricesjson.contains("ok") && fuelpricesjson["ok"]) {
            auto stations = fuelpricesjson["stations"];
            double minPrice = std::numeric_limits<double>::max();
            nlohmann::json cheapestStation;

            for (const auto& station : stations) {
                if (station.contains("price") && station["price"] < minPrice) {
                    minPrice = station["price"];
                    cheapestStation = station;
                }
            }

            if (!cheapestStation.empty()) {
                std::cout << "Cheapest Station: " << cheapestStation["name"] 
                          << " at " << cheapestStation["place"] 
                          << " with price: " << cheapestStation["price"] << " EUR" << std::endl;

                std::string stationId = cheapestStation["id"];
                std::string stationDetailsResponse = stationdetails(apiKey, stationId);
                auto stationDetailsJson = nlohmann::json::parse(stationDetailsResponse);

                if (stationDetailsJson.contains("ok") && stationDetailsJson["ok"]) {
                    std::cout << "Station Details: " << stationDetailsJson.dump(4) << std::endl;

                    std::string notificationMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + 
                                                      " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";

                    // SMS-Benachrichtigung senden
                    smsnotification(phoneNumber, notificationMessage);

                    // E-Mail-Benachrichtigung senden
                    std::string emailSubject = "Günstigste Tankstelle gefunden";
                    emailnotification(emailRecipient, emailSubject, notificationMessage);

                    // MQTT-Benachrichtigung senden
                    std::string mqttTopic = "fuel/cheapest_station";
                    mqttnotification(mqttTopic, notificationMessage);

                } else {
                    std::cerr << "Error: " << stationDetailsJson["message"] << std::endl;
                }
            } else {
                std::cout << "No stations found." << std::endl;
            }
        } else {
            std::cerr << "Error: " << fuelpricesjson["message"] << std::endl;
        }

        // 🟢 NEU: Statt Automatik fragen wir den Benutzer, ob er weitermachen will
        std::cout << "Möchten Sie eine neue Anfrage starten? (ja/nein): ";
        std::string userResponse;
        std::getline(std::cin, userResponse);
        if (userResponse != "ja") {
            break;
        }
    }

    return 0;
}
