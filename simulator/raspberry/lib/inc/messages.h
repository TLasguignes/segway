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

/* 
 * Author: dimercur
 *
 * Created on 22 novembre 2018, 15:18
 */

#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

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

class Message {
public:
    Message();
    virtual ~Message();

    virtual string ToString();
    virtual Message* Copy();
   
    MESSAGE_ID GetID() { return messageID; }
        
    bool operator==(const Message& msg) {
        return (messageID == msg.messageID);
    }

    bool operator!=(const Message& msg) {
        return !(messageID == msg.messageID);
    }

protected:
    MESSAGE_ID messageID;
    virtual bool CheckID(MESSAGE_ID id);
};

class MessageFloat : public Message {
public:
    MessageFloat();
    MessageFloat(MESSAGE_ID id, float val);
    
    void SetID(MESSAGE_ID id);
    float GetValue() { return value; }
    void SetValue(float val) { this->value = val; }
    
    string ToString();
    Message* Copy();
    
protected:
    float value;
    bool CheckID(MESSAGE_ID id);
};

class MessageString: public Message {
public:
    MessageString();
    MessageString(MESSAGE_ID id, string s);
    
    void SetID(MESSAGE_ID id);
    string GetString() { return s; }
    void SetString(string s) { this->s = s; }
    
    string ToString();
    Message* Copy();
    
protected:
    string s;
    bool CheckID(MESSAGE_ID id);
};

class MessageBool : public Message {
public:
    MessageBool();
    MessageBool(MESSAGE_ID id, bool state);
    
    void SetID(MESSAGE_ID id);
    bool GetState() { return state; }
    void SetState(bool state) { this->state = state; }
    
    string ToString();
    Message* Copy();
    
protected:
    bool state;
    bool CheckID(MESSAGE_ID id);
};

#endif /* __MESSAGES_H__ */

