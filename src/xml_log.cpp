#include <cstring>
#include <sstream>
#include <iostream>     
#include <iomanip>      
#include <ctime>        
#include "xml_log.h"

std::string XML_log::log_xml(std::string timestamp,
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
                          int sail_position) {

    std::stringstream ss;
    pugi::xml_document doc;

    /* Tag Message */
    pugi::xml_node node = doc.append_child("message");

    /* Tag source */
    pugi::xml_node node_source = node.append_child("sor");
    node_source.append_child(pugi::node_pcdata).set_value("RPI");


    /* Tag systemclock */
    pugi::xml_node node_systemclock = node.append_child("tim");
    node_systemclock.append_child(pugi::node_pcdata).set_value(timestamp.c_str());

    /* Tag windsensor */
    pugi::xml_node node_windsensor = node.append_child("ws");

    /* Tag app_winddir_deg */
    pugi::xml_node app_winddir = node_windsensor.append_child("wdi");

    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(windsensor_dir_deg); 
    app_winddir.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag app_winddir_deg */
    pugi::xml_node app_windspeed = node_windsensor.append_child("wsp");
    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(windsensor_speed_ms); 
    app_windspeed.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag compass */
    pugi::xml_node node_compass = node.append_child("com");

    /* Tag heading_deg */
    pugi::xml_node heading_deg = node_compass.append_child("hea");
    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(compass_heading_deg); 
    heading_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag pitch_deg */
    pugi::xml_node pitch_deg = node_compass.append_child("pit");
    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(compass_pitch_deg); 
    pitch_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag roll_deg */
    pugi::xml_node roll_deg = node_compass.append_child("rol");
    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(compass_roll_deg); 
    roll_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag gps */
    pugi::xml_node node_gps = node.append_child("gps");

    /* Tag pos  */
    pugi::xml_node gmlPos = node_gps.append_child("pos");
    
    ss.str(std::string()); //Clear stringstream
    ss << std::setprecision(10) << gps_pos_lat << " " << gps_pos_long;        //precision 2+8=10
    gmlPos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag cog_deg */
    pugi::xml_node cog_deg = node_gps.append_child("cog");    
    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(gps_cog_deg); 
    cog_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag sog_ms */
    pugi::xml_node sog_ms = node_gps.append_child("sog");
    ss.str(std::string()); //Clear stringstream
    ss << decimals_to_tenths(gps_sog_ms); 
    sog_ms.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag actuator */
    pugi::xml_node node_actuator = node.append_child("act");
   
    /* Tag rudder_pos */
    pugi::xml_node rudder_pos = node_actuator.append_child("rud");
    ss.str(std::string()); //Clear stringstream
    ss << rudder_position;
    rudder_pos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag sail_pos */
    pugi::xml_node sail_pos = node_actuator.append_child("sai");
    ss.str(std::string()); //Clear stringstream
    ss << sail_position;
    sail_pos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());



    std::ostringstream out_ss; 
    out_ss.str(std::string());
    doc.save(out_ss, PUGIXML_TEXT("\t"), pugi::format_raw); 
    std::string res_xml = out_ss.str(); 
    return res_xml;

  }

void XML_log::parse_output_file(const char* filename) {
  pugi::xml_document doc;
  doc.load_file(filename);
    
  std::cout << "Parsing file: " << filename << std::endl;

  pugi::xml_node ship = doc.child("message");
  for (pugi::xml_node child = ship.first_child(); child; child = child.next_sibling()) {
    for (pugi::xml_node node = child.first_child(); node; node = node.next_sibling()) {
      std::cout << node.name() << "=" << node.child_value() << std::endl;
        
      /* Only for tags on 4th level */
      if(std::strcmp(node.name(), "gml:Point") == 0) {
        pugi::xml_node node_child = node.first_child();
        std::cout << node_child.name() << "=" << node_child.child_value() << std::endl;
      }
    }
  }
}

int XML_log::parse_rudCMD(std::string xml_source) {
  pugi::xml_document doc;
  doc.load(xml_source.c_str());

  pugi::xml_node ship = doc.child("message");
  for (pugi::xml_node child = ship.first_child(); child; child = child.next_sibling()) {
    for (pugi::xml_node node = child.first_child(); node; node = node.next_sibling()) {
      if(std::strcmp(node.name(), "rudCMD") == 0) {
        int rudCMD = std::stoi(node.child_value());
        return rudCMD;
      }
    }
  }
  return -1;
}


int XML_log::parse_saiCMD(std::string xml_source) {
  pugi::xml_document doc;
  doc.load(xml_source.c_str());

  pugi::xml_node ship = doc.child("message");
  for (pugi::xml_node child = ship.first_child(); child; child = child.next_sibling()) {
    for (pugi::xml_node node = child.first_child(); node; node = node.next_sibling()) {
      if(std::strcmp(node.name(), "saiCMD") == 0) {
        int saiCMD = std::stoi(node.child_value());
        return saiCMD; 
      }
    }
  }
  return -1;
}

std::string XML_log::parse_time(std::string xml_source) {
  pugi::xml_document doc;
  doc.load(xml_source.c_str());

  pugi::xml_node ship = doc.child("message");
  for (pugi::xml_node child = ship.first_child(); child; child = child.next_sibling()) {
      if(std::strcmp(child.name(), "tim") == 0) {
        std::string timestamp = child.child_value();
        return timestamp; 
    }
  }
  return 0;
}

double XML_log::decimals_to_tenths(double variableToRoundUp){
  
  double tenths_scale = 0.1;  // Round up decimals to the nearest tenths
  double value;
  
  value = (int)(variableToRoundUp / tenths_scale) * tenths_scale;

  return value;
}
