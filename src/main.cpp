#include "icharger.h"

using namespace ichargermon;

/**
 * The default device file to open when communicating with an iCharger.
 */
constexpr char kDefaultDevTty[] = "/dev/ttyUSB0";

int main(int argc, char **argv) {
  // If an argument is supplied, use that as the file path to open.
  const char *uart_file_path = kDefaultDevTty;
  if (argc == 2) {
    uart_file_path = argv[1];
  }

  ICharger icharger(uart_file_path);
  if (!icharger.IsInitialized()) {
    fprintf(stderr, "iCharger not initialized. Quitting.\n");
    return -1;
  }

  while (1) {
    IChargerState charger_state = icharger.ReadState();
    fprintf(stderr, "%s\n", charger_state.ToPrettyString().c_str());
  }

  return 0;
}
