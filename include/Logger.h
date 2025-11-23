#ifndef LOGGER_H
#define LOGGER_H
#include <Arduino.h>

inline void log_internal(String function, String variable_name, String value) {
    Serial.print("[");
    Serial.print(function);
    Serial.print("] ");
    Serial.print(variable_name);
    Serial.print(": ");
    Serial.println(value);
}

#define LOG_VAR(var) log_internal(__func__, #var, String(var))
#define LOG_STR(var) log_internal(__func__, "", String(var))

#endif
