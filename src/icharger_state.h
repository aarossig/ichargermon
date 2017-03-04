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

#ifndef ICHARGERMON_ICHARGER_STATE_H_
#define ICHARGERMON_ICHARGER_STATE_H_

#include <array>
#include <string>

namespace ichargermon {

/**
 * Stores the state associated with an iCharger.
 */
class IChargerState {
 public:
  /**
   * Initializes the state to zero.
   */
  IChargerState();

  /**
   * Parses a packet from a string.
   *
   * @param The packet to parse.
   * @return True if parsing is successful.
   */
  bool ParsePacket(std::string packet);

  /**
   * Formats the internal state into a pretty string, suitable for output in
   * logs or on a console.
   */
  std::string ToPrettyString() const;

 private:
  //! The input voltage currently seen by the charger.
  float input_voltage_;

  //! The voltage across the battery under charge.
  float battery_voltage_;

  //! The current currently flowing through the battery.
  float battery_amps_;

  //! The internal temperature of the charger.
  float internal_temperature_;

  //! The voltage of each cell in the pack under charge.
  std::array<float, 10> cell_voltages_;
};



}  // namespace ichargermon

#endif  // ICHARGERMON_ICHARGER_STATE_H_
