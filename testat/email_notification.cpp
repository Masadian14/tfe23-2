#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include "email_notification.h"

size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    std::string* data = reinterpret_cast<std::string*>(userp);
    size_t len = data->size() < size * nmemb ? data->size() : size * nmemb;
    memcpy(ptr, data->c_str(), len);
    data->erase(0, len);
    return len;
}

// Funktion zum Senden einer E-Mail-Benachrichtigung
void sendEmailNotification(const std::string& recipient, const std::string& subject, const std::string& message) {
    CURL* curl;
    CURLcode res;

    struct curl_slist* recipients = NULL;

    curl = curl_easy_init();
    if (curl) {
        // SMTP-Server und Port für Gmail (TLS)
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); // Verwenden von TLS

        // Anmeldedaten für Gmail
        curl_easy_setopt(curl, CURLOPT_USERNAME, "nichtsnichts68@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "meke biye wdzj yhmi");

        // Absenderadresse
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<nichtsnichts68@gmail.com>");
        recipients = curl_slist_append(recipients, recipient.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // E-Mail-Nachricht formatieren
        std::string emailData = "To: " + recipient + "\r\n" +
                                "From: <nichtsnichts68@gmail.com>\r\n" +
                                "Subject: " + subject + "\r\n" +
                                "\r\n" + message + "\r\n";

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &emailData);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Debugging-Ausgabe vor dem Senden der E-Mail
        std::cout << "Sending email to: " << recipient << std::endl;
        std::cout << "Subject: " << subject << std::endl;
        std::cout << "Message: " << message << std::endl;

        // Aktivieren von Debugging-Ausgaben in libcurl
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            // Zusätzliche Debugging-Informationen ausgeben
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            std::cerr << "Response code: " << response_code << std::endl;
        } else {
            std::cout << "Email sent successfully!" << std::endl;
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}