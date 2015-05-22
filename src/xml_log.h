
#ifndef __XML_LOG_H__
#define __XML_LOG_H__
#include <iostream>
#include <cstring>
#include <sstream>
#include "../pugi/pugixml.hpp"

class XML_log {

public:

  std::string log_xml(std::string timestamp,
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

  int parse_saiCMD(std::string xml_source);
  int parse_rudCMD(std::string xml_source);
  std::string parse_time(std::string xml_source);

};

#endif