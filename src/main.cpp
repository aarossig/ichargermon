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

#include "mod_bus_icharger.h"
#include "serial_icharger.h"

#include <tclap/CmdLine.h>

using namespace ichargermon;

/**
 * The default device file to open when communicating with an iCharger.
 */
constexpr char kDefaultDevTty[] = "/dev/ttyUSB0";

//! A description of this tool.
constexpr char kToolDescription[] =
    "a tool for interacting with PowerUSB USB-controlled power strips";

//! A string constant for serial-port based devices.
const char kSerialPortDevice[] = "serial";

//! A string constant for USB based devices.
const char kModBusPortDevice[] = "mod_bus";

//! The current version of this tool. Defined according to the rules of
//! semantic versioning.
constexpr char kVersionString[] = "0.1.0";

int main(int argc, char **argv) {
  using TCLAP::CmdLine;
  using TCLAP::SwitchArg;
  using TCLAP::ValueArg;
  using TCLAP::ValuesConstraint;

  // The command line object with tool description and version.
  CmdLine cmd(kToolDescription, ' ', kVersionString);

  // The allowable device types.
  std::vector<std::string> allowed_device_types;
  allowed_device_types.push_back(kSerialPortDevice);
  allowed_device_types.push_back(kModBusPortDevice);
  ValuesConstraint<std::string> device_types_constraint(allowed_device_types);

  // The device type argument.
  ValueArg<std::string> device_type_arg("", "device_type",
      "The type of the device.", true, "string", &device_types_constraint, cmd);

  // The device path argument.
  ValueArg<std::string> serial_device_path_arg("", "device_path",
      "The serial device path.", false, kDefaultDevTty, "string", cmd);

  // Parse the provided command line arguments.
  cmd.parse(argc, argv);

  if (device_type_arg.getValue() == kSerialPortDevice) {
    std::string device_path = serial_device_path_arg.getValue();
  
    SerialICharger icharger(device_path.c_str());
    if (!icharger.IsInitialized()) {
      fprintf(stderr, "Serial iCharger not initialized. Quitting\n");
      return -1;
    }
  
    while (1) {
      SerialIChargerState charger_state = icharger.ReadState();
      fprintf(stderr, "%s\n", charger_state.ToPrettyString().c_str());
    }
  } else if (device_type_arg.getValue() == kModBusPortDevice) {
    ModBusICharger icharger;
    if (!icharger.IsInitialized()) {
      fprintf(stderr, "ModBus iCharger not initialized. Quitting\n");
      return -1;
    }

    fprintf(stderr, "ModBus initialized");
  } else {
    fprintf(stderr, "Invalid device type\n");
    return -1;
  }

  return 0;
}
