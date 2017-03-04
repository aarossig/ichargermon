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

#include <cstdint>

//! The vendor ID of the iCharger product line.
constexpr uint16_t kVendorId(0x0483);

//! The product ID of the iCharger 4010 Duo.
constexpr uint16_t k4010DuoProductId(0x5751);

namespace ichargermon {

ModBusICharger::ModBusICharger() {
  device_ = hid_open(kVendorId, k4010DuoProductId, nullptr /* serial_number */);
}

bool ModBusICharger::IsInitialized() const {
  return (device_ != nullptr);
}

}  // namespace ichargermon
