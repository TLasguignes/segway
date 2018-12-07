/* 
 * File:   lib_serial.c
 * Author: INSA TOULOUSE
 *
 * Created on 10-07 2017
 */

#include "comstm32.h"

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>  

#include <string>
#include <stdexcept>

/**
        Initialize the serial port in order to send and receive messages through it
        @returns: the file descriptor, or -1 if there was an error. 
        (Retreiving the file descriptor is not necessary as it is not an argument of any function of the library)

 */

#define MESSAGE_SERIAL_LENGTH 37
#define MESSAGE_TIMEOUT_NS 2000

#ifdef __FOR_PC__
#define USART_FILENAME "/dev/ttyUSB0"
#else
#define USART_FILENAME "/dev/ttyS0"
#endif /* __FOR_PC__ */

enum LABEL_STM32 {
    LABEL_ANGLE_POSITION = 'p',
    LABEL_ANGULAR_SPEED = 's',
    LABEL_BATTERY_LEVEL = 'b',
    LABEL_BETA_ANGLE = 'v',
    LABEL_USER_PRESENCE = 'u',

    LABEL_TORQUE = 'c',
    LABEL_EMERGENCY_STOP = 'a'
};

int ComStm32::Open() {
    fd = open(USART_FILENAME, O_RDWR | O_NOCTTY /*| O_NDELAY*/); //Open in non blocking read/write mode
    if (fd == -1) {
        //ERROR - CAN'T OPEN SERIAL PORT
        throw std::runtime_error{"Error - Unable to open UART "+ string(USART_FILENAME)+".  Ensure it is not in use by another application"};
        exit(EXIT_FAILURE);
    }

    //Configuration of the serial port 115 520 Bauds
    struct termios options;
    tcgetattr(fd, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD; //<Set baud rate
    options.c_iflag = IGNPAR; // ignores bytes with bad parity
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    return fd;
}

int ComStm32::Close() {
    return close(fd);
}

/**
        Reads a message from the serial port. 
        The function is blocked until a suitable message is received. 
 */
Message* ComStm32::Read() {
    int rxLength;
    unsigned char rxBuffer[6];
    unsigned char receivedChar;
    bool messageComplete = false;
    Message *msg;
    unsigned int i;

    /* Call pre method for read */
    Read_Pre();

    lostCom = false;
    /* a message is composed of 7 bytes.
                the byte 0 should always be '<'
                the byte 1 should be an ascii char that is the label. It define what the data represent
                the bytes 2 to 5 are the float value
                the byte 6 should always be a '\n'
     */
    while (messageComplete == false) {
        rxLength = read(this->fd, (void*) &receivedChar, 1); //Filestream, buffer to store in, number of bytes to read (max)
        //printf ("W=%02X ", receivedChar);

        if (rxLength <= -1) {
            this->lostCom = true;
            printf("Warning: communication lost in ComStm32::Read\n");
            msg = new Message();

            return msg;
        } else if (rxLength == 0) {
            // nothing to do
        } else if (receivedChar == '<') { // start of frame received
            //printf ("received Start\n");
            i = 0;

            do {
                rxLength = read(this->fd, (void*) &rxBuffer[i], 6 - i); //Filestream, buffer to store in, number of bytes to read (max)

                if (rxLength >= 0)
                    i = i + rxLength;
                else {
                    printf("Error while reading (%i)", rxLength);

                    return NULL;
                }
            }            while (i < 6);

            //printf ("data received (%i)\n", rxLength);

            if (rxBuffer[5] == '\n') {
                messageComplete = true;
            }
        }
    }

    /* Treatment of received message */
    msg = CharToMessage(rxBuffer);

    /* Call Post method for read */
    Read_Post();

    return msg;
}

/**
        Takes an array of 7 bytes and tries to format it to a message structure

        @params unsigned char * mesg : an array of 6 bytes.
                the byte 0 should be an ascii char that is the label. It define what the data represent
                the bytes 1 to 4 are the float value
                the byte 5 should always be a '\n'
        @params message_serial * m : a pointer of a message. If there was an issue when reading the serial port
                the message takes 'e' (for error) as its label

        @returns 0 if there was an issue while reading the message else 1
 */

Message* ComStm32::CharToMessage(unsigned char *bytes) {

    Message *msg = __null;
    MessageFloat *msgf;
    MessageBool *msgb;

    switch (bytes[0]) {
        case LABEL_ANGLE_POSITION:
            msgf = new MessageFloat();
            msgf->SetID(MESSAGE_ANGLE_POSITION);
            msgf->SetValue(CharToFloat(&bytes[1]));
            msg = (Message*) msgf;

            break;
        case LABEL_ANGULAR_SPEED:
            msgf = new MessageFloat();
            msgf->SetID(MESSAGE_ANGULAR_SPEED);
            msgf->SetValue(CharToFloat(&bytes[1]));
            msg = (Message*) msgf;

            break;
        case LABEL_BATTERY_LEVEL:
            msgf = new MessageFloat();
            msgf->SetID(MESSAGE_BATTERY);
            msgf->SetValue(CharToFloat(&bytes[1]));
            msg = (Message*) msgf;

            break;
        case LABEL_BETA_ANGLE:
            msgf = new MessageFloat();
            msgf->SetID(MESSAGE_BETA);
            msgf->SetValue(CharToFloat(&bytes[1]));
            msg = (Message*) msgf;

            break;
        case LABEL_USER_PRESENCE:
            msgb = new MessageBool();
            msgb->SetID(MESSAGE_USER_PRESENCE);
            msgb->SetState(CharToBool(&bytes[1]));
            msg = (Message*) msgb;

            break;
        default:
            printf("Unknown message received from STM32 (%i)\n", bytes[0]);
            fflush(stdout);
            msg = new Message();
    }

    if (msg == NULL) {
        printf("Message is null (%02X)\n", bytes[0]);
        fflush(stdout);
        msg = new Message();
    }

    return msg;
}

/**
        Converts an array of 4 bytes into a float

        @params unsigned char * bytes : array of 4 bytes

        @return the float value
 */

float ComStm32::CharToFloat(unsigned char *bytes) {
    unsigned long value;
    union {
        unsigned char buffer[4];
        float f;
    } convert;

    convert.buffer[0]=bytes[0];
    convert.buffer[1]=bytes[1];
    convert.buffer[2]=bytes[2];
    convert.buffer[3]=bytes[3];
    
    //value = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | (bytes[0]);

    return convert.f;
}

/**
        Converts an array of 4 bytes into a float

        @params unsigned char * bytes : array of 4 bytes

        @return the float value
 */

unsigned int ComStm32::CharToInt(unsigned char *bytes) {
    unsigned long value;

    value = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | (bytes[0]);

    return (unsigned int)value;
}

/**
        Converts an array of 4 bytes into a float

        @params unsigned char * bytes : array of 4 bytes

        @return the float value
 */

bool ComStm32::CharToBool(unsigned char *bytes) {
    unsigned long value;

    value = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | (bytes[0]);

    if (value == 0) return false;

    else return true;
}

int ComStm32::Write(Message* msg) {
    unsigned char buffer[7];
    int ret_val = 0;

    MessageToChar(msg, buffer);

    Write_Pre();

//    printf ("Message to send: %s\n", msg->ToString().c_str());
//    printf ("Message converted: ");
//    for (int i=0; i<7; i++)
//    {
//        printf ("%02X ", buffer[i]);
//    }
//    printf ("\n");
//    fflush(stdout);
    
    if (this->fd != -1) {
        int count = write(this->fd, &buffer[0], 7); //Filestream, bytes to write, number of bytes to write
        if (count < 0) {
            printf("Warning: UART TX error in ComStm32::Write\n");
        } else {
            ret_val = 1;
        }
    }

    // deallocation of msg
    delete(msg);
    
    Write_Post();

    return ret_val;
}

void ComStm32::MessageToChar(Message *msg, unsigned char *buffer) {
    float val_f;
    int val_i;
    unsigned char *b;

    buffer[0] = '<';
    buffer[6] = '\n';
    
    switch (msg->GetID()) {
        case MESSAGE_TORQUE:
            buffer[1] = LABEL_TORQUE;
            val_f = ((MessageFloat*) msg)->GetValue();
            b = (unsigned char *) &val_f;

            break;
        case MESSAGE_EMERGENCY_STOP:
            buffer[1] = LABEL_EMERGENCY_STOP;
            if (((MessageBool*) msg)->GetState())
                val_i = 1;
            else
                val_i = 0;
            b = (unsigned char *) &val_i;

            break;
        default:
            printf("Invalid message to send");
            val_i = 0;
            b = (unsigned char *) &val_i;
    }

    buffer[2] = b[0];
    buffer[3] = b[1];
    buffer[4] = b[2];
    buffer[5] = b[3];
}

