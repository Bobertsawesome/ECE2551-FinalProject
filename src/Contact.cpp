#include "Contact.h"
#include <string.h>
#include <Arduino.h>

Contact::Contact(){
    // Initialize UUID array with zeros
    memset(uuid, 0, UUID_LEN);
    // Initialize name array with zeros (empty string)
    memset(name, 0, NAME_LEN);
}

Contact::Contact(const uint8_t* givenUUID, const char* givenName){
    // Copy UUID from given array
    setUUID(givenUUID);
    // Copy name from given string (with truncation if needed)
    setName(givenName);
}

// Single character name constructor: Initialize contact with UUID and single char
Contact::Contact(unsigned char* givenUUID, char givenName){
    // Copy UUID from given array
    setUUID(givenUUID);
    // Initialize name with zeros
    memset(name, 0, NAME_LEN);
    // Set first character of name to given char
    name[0] = givenName;
}

void Contact::setUUID(const uint8_t* givenUUID){
    // Copy UUID_LEN (5) bytes from given array to uuid member
    memcpy(uuid, givenUUID, UUID_LEN);
}

void Contact::setName(const char* givenName){
    // Initialize name array with zeros first
    memset(name, 0, NAME_LEN);

    // Copy up to NAME_LEN-1 (9) characters to leave room for null terminator
    // This automatically truncates if givenName is longer than 9 characters
    strncpy(name, givenName, NAME_LEN - 1);

    // Ensure null termination (strncpy may not null-terminate if source is too long)
    name[NAME_LEN - 1] = '\0';
}
