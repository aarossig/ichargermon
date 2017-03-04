/*
 * Copyright 2017 Andrew Rossignol andrew.rossignol@gmail.com
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

#include "serial_icharger.h"

#include <cstdio>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

namespace ichargermon {

SerialICharger::SerialICharger(const char *device_path) {
  fd_ = open(device_path, O_RDONLY | O_NOCTTY | O_NONBLOCK);
  if (fd_ < 0) {
    fprintf(stderr, "Error opening device %s with error %s\n",
        device_path, strerror(errno));
    return;
  }

  // Configure the UART.
  struct termios options;
  options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
  options.c_iflag = IGNPAR;
  tcflush(fd_, TCIFLUSH);
  tcsetattr(fd_, TCSANOW, &options);
}

bool SerialICharger::IsInitialized() const {
  return fd_ >= 0;
}

/**
 * iCharger packets are delimited by CRLF. Simply ready one byte at a time from
 * the file descriptor until a CRLF is detected.
 */
std::string ReadChargerPacket(int fd) {
  std::string packet_buffer;

  while (1) {
    char character;
    if (read(fd, &character, 1) > 0) {
      packet_buffer.push_back(character);
    }

    if (packet_buffer.size() >= 2
        && packet_buffer[packet_buffer.size() - 2] == '\r'
        && packet_buffer[packet_buffer.size() - 1] == '\n') {
      break;
    }
  }

  return packet_buffer;
}

SerialIChargerState SerialICharger::ReadState() const {
  while (1) {
    std::string packet = ReadChargerPacket(fd_);
    SerialIChargerState charger_state;
    if (charger_state.ParsePacket(packet)) {
      return charger_state;
    }
  }
}

}  // namespace ichargermon
