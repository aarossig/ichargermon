#include "icharger.h"

#include <cstdio>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

namespace ichargermon {

ICharger::ICharger(const char *device_path) {
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

bool ICharger::IsInitialized() const {
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

IChargerState ICharger::ReadState() const {
  while (1) {
    std::string packet = ReadChargerPacket(fd_);
    IChargerState charger_state;
    if (charger_state.ParsePacket(packet)) {
      return charger_state;
    }
  }
}

}  // namespace ichargermon
