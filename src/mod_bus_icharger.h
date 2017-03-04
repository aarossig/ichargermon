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

#ifndef ICHARGERMON_MODBUS_ICHARGER_H_
#define ICHARGERMON_MODBUS_ICHARGER_H_

#include <hidapi.h>

namespace ichargermon {

class ModBusICharger {
 public:
  /**
   * Constructs a ModBusICharger by opening the first (or only) ModBus-based
   * ICharger device. This library currently only supports interfacing with one
   * device at a time (and defaults to the first available).
   *
   * The return value of IsInitialized() must be checked prior to invoking any
   * of the methods that read or write the state of the device.
   */
  ModBusICharger();

  /**
   * Determines whether or not the device has been initialized. This method must
   * be invoked before any other API provided by this class. If this method
   * returns false, no ModBus-based ICharger was found.
   *
   * @return Returns true if the ModBusICharger was opened correctly.
   */
  bool IsInitialized() const;

 private:
  //! The underlying HID device.
  hid_device *device_;
};

}  // namespace ichargermon

#endif  // ICHARGERMON_MODBUS_ICHARGER_H_
