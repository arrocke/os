#include "log.h"
#include "serial.h"

// The output location for the log file.
#define LOG_COM COM1

// The level of logs to report.
#define LOG_LEVEL LOG_INFO

// Converts a log level int to a human readable string.
static char* log_level_string(uint8_t level) {
    switch (level) {
        case LOG_INFO:
            return "INFO";
        case LOG_DEBUG:
            return "DEBUG";
        case LOG_WARN:
            return "WARN";
        case LOG_ERROR:
            return "ERROR";
        default:
            return "(none)";
    }
}

// Initalizes the COM port used for the log.
void log_init() {
    serial_init(LOG_COM);
    log_println("Log initialized.", LOG_INFO);
}

// Prints a line with the log level to the log COM port
// if the message level is at least LOG_LEVEL.
void log_println(char const *msg, uint8_t level) {
    if (LOG_LEVEL >= level) {
        serial_print_string(LOG_COM, log_level_string(level));
        serial_print_string(LOG_COM, ": ");
        serial_print_string(LOG_COM, msg);
        serial_print_string(LOG_COM, "\n");
    }
}