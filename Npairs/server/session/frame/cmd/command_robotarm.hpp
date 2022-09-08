#if !defined(_COMMAND_ROBOTARM_HPP_)
#define _COMMAND_ROBOTARM_HPP_

#include <string>

class RobotArmCommand
{
    private:
        
    public:
        static std::string getCommandMessage(const int command_index);
};


#endif // _COMMAND_ROBOTARM_HPP_
