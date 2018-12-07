/*
 * Copyright (C) 2018 dimercur
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

/**
 * Message ID defined for system communication
 * 
 * @brief List of available message ID
 * 
 */
enum MESSAGE_ID {
    MESSAGE_ANGLE_POSITION=0,
    MESSAGE_ANGULAR_SPEED,
    MESSAGE_LINEAR_SPEED,
    MESSAGE_BATTERY,
    MESSAGE_BETA,
    MESSAGE_TORQUE,
    MESSAGE_USER_PRESENCE,
    MESSAGE_EMERGENCY_STOP,
    MESSAGE_LOG,
    MESSAGE_EMPTY
};

using namespace std;

/**
 * Base class for messaging
 * 
 * @brief Base class for messaging
 * 
 */
class Message {
public:
    /**
     * Create a new, empty message
     */
    Message();
    
    /**
     * Destroy message
     */
    virtual ~Message();

    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    virtual string ToString();
    
    /**
     * Allocate a new mesage and copy contents of current message
     * @return A message, copy of current
     */
    virtual Message* Copy();
   
    /**
     * Get message ID
     * @return Current message ID
     */
    MESSAGE_ID GetID() { return messageID; }
    
    /**
     * Set message ID
     * @param id Message ID
     */
    virtual void SetID(MESSAGE_ID id) {}
    
    /**
     * Comparison operator
     * @param msg Message to be compared
     * @return true if message are equal, false otherwise
     */
    bool operator==(const Message& msg) {
        return (messageID == msg.messageID);
    }

    /**
     * Difference operator
     * @param msg Message to be compared
     * @return true if message are different, false otherwise
     */
    bool operator!=(const Message& msg) {
        return !(messageID == msg.messageID);
    }

protected:
    /**
     * Message identifier (@see MESSAGE_ID)
     */
    MESSAGE_ID messageID;
    
    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    virtual bool CheckID(MESSAGE_ID id);
};

/**
 * Message class for holding float value, based on Message class
 * 
 * @brief Float message class
 * 
 */
class MessageFloat : public Message {
public:
    /**
     * Create a new, empty float message
     */
    MessageFloat();
    
    /**
     * Create a new float message, with given ID and value
     * @param id Message ID
     * @param val Message value
     * @throw std::runtime_error if message ID is incompatible with float data
     */
    MessageFloat(MESSAGE_ID id, float val);
    
    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible with float data
     */
    void SetID(MESSAGE_ID id);
    
    /**
     * Get message value (float)
     * @return Float value
     */
    float GetValue() { return value; }
    
    /**
     * Set message value (float)
     * @param val Float value to store in message
     */
    void SetValue(float val) { this->value = val; }
    
    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();
    
    /**
     * Allocate a new mesage and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();
    
protected:
    /**
     * Message float value
     */
    float value;
    
    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MESSAGE_ID id);
};

/**
 * Message class for holding string value, based on Message class
 * 
 * @brief String message class
 * 
 */
class MessageString: public Message {
public:
    /**
     * Create a new, empty string message
     */
    MessageString();
    
    /**
     * Create a new string message, with given ID and string
     * @param id Message ID
     * @param s Message string
     * @throw std::runtime_error if message ID is incompatible with string data
     */
    MessageString(MESSAGE_ID id, string s);
    
    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible with string data
     */
    void SetID(MESSAGE_ID id);
    
    /**
     * Get message string
     * @return String
     */
    string GetString() { return s; }
    
    /**
     * Set message string
     * @param s String to store in message
     */
    void SetString(string s) { this->s = s; }
    
    /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();
    
    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();
    
protected:
    /**
     * Message content
     */
    string s;
    
    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MESSAGE_ID id);
};

/**
 * Message class for holding boolean value, based on Message class
 * 
 * @brief Boolean message class
 * 
 */
class MessageBool : public Message {
public:
    /**
     * Create a new, empty boolean message
     */
    MessageBool();
    
    /**
     * Create a new boolean message, with given ID and boolean value
     * @param id Message ID
     * @param state Boolean value
     * @throw std::runtime_error if message ID is incompatible with boolean data
     */
    MessageBool(MESSAGE_ID id, bool state);
    
    /**
     * Set message ID
     * @param id Message ID
     * @throw std::runtime_error if message ID is incompatible with boolean data
     */
    void SetID(MESSAGE_ID id);
    
    /**
     * Get message state
     * @return Boolean state
     */
    bool GetState() { return state; }
    
    /**
     * Set message state
     * @param state Boolean state to store in message
     */
    void SetState(bool state) { this->state = state; }
    
     /**
     * Translate content of message into a string that can be displayed
     * @return A string describing message contents
     */
    string ToString();
    
    /**
     * Allocate a new message and copy contents of current message
     * @return A message, copy of current
     */
    Message* Copy();
    
protected:
    /**
     * Message state
     */
    bool state;
    
    /**
     * Verify if message ID is compatible with current message type
     * @param id Message ID
     * @return true, if message ID is acceptable, false otherwise
     */
    bool CheckID(MESSAGE_ID id);
};

#endif /* __MESSAGES_H__ */

