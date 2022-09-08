#include "command_robotarm.hpp"


std::string RobotArmCommand::getCommandMessage(const int command_index)
{
    std::string move_cmd;
    switch (command_index)
    {
        // active robot arm program.
        case 1: 
            move_cmd = "$1,active,0,0,move$";
            break;
        // robot arm run "alignment"
        case 2: 
            move_cmd = "$2,align,0,0,move$";
            break;
        // robot arm run "no1 drill above"
        case 11:
            move_cmd = "$11,1,drillabove,0,move$";
            break;
        // robot arm run "no1 drill workplace"
        case 12:
            move_cmd = "$12,1,drillworkplace,0,move$";
            break;
        // robot arm run "no1 drill safe"
        case 13:
            move_cmd = "$13,1,drillsafe,0,move$";
            break;
        // robot arm run "no2 drill above"
        case 21:
            move_cmd = "$21,2,drillabove,0,move$";
            break;
        // robot arm run "no2 drill workplace"
        case 22:
            move_cmd = "$22,2,drillworkplace,0,move$";
            break;
        // robot arm run "no2 drill safe"
        case 23:
            move_cmd = "$23,2,drillsafe,0,move$";
            break;
        // robot arm run "no3 drill above"
        case 31:
            move_cmd = "$31,3,drillabove,0,move$";
            break;
        // robot arm run "no3 drill workplace"
        case 32:
            move_cmd = "$32,3,drillworkplace,0,move$";
            break;
        // robot arm run "no3 drill safe"
        case 33:
            move_cmd = "$33,3,drillsafe,0,move$";
            break;
        // robot arm run "no4 drill above"
        case 41:
            move_cmd = "$41,4,drillabove,0,move$";
            break;
        // robot arm run "no4 drill workplace"
        case 42:
            move_cmd = "$42,4,drillworkplace,0,move$";
            break;
        // robot arm run "no4 drill safe"
        case 43:
            move_cmd = "$43,4,drillsafe,0,move$";
            break;
        // robot arm run "no5 drill above"
        case 51:
            move_cmd = "$51,5,drillabove,0,move$";
            break;
        // robot arm run "no5 drill workplace"
        case 52:
            move_cmd = "$52,5,drillworkplace,0,move$";
            break;
        // robot arm run "no5 drill safe"
        case 53:
            move_cmd = "$53,5,drillsafe,0,move$";
            break;
        // robot arm run "no6 drill above"
        case 61:
            move_cmd = "$61,6,drillabove,0,move$";
            break;
        // robot arm run "no6 drill workplace"
        case 62:
            move_cmd = "$62,6,drillworkplace,0,move$";
            break;
        // robot arm run "no6 drill safe"
        case 63:
            move_cmd = "$63,6,drillsafe,0,move$";
            break;
        // robot arm run "go home"
        case 99:
            move_cmd = "$99,safe,0,0,move$";
            break;
        // robot arm run "pcb above (get target)"
        case 100:
            move_cmd = "$100,pcbabove,0,0,move$";
            break;
        // robot arm run "pcb x position (get target)"
        case 101:
            move_cmd = "$101,pcbworkplace,0,x,move$";
            break;
        // robot arm run "pcb safe (get target)"
        case 102:
            move_cmd = "$102,pcbsafe,0,0,move$";
            break;
        // robot arm run "pcb above (place target)"
        case 103:
            move_cmd = "$103,pcbabove,0,0,move$";
            break;
        // robot arm run "pcb x position (place target)"
        case 104:
            move_cmd = "$104,pcbworkplace,0,x,move$";
            break;
        // robot arm run "pcb safe (place target)"
        case 105:
            move_cmd = "$105,pcbsafe,0,0,move$";
            break;

        default:
            move_cmd = "";
            break;
    }
    
    return move_cmd;
}