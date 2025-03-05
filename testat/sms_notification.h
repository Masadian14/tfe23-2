#ifndef SMS_NOTIFICATION_H
#define SMS_NOTIFICATION_H

#include <string>

// Deklaration der Funktion zum Senden einer SMS-Benachrichtigung
void smsnotification(const std::string& phoneNumber, const std::string& message);

#endif // SMS_NOTIFICATION_H