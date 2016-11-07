#ifndef ICHARGERMON_ICHARGER_H_
#define ICHARGERMON_ICHARGER_H_

#include "icharger_state.h"

namespace ichargermon {

/**
 * Contains the logic associated with interfacing with an iCharger.
 */
class ICharger {
 public:
  /**
   * Constructs an ICharger by opening the device. The IsInitialized method
   * must be tested before invoking ReadState.
   */
  ICharger(const char *device_path);

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
  IChargerState ReadState() const;

 private:
  /**
   * The file descriptor for the device.
   */
  int fd_;
};

}  // namespace ichargermon

#endif  // ICHARGERMON_ICHARGER_H_
