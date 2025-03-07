#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <nlohmann/json.hpp>
#include <limits>
#include "sms_notification.h"
#include "email_notification.h"
#include "mqtt_notification.h"

// Deklariere die getesteten Funktionen (aus der main.cpp)
std::string fuelprices(const std::string& apiKey, const std::string& lat, const std::string& lng, const std::string& radius, const std::string& fuelType);
std::string stationdetails(const std::string& apiKey, const std::string& stationId);

// Beispiel für einen Mock einer API-Antwort
std::string mock_fuelprices_response() {
    return R"({
        "ok": true,
        "stations": [
            { "id": "123", "name": "Tankstelle A", "place": "Berlin", "price": 1.50 },
            { "id": "456", "name": "Tankstelle B", "place": "München", "price": 1.55 }
        ]
    })";
}

TEST_CASE("JSON-Parsing für fuelprices", "[fuelprices]") {
    std::string response = mock_fuelprices_response();
    auto jsonResponse = nlohmann::json::parse(response);

    REQUIRE(jsonResponse["ok"] == true);
    REQUIRE(jsonResponse["stations"].size() == 2);
    REQUIRE(jsonResponse["stations"][0]["name"] == "Tankstelle A");
    REQUIRE(jsonResponse["stations"][0]["price"] == 1.50);
}

TEST_CASE("Station Details JSON-Parsing", "[stationdetails]") {
    std::string response = R"({
        "ok": true,
        "station": {
            "id": "123",
            "name": "Tankstelle A",
            "street": "Hauptstraße 1",
            "place": "Berlin"
        }
    })";

    auto jsonResponse = nlohmann::json::parse(response);

    REQUIRE(jsonResponse["ok"] == true);
    REQUIRE(jsonResponse["station"]["name"] == "Tankstelle A");
    REQUIRE(jsonResponse["station"]["place"] == "Berlin");
}

