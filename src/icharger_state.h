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
