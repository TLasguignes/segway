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

/**
 * \author INSA Toulouse
 * \version 1.0
 * \date 20 Mai 2017
 */

#ifndef __COM_STM32_H__
#define __COM_STM32_H__

#include "messages.h"

using namespace std;

class ComStm32 {
public:
    ComStm32() {}
    virtual ~ComStm32() {}
    
    int Open();
    int Close();
    
    bool GetComState() { return lostCom; }
    
    Message* Read();
    int Write(Message* msg);
    
    virtual void Read_Pre() {}
    virtual void Read_Post() {}
    virtual void Write_Pre() {}
    virtual void Write_Post() {}
    
protected:
    bool lostCom = false;
    int fd;
    
    float CharToFloat(unsigned char *bytes);
    bool CharToBool(unsigned char *bytes);
    unsigned int CharToInt(unsigned char *bytes);
    
    Message* CharToMessage(unsigned char *bytes);
    void MessageToChar(Message *msg, unsigned char *buffer);
};

#endif /* __COM_STM32_H__ */
