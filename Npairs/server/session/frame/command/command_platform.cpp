#include "command_platform.hpp"

unsigned char* PlatformCommand::getCommandMessage()
{

}

// std::string session::getMoveCMD(std::string vehicle_state, 
//                                  std::string send_mission,
//                                  std::string send_mission_state, 
//                                  std::string reply_mission,
//                                  std::string reply_mission_state,
//                                  std::string vehicle_position_state,
//                                  std::string recipe,
//                                  std::string tray_number)
//     {
//         std::string cmd;
//         cmd += "@";
//         cmd += "0}" + vehicle_state + ",";
//         cmd += "1}" + send_mission + ",";
//         cmd += "2}" + send_mission_state + ",";
//         cmd += "3}" + reply_mission + ",";
//         cmd += "4}" + reply_mission_state + ",";
//         cmd += "5}" + vehicle_position_state + ",";
//         cmd += "6}" + recipe + ",";
//         cmd += "7}" + tray_number;
//         cmd += "#";

//         return cmd;
//     }