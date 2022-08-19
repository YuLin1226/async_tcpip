#include "session_robot_arm.hpp"

SessionRobotArm::SessionRobotArm(std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr, std::shared_ptr<boost::asio::deadline_timer> timer_ptr)
{
    std::cout << ">>> Session <ROBOTARM> created." << std::endl;
}

SessionRobotArm::~SessionRobotArm()
{
    std::cout << ">>> Session <ROBOTARM> destroyed." << std::endl;
}

std::string SessionRobotArm::getMoveCommand(const int move_id)
{
    std::string move_cmd;    
    switch (move_id)
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

std::string SessionRobotArm::getMoveFeedbackDefinition(const int move_id)
{
    std::string move_cmd;    
    switch (move_id)
    {
        // active robot arm program.
        case 1: 
            move_cmd = "$1,active,0,0,done$";
            break;
        // robot arm run "alignment"
        case 2: 
            move_cmd = "$2,align,0,0,done$";
            break;
        // robot arm run "no1 drill above"
        case 11:
            move_cmd = "$11,1,drillabove,0,done$";
            break;
        // robot arm run "no1 drill workplace"
        case 12:
            move_cmd = "$12,1,drillworkplace,0,done$";
            break;
        // robot arm run "no1 drill safe"
        case 13:
            move_cmd = "$13,1,drillsafe,0,done$";
            break;
        // robot arm run "no2 drill above"
        case 21:
            move_cmd = "$21,2,drillabove,0,done$";
            break;
        // robot arm run "no2 drill workplace"
        case 22:
            move_cmd = "$22,2,drillworkplace,0,done$";
            break;
        // robot arm run "no2 drill safe"
        case 23:
            move_cmd = "$23,2,drillsafe,0,done$";
            break;
        // robot arm run "no3 drill above"
        case 31:
            move_cmd = "$31,3,drillabove,0,done$";
            break;
        // robot arm run "no3 drill workplace"
        case 32:
            move_cmd = "$32,3,drillworkplace,0,done$";
            break;
        // robot arm run "no3 drill safe"
        case 33:
            move_cmd = "$33,3,drillsafe,0,done$";
            break;
        // robot arm run "no4 drill above"
        case 41:
            move_cmd = "$41,4,drillabove,0,done$";
            break;
        // robot arm run "no4 drill workplace"
        case 42:
            move_cmd = "$42,4,drillworkplace,0,done$";
            break;
        // robot arm run "no4 drill safe"
        case 43:
            move_cmd = "$43,4,drillsafe,0,done$";
            break;
        // robot arm run "no5 drill above"
        case 51:
            move_cmd = "$51,5,drillabove,0,done$";
            break;
        // robot arm run "no5 drill workplace"
        case 52:
            move_cmd = "$52,5,drillworkplace,0,done$";
            break;
        // robot arm run "no5 drill safe"
        case 53:
            move_cmd = "$53,5,drillsafe,0,done$";
            break;
        // robot arm run "no6 drill above"
        case 61:
            move_cmd = "$61,6,drillabove,0,done$";
            break;
        // robot arm run "no6 drill workplace"
        case 62:
            move_cmd = "$62,6,drillworkplace,0,done$";
            break;
        // robot arm run "no6 drill safe"
        case 63:
            move_cmd = "$63,6,drillsafe,0,done$";
            break;
        // robot arm run "go home"
        case 99:
            move_cmd = "$99,safe,0,0,done$";
            break;
        // robot arm run "pcb above (get target)"
        case 100:
            move_cmd = "$100,pcbabove,0,0,done$";
            break;
        // robot arm run "pcb x position (get target)"
        case 101:
            move_cmd = "$101,pcbworkplace,0,x,done$";
            break;
        // robot arm run "pcb safe (get target)"
        case 102:
            move_cmd = "$102,pcbsafe,0,0,done$";
            break;
        // robot arm run "pcb above (place target)"
        case 103:
            move_cmd = "$103,pcbabove,0,0,done$";
            break;
        // robot arm run "pcb x position (place target)"
        case 104:
            move_cmd = "$104,pcbworkplace,0,x,done$";
            break;
        // robot arm run "pcb safe (place target)"
        case 105:
            move_cmd = "$105,pcbsafe,0,0,done$";
            break;

        default:
            move_cmd = "";
            break;
    }

    return move_cmd;
}

void SessionRobotArm::writeMessage(const int move_id)
{
    // TODO: command if as arg.
    // if the command id does not exist, throw error.

    auto move_cmd = getMoveCommand(move_id)    ;

    if(move_cmd == "")
    {
        std::cout << "[Output] Error: Wrong command id.\n";
        return;
    }

    std::cout << "[Output] Send command: " << move_id << "\n";
    boost::asio::async_write(
        *socket_ptr_,
        boost::asio::buffer(move_cmd + "\r\n"),
        [&](boost::system::error_code error, std::size_t bytes_transferred)
        {
        });

}

void SessionRobotArm::readMessage(const int move_id)
{     
    int data_size = getMoveCommand(move_id).length();
    auto self(shared_from_this());
    bool data_available = false;
    received_data_ = std::vector<char>(data_size);
    bool end_this_function = false;
    try
    {
        boost::asio::async_read( 
            *socket_ptr_, 
            boost::asio::buffer(received_data_, data_size),
            [&](const boost::system::error_code &error, std::size_t bytes_transferred)
            {
                if (error)
                {
                    data_available = false;
                    std::cerr << "[Output] readCallback Error " << error << std::endl;
                }
                std::cout << "[Output] Reading finished and cancel timer.\n";
                timer_ptr_->cancel();
                data_available = true;
                end_this_function = true;
            });
        
        timer_ptr_->expires_from_now(boost::posix_time::seconds(MOVE_WAIT_TIME));
        // // Use sync wait to block following actions.
        // timer_ptr_->wait();
        // if(!data_available)
        // {
        //     socket_ptr_->cancel();
        //     std::cerr << "[Output] Read timeout." << std::endl;
        // }
        timer_ptr_->async_wait(  
            [&](const boost::system::error_code &error)
            {
                if (!error)
                {
                    socket_ptr_->cancel();
                    std::cerr << "[Output] Read timeout." << std::endl;
                }
                else
                {
                    std::cerr << "[Output] Timer destroyed." << std::endl;
                }
                end_this_function = true;
            });
        
        while(!end_this_function)
        {
            // silly blocking, needs a smart way.
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "[Output] Read exception. " << e.what() << '\n';
    }

}

Session::ActionStatus SessionRobotArm::checkActionStatus(const int move_id)
{
    auto move_def = getMoveFeedbackDefinition(move_id);
    /*
        if buffer == move_def, return ActionStatus::SUCCESS

        if buffer != move_def, return ActionStatus::FAILURE

        if timer expire, return ActionStatus::UNKNOWN
    */
    for(auto i=0; i<received_data_.size(); i++)
    {
        if(received_data_[i] != move_def[i])
            return Session::ActionStatus::FAILURE;
    }

    return Session::ActionStatus::SUCCESS;

}