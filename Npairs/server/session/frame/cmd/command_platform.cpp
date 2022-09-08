#include "command_platform.hpp"

std::string PlatformCommand::getCommandMessage()
{
    std::string cmd;
    
    std::string car_state, send_mission_number, send_mission_state, reply_mission_number, reply_mission_state, car_pos, recipe, tray_number;

    car_state = '0';
    send_mission_number = '0';
    send_mission_state = '0';
    reply_mission_number = '0';
    reply_mission_state = '0';
    car_pos = '0';


    // start code
    cmd += "@";
    cmd += "0}" + car_state + ",";
    cmd += "1}" + send_mission_number + ",";
    cmd += "2}" + send_mission_state + ",";
    cmd += "3}" + reply_mission_number + ",";
    cmd += "4}" + reply_mission_state + ",";
    cmd += "5}" + car_pos + ",";
    cmd += "6}" + recipe + ",";
    cmd += "7}" + tray_number;
    cmd += "#";
    
    return cmd;
}
