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

#ifndef ICHARGERMON_SERIAL_ICHARGER_H_
#define ICHARGERMON_SERIAL_ICHARGER_H_

#include "serial_icharger_state.h"

namespace ichargermon {

/**
 * Contains the logic associated with interfacing with an iCharger.
 */
class SerialICharger {
 public:
  /**
   * Constructs an ICharger by opening the device. The IsInitialized method
   * must be tested before invoking ReadState.
   */
  SerialICharger(const char *device_path);

  /**
   * Determine whether the ICharger was initialized correctly.
   *
   * @return False if the device was not initialized correctly.
   */
  bool IsInitialized() const;

  /**
   * Reads the state from an iCharger.
   *
   * @return An IChargerState object that is populated with data from an
   * iCharger.
   */
  SerialIChargerState ReadState() const;

 private:
  /**
   * The file descriptor for the device.
   */
  int fd_;
};

}  // namespace ichargermon

#endif  // ICHARGERMON_SERIAL_ICHARGER_H_
