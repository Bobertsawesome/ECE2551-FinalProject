#include "Message.h"
#include <Arduino.h>
#include <string.h>


Message::Message(){
    // Initialize all UUID arrays with zeros
    memset(toUUID, 0, UUID_LENGTH);
    memset(fromUUID, 0, UUID_LENGTH);
    // Initialize payload and length to zero
    payload = 0;
    payloadLength = 0;
}

Message::Message(const uint8_t* from, const uint8_t* to, uint16_t payload, uint8_t length){
    // Set sender UUID
    setFrom(from);
    // Set receiver UUID
    setTo(to);
    // Set binary payload
    setPayload(payload);
    // Set payload length
    setLength(length);
}

Message::Message(const uint8_t* from, uint8_t* to, const char* message){
    // Set sender UUID
    setFrom(from);
    // Set receiver UUID
    setTo(to);
    // Convert string message to binary payload (max 16 characters)
    setPayload(stringtoPayload(message, 16));
    // Set length based on message string length
    setLength(LENTHMSG(message));
}

void Message::setTo(const uint8_t* to){
    // Copy UUID_LENGTH (5) bytes from to array to toUUID member
    memcpy(toUUID, to, UUID_LENGTH);
}

void Message::setFrom(const uint8_t* from){
    // Copy UUID_LENGTH (5) bytes from from array to fromUUID member
    memcpy(fromUUID, from, UUID_LENGTH);
}

void Message::setPayload(uint16_t p){
    // Set the binary payload value
    payload = p;
}

char* Message::getPayloadString() const{
    // Use static method to convert this message's payload to string
    return payloadtoString(payload, payloadLength);
}

uint16_t Message::stringtoPayload(const char* message, uint8_t maxLen){
    uint16_t result = 0;

    // Iterate through message string (up to maxLen characters)
    for (uint8_t i = 0; i < maxLen && message[i] != '\0'; i++) {
        // Check if character is a dash
        if (message[i] == '-') {
            // Set bit at position i to 1 (dash)
            result |= (1 << i);
        }
        // If character is '.', bit stays 0 (dot) - no action needed
    }

    return result;
}

char* Message::payloadtoString(uint16_t payload, uint8_t length){
    // Allocate memory for string (length + 1 for null terminator)
    char* result = new char[length + 1];

    // Decode each bit position to a character
    for (uint8_t i = 0; i < length; i++) {
        // Check if bit at position i is set
        if (payload & (1 << i)) {
            result[i] = '-';  // Bit is 1, so it's a dash
        } else {
            result[i] = '.';  // Bit is 0, so it's a dot
        }
    }

    // Null-terminate the string
    result[length] = '\0';

    return result;
}

uint8_t Message::LENTHMSG(const char* input){
    uint8_t count = 0;

    // Count characters in string (up to maximum of 16)
    while (input[count] != '\0' && count < 16) {
        count++;
    }

    return count;
}