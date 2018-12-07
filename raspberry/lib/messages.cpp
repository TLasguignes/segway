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
 * File:   messages.cpp
 * Author: dimercur
 * 
 * Created on 22 novembre 2018, 15:18
 */

#include "messages.h"
#include <exception>
#include <stdexcept>
#include <string>

using std::exception;

const string MESSAGE_ID_STRING[] = {
    "Angle Position",
    "Angular Speed",
    "Linear Speed",
    "Battery",
    "Beta",
    "Torque",
    "User Presence",
    "Emergency Stop",
    "Log",
    "Empty"
};

Message::Message() {
    this->messageID = MESSAGE_EMPTY;
}

Message::~Message() {
}

string Message::ToString() {
    if (CheckID(this->messageID))
        return "Id: \"" + MESSAGE_ID_STRING[this->messageID] + "\"";
    else
        return "Invalid message";
}

Message* Message::Copy() {
    Message *msg = new Message();

    return msg;
}

bool Message::CheckID(MESSAGE_ID id) {
    if ((id != MESSAGE_EMPTY)) {
        return false;
    } else return true;
}

// class MessageFloat
MessageFloat::MessageFloat() {
    value = 0.0;
}

MessageFloat::MessageFloat(MESSAGE_ID id, float val) {
    MessageFloat::SetID(id);
        
    value = val;
}

void MessageFloat::SetID(MESSAGE_ID id) {
    if (CheckID(id))
        messageID = id;
    else
        throw std::runtime_error{"Invalid message id for MessageFloat"};
}

string MessageFloat::ToString() {
    if (CheckID(this->messageID))
        return "Id: \"" + MESSAGE_ID_STRING[this->messageID] + "\"\nValue: " + to_string(this->value);
    else
        return "Invalid message";
}

Message* MessageFloat::Copy() {
    return new MessageFloat(this->messageID, this->value);
}

bool MessageFloat::CheckID(MESSAGE_ID id) {
    if ((id != MESSAGE_ANGLE_POSITION) &&
            (id != MESSAGE_ANGULAR_SPEED) &&
            (id != MESSAGE_BATTERY) &&
            (id != MESSAGE_BETA) &&
            (id != MESSAGE_LINEAR_SPEED) &&
            (id != MESSAGE_TORQUE)) {
        return false;
    } else return true;
}

// class MessageString
MessageString::MessageString() {
    s=string("");
}

MessageString::MessageString(MESSAGE_ID id, string s) {
    MessageString::SetID(id);
        
    this->s = s;
}

void MessageString::SetID(MESSAGE_ID id) {
    if (CheckID(id))
        messageID = id;
    else
        throw std::runtime_error{"Invalid message id for MessageString"};
}

string MessageString::ToString() {
    if (CheckID(this->messageID))
        return "Id: \"" + MESSAGE_ID_STRING[this->messageID] + "\"\nString: \"" + this->s + "\"";
    else
        return "Invalid message";
}

Message* MessageString::Copy() {
    return new MessageString(this->messageID, this->s);
}

bool MessageString::CheckID(MESSAGE_ID id) {
    if ((id != MESSAGE_LOG)) {
        return false;
    } else return true;
}

// class MessageBool
MessageBool::MessageBool() {
    state=false;
}

MessageBool::MessageBool(MESSAGE_ID id, bool state) {
    MessageBool::SetID(id);
    
    this->state = state;
}

void MessageBool::SetID(MESSAGE_ID id) {
    if (CheckID(id))
        messageID = id;
    else
        throw std::runtime_error{"Invalid message id for MessageBool"};
}

string MessageBool::ToString() {
    if (CheckID(this->messageID))
        return "Id: \"" + MESSAGE_ID_STRING[this->messageID] + "\"\nState: \"" + to_string(this->state) + "\"";
    else
        return "Invalid message";
}

Message* MessageBool::Copy() {
    return new MessageBool(this->messageID, this->state);
}

bool MessageBool::CheckID(MESSAGE_ID id) {
    if ((id != MESSAGE_EMERGENCY_STOP) &&
        (id != MESSAGE_USER_PRESENCE)) {
        return false;
    } else return true;
}
