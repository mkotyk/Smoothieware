
/**
 * @file    BufferedSoftSerial.h
 * @brief   Software Buffer - Extends mbed Serial functionallity adding irq driven TX and RX
 * @author  sam grove
 * @version 1.0
 * @see     
 *
 * Copyright (c) 2013
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BUFFEREDSOFTSERIAL_H
#define BUFFEREDSOFTSERIAL_H

#include "mbed.h"
#include "libs/RingBuffer.h"
#include "SerialParams.h"
#include <functional>

class SerialPinConfig;

/**
 *  @class BufferedSerial
 *  @brief Software buffers and interrupt driven tx and rx for SoftSerial
 */
class BufferedSoftSerial {
private:
    SerialPinConfig *serialPinConfig;
    RingBuffer<char, 32> _rxbuf;
    RingBuffer<char, 32> _txbuf;

    void prime();

    void byteIn(unsigned char c);

    std::function<void(const unsigned char)> _emit;
public:
    /** Create a BufferedSoftSerial port, connected to the specified transmit and receive pins
     *  @param tx Transmit pin
     *  @param rx Receive pin
     *  @note Either tx or rx may be specified as NC if unused
     */
    BufferedSoftSerial(PinName tx, PinName rx, const char *name = NULL);

    /** Check on how many bytes are in the rx buffer
     *  @return 1 if something exists, 0 otherwise
     */
    int readable(void);

    /** Check to see if the tx buffer has room
     *  @return 1 always has room and can overwrite previous content if too small / slow
     */
    int writeable(void);

    /** Get a single byte from the BufferedSoftSerial Port.
     *  Should check readable() before calling this.
     *  @return A byte that came in on the BufferedSoftSerial Port
     */
    int getc(void);

    /** Write a single byte to the BufferedSoftSerial Port.
     *  @param c The byte to write to the BufferedSoftSerial Port
     *  @return The byte that was written to the BufferedSoftSerial Port Buffer
     */
    int putc(int c);

    /** Write a string to the BufferedSoftSerial Port. Must be NULL terminated
     *  @param s The string to write to the Serial Port
     *  @return The number of bytes written to the Serial Port Buffer
     */
    int puts(const char *s);

    /** Write a formatted string to the BufferedSoftSerial Port.
     *  @param format The string + format specifiers to write to the BufferedSoftSerial Port
     *  @return The number of bytes written to the Serial Port Buffer
     */
    int printf(const char *format, ...);

    /** Write data to the BufferedSoftSerial Port
     *  @param s A pointer to data to send
     *  @param length The amount of data being pointed to
     *  @return The number of bytes written to the Serial Port Buffer
     */
    ssize_t write(const void *s, size_t length);

    void attach(std::function<void(const unsigned char)> &&emit) { _emit = emit; }

    void baud(int baudrate);

    void format(int bits, SerialParams::Parity parity, int stop_bits);
};

#endif
