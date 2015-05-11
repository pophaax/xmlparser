
#ifndef __XML_LOG_H__
#define __XML_LOG_H__
#include <iostream>
#include <cstring>
#include <sstream>
#include "../pugi/pugixml.hpp"

class XML_log {

public:

  std::string log_to_file(std::string timestamp,
                          double windsensor_dir_deg,
                          double windsensor_speed_ms,
                          double compass_heading_deg,
                          double compass_pitch_deg,
                          double compass_roll_deg,
                          double gps_pos_lat,
                          double gps_pos_long,
                          double gps_cog_deg,
                          double gps_sog_ms,
                          int rudder_position,
                          int sail_position);

  void parse_output_file(const char* filename);

  double decimals_to_tenths(double variableToRoundUp);

};

#endif