#include "icharger_state.h"

#include <sstream>
#include <vector>

namespace ichargermon {

/**
 * The length of an iCharger packet.
 */
constexpr size_t kPacketFieldCount = 20;

IChargerState::IChargerState()
    : input_voltage_(0.0f),
      battery_voltage_(0.0f),
      battery_amps_(0.0f),
      internal_temperature_(0.0f) {}

/**
 * Splits a string into substrings given a delimeter.
 *
 * @param The string to split
 * @param The delimeter to split on
 * @return The vector of substrings
 */
std::vector<std::string> SplitString(const std::string& str, char delimeter) {
  std::vector<std::string> elements;

  std::stringstream str_stream(str);
  std::string element;
  while (std::getline(str_stream, element, delimeter)) {
    elements.push_back(element);
  }

  return elements;
}

/**
 * Parses a float safely. Returns false if the string could not be parsed into
 * a float.
 *
 * @param The string to parse
 * @param A pointer to a float to populate if parsing is successful
 * @return True if parsing was successful.
 */
bool ParseFloat(const std::string& str, float *f) {
  char *end_ptr;
  *f = strtof(str.c_str(), &end_ptr);
  return str.c_str() != end_ptr;
}

bool IChargerState::ParsePacket(std::string packet) {
  std::vector<std::string> fields = SplitString(packet, ';');
  if (fields.size() != kPacketFieldCount) {
    fprintf(stderr, "Received malformed packet. "
        "Expected %zu fields, received %zu\n", kPacketFieldCount, fields.size());
    return false;
  }

  // Parse the fields.
  if (!ParseFloat(fields[3], &input_voltage_)) {
    fprintf(stderr, "Error parsing input voltage\n");
    return false;
  }

  if (!ParseFloat(fields[4], &battery_voltage_)) {
    fprintf(stderr, "Error parsing battery voltage\n");
    return false;
  }

  if (!ParseFloat(fields[5], &battery_amps_)) {
    fprintf(stderr, "Error parsing battery amps\n");
    return false;
  }

  for (size_t i = 0; i < cell_voltages_.size(); i++) {
    if (!ParseFloat(fields[i + 6], &cell_voltages_[i])) {
      fprintf(stderr, "Error parsing cell %zu voltage\n", i);
      return false;
    }

    // Normalize units to volts.
    cell_voltages_[i] /= 1000.0f;
  }

  if (!ParseFloat(fields[16], &internal_temperature_)) {
    fprintf(stderr, "Error parsing internal temperature\n");
    return false;
  }

  // Normalize units.
  input_voltage_ /= 1000.0f;
  battery_voltage_ /= 1000.0f;
  battery_amps_ /= 100.0f;
  internal_temperature_ /= 10.0f;
  return true;
}

std::string IChargerState::ToPrettyString() const {
  std::string pretty_string;

  const char kFormatString[] =
      "Input voltage:    %04.3fV\n"
      "Battery voltage:  %04.3fV\n"
      "Battery amps:     %04.3fA\n"
      "Internal temp:    %04.3fC\n";

  const char kCellVoltageFormatString[] =
      "Cell %zu voltage:   %04.3fV\n";

  char buffer[512];
  snprintf(buffer, sizeof(buffer), kFormatString,
      input_voltage_,
      battery_voltage_,
      battery_amps_,
      internal_temperature_);
  pretty_string.append(buffer);

  for (size_t i = 0; i < cell_voltages_.size(); i++) {
    snprintf(buffer, sizeof(buffer), kCellVoltageFormatString, i, cell_voltages_[i]);
    pretty_string.append(buffer);
  }

  return pretty_string;
}

}  // namespace ichargermon
