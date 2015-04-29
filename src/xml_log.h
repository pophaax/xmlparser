#include <iostream>
#include <cstring>
#include <sstream>
#include "../pugi/pugixml.hpp"

class XML_log {

public:

  void log_to_file(std::string timestamp,
                          double windsensor_dir_deg,
                          double windsensor_speed_ms,
                          double compass_heading_deg,
                          double compass_pitch_deg,
                          double compass_roll_deg,
                          double gps_pos_arg1,
                          double gps_pos_arg2,
                          double gps_cog_deg,
                          double gps_sog_ms,
                          int rudder_position,
                          int sail_position);

  void parse_output_file(const char* filename);

  double decimals_to_tenths(double variableToRoundUp);

};
