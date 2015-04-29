#include <iostream>
#include <cstring>
#include <sstream>
#include "xml_log.h"

void XML_log::log_to_file(std::string timestamp,
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
                          int sail_position) {

    std::stringstream ss;
    pugi::xml_document doc;

    /* Tag Message */
    pugi::xml_node node = doc.append_child("message");

    /* Tag source */
    pugi::xml_node node_source = node.append_child("source");
    node_source.set_value("id");
    node_source.append_attribute("id") = "RPI";

    /* Tag systemclock */
    pugi::xml_node node_systemclock = node.append_child("systemclock");
    
    /* Tag timestamp */
    pugi::xml_node descr = node_systemclock.append_child("timestamp");
    descr.append_child(pugi::node_pcdata).set_value(timestamp.c_str());

    /* Tag windsensor */
    pugi::xml_node node_windsensor = node.append_child("windsensor");

    /* Tag app_winddir_deg */
    pugi::xml_node app_winddir = node_windsensor.append_child("app_winddir_deg");

    ss.str(std::string()); //Clear stringstream
    ss << windsensor_dir_deg;
    app_winddir.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag app_winddir_deg */
    pugi::xml_node app_windspeed = node_windsensor.append_child("app_windspeed_ms");
    ss.str(std::string()); //Clear stringstream
    ss << windsensor_speed_ms;
    app_windspeed.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag compass */
    pugi::xml_node node_compass = node.append_child("compass");

    /* Tag heading_deg */
    pugi::xml_node heading_deg = node_compass.append_child("heading_deg");
    ss.str(std::string()); //Clear stringstream
    ss << compass_heading_deg;
    heading_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag pitch_deg */
    pugi::xml_node pitch_deg = node_compass.append_child("pitch_deg");
    ss.str(std::string()); //Clear stringstream
    ss << compass_pitch_deg;
    pitch_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag roll_deg */
    pugi::xml_node roll_deg = node_compass.append_child("roll_deg");
    ss.str(std::string()); //Clear stringstream
    ss << compass_roll_deg;
    roll_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag gps */
    pugi::xml_node node_gps = node.append_child("gps");

    /* Tag gml:Point  */
    pugi::xml_node gmlPoint = node_gps.append_child("gml:Point");
    gmlPoint.set_value("xmlns:gml");
    gmlPoint.append_attribute("xmlns:gml") = "http://www.ogcnetwork.net/GML";

    /* Tag gml:pos  */
    pugi::xml_node gmlPos = gmlPoint.append_child("gml:pos");
    gmlPos.set_value("srsDimension");
    gmlPos.append_attribute("srsDimension") = "2";
    
    ss.str(std::string()); //Clear stringstream
    ss << gps_pos_arg1;
    gmlPos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    ss.str(std::string()); //Clear stringstream
    ss << gps_pos_arg2;
    gmlPos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag cog_deg */
    pugi::xml_node cog_deg = node_gps.append_child("cog_deg");    
    ss.str(std::string()); //Clear stringstream
    ss << gps_cog_deg;
    cog_deg.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag sog_ms */
    pugi::xml_node sog_ms = node_gps.append_child("sog_ms");
    ss.str(std::string()); //Clear stringstream
    ss << gps_sog_ms;
    sog_ms.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag actuator */
    pugi::xml_node node_actuator = node.append_child("actuator");
   
    /* Tag rudder_pos */
    pugi::xml_node rudder_pos = node_actuator.append_child("rudder_pos");
    ss.str(std::string()); //Clear stringstream
    ss << rudder_position;
    rudder_pos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    /* Tag sail_pos */
    pugi::xml_node sail_pos = node_actuator.append_child("sail_pos");
    ss.str(std::string()); //Clear stringstream
    ss << sail_position;
    sail_pos.append_child(pugi::node_pcdata).set_value(ss.str().c_str());

    // save document to file
    doc.save_file("log_output.xml");
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

double XML_log::decimals_to_tenths(double variableToRoundUp){
  
  double tenths_scale = 0.1;  // Round up decimals to the nearest tenths
  double value;

  value = (int)(variableToRoundUp / tenths_scale) * tenths_scale;

  return value;
}

int main() {
  XML_log xml_log;

  xml_log.decimals_to_tenths((double)-123.2623232332);
  xml_log.decimals_to_tenths((double) 300.2623232332);
  xml_log.decimals_to_tenths((double) 0.2623232332);


  xml_log.log_to_file("2015-04-10T10:53:15.1234Z", //Timestamp
                      (double)270.2, //winddir degrees
                      (double)4.3, //windspeed ms
                      (double)11.3, //Heading deg
                      (double)3.2, //Pitch deg
                      (double)5.3, //Roll deg
                      (double)49.40, // gml:pos arg1
                      (double)-123.26, // gml:pos arg2
                      (double)15.4, // cog_deg
                      (double)2.0, //sog_ms
                      (int)5341,//Rudderpos
                      (int)3256 //Sailpos
                      );
  
  xml_log.parse_output_file("log_output.xml");

}