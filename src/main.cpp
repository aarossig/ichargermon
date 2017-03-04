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
