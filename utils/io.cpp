//
// Created by Carlos on 01/05/2021.
//

#include "io.h"

namespace io {
    namespace output {
        void error(const char *msg, ...) {
            va_list args;
            char buffer[1024];
            va_start(args, msg);
            vsnprintf(buffer, sizeof(buffer), msg, args);
            printf("%s[ERROR]%s %s\n", BOLDRED.c_str(), RESET.c_str(), msg);
            va_end(args);
        }

        void info(const char *msg, ...) {
            va_list args;
            char buffer[1024];
            va_start(args, msg);
            vsnprintf(buffer, sizeof(buffer), msg, args);
            printf("%s[INFO]%s %s\n", BOLDBLUE.c_str(), RESET.c_str(), buffer);
            va_end(args);
        }

        /**
         * Colorizes only the type of the message, i.e. [INFO]
         * @param color
         * @param newLine
         * @param messageType
         * @param message
         */
        void custom(std::string color, bool newLine, const std::string &messageType, const std::string& message) {
            printf("%s[%s]%s %s%c", color.c_str(), messageType.c_str(), RESET.c_str(), message.c_str(), newLine ? '\n' : '\0');
        }

        /**
         * Colorizes the entire string.
         * @param color
         * @param newLine
         * @param messageType
         * @param message
         */
        void custom(std::string color, bool newLine, const std::string& message) {
            printf("%s%s%s%c", color.c_str(), message.c_str(), RESET.c_str(), newLine ? '\n' : '\0');
        }

        void divider(bool empty) {
            if (empty) {
                printf("\n");
            } else {
                io::output::custom(io::WHITE, true, "=============================================");
            }
        }

        void flushScreen() {
            printf("\n\r");
        }
    }

    namespace input {
        void getString(std::string& destination, const std::string& prompt) {
            io::output::custom(io::BOLDYELLOW, false, "string", prompt);
            std::string temp;
            std::getline(std::cin, temp, '\n');
            destination = temp;
        }

        void getChar(char& destination, const std::string& prompt) {
            io::output::custom(io::BOLDYELLOW, false, "string", prompt);
            std::string temp;
            std::getline(std::cin, temp, '\n');
            destination = temp.at(0);
        }

        void getInt(int& destination, const std::string& prompt) {
            output::custom(BOLDYELLOW, false, "int", prompt);
            std::string temp;
            std::getline(std::cin, temp, '\n');
            destination = std::stoi(temp);
        }
    }
}

