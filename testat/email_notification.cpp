#include "email_notification.h"
#include <curl/curl.h>
#include <iostream>

void sendEmailNotification(const std::string& recipient, const std::string& subject, const std::string& message) {
    CURL* curl;
    CURLcode res;

    struct curl_slist* recipients = NULL;
    const char* payload_text = message.c_str();

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, "nichtsnichts68@gmail.com"); // Ihre Gmail-Adresse
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "your_password"); // Ihr Gmail-App-Passwort
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587"); // SMTP-Server und Port für Gmail

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "<nichtsnichts68@gmail.com>");
        recipients = curl_slist_append(recipients, recipient.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // E-Mail-Nachricht formatieren
        std::string emailData = "To: " + recipient + "\r\n" +
                                "From: <nichtsnichts68@gmail.com>\r\n" +
                                "Subject: " + subject + "\r\n" +
                                "\r\n" + message + "\r\n";

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, [](void *ptr, size_t size, size_t nmemb, void *userp) -> size_t {
            std::string* data = reinterpret_cast<std::string*>(userp);
            size_t len = data->size() < size * nmemb ? data->size() : size * nmemb;
            memcpy(ptr, data->c_str(), len);
            data->erase(0, len);
            return len;
        });

        curl_easy_setopt(curl, CURLOPT_READDATA, &emailData);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}