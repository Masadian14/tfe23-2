#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "sms_notification.h"
#include "email_notification.h"

// Callback-Funktion für libcurl zum Speichern der HTTP-Antwort in einem String
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Funktion zum Abrufen der Spritpreise
std::string getFuelPrices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/list.php?lat=" + lat 
                        + "&lng=" + lng + "&rad=" + radius + "&sort=price&type=" + fuelType + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

// Funktion zum Abrufen der Details einer Tankstelle
std::string getStationDetails(const std::string& apiKey, const std::string& stationId) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://creativecommons.tankerkoenig.de/json/detail.php?id=" + stationId + "&apikey=" + apiKey;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

int main() {
    std::string apiKey = "6548316a-6bce-f3cc-b70d-5560b29485aa";
    std::string lat = "47.6561"; // Breitengrad für Friedrichshafen
    std::string lng = "9.4797";  // Längengrad für Friedrichshafen
    std::string radius = "4"; // Radius in Kilometern
    std::string fuelType = "diesel"; // Kraftstofftyp: diesel, e5, e10

    // Abrufen der Tankstellenliste
    std::string fuelPricesResponse = getFuelPrices(apiKey, lat, lng, radius, fuelType);
    auto fuelPricesJson = nlohmann::json::parse(fuelPricesResponse);

    if (fuelPricesJson.contains("ok") && fuelPricesJson["ok"]) {
        auto stations = fuelPricesJson["stations"];
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
                      << " with price: " << cheapestStation["price"] << std::endl;

            // Abrufen der Details der günstigsten Tankstelle
            std::string stationId = cheapestStation["id"];
            std::string stationDetailsResponse = getStationDetails(apiKey, stationId);
            auto stationDetailsJson = nlohmann::json::parse(stationDetailsResponse);

            if (stationDetailsJson.contains("ok") && stationDetailsJson["ok"]) {
                std::cout << "Station Details: " << stationDetailsJson.dump(4) << std::endl;
                
                // Benachrichtigung per SMS senden
                std::string phoneNumber = "+491234567890"; // Beispiel-Telefonnummer
                std::string smsMessage = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                sendSMSNotification(phoneNumber, smsMessage);

                // Benachrichtigung per E-Mail senden
                std::string emailRecipient = "maxikom@hotmail.com"; // Beispiel-E-Mail-Adresse
                std::string emailSubject = "Günstigste Tankstelle gefunden";
                std::string emailBody = "Die günstigste Tankstelle ist " + cheapestStation["name"].get<std::string>() + " mit einem Preis von " + std::to_string(cheapestStation["price"].get<double>()) + " EUR.";
                sendEmailNotification(emailRecipient, emailSubject, emailBody);
            } else {
                std::cerr << "Error: " << stationDetailsJson["message"] << std::endl;
            }
        } else {
            std::cout << "No stations found." << std::endl;
        }
    } else {
        std::cerr << "Error: " << fuelPricesJson["message"] << std::endl;
    }

    return 0;
}