#include <iostream>
#include <math.h>
#include <boost/shared_ptr.hpp>
#include <sdf/sdf.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo.hh>
#include <iostream>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/math/gzmath.hh>
#include "position_stiffness_request.pb.h"
#include "pos_current_echo_request.pb.h"


typedef const boost::shared_ptr<const position_stiffness_creator_msgs::msgs::PositionStiffnessRequest> PositionStiffnessRequestPtr;

typedef const boost::shared_ptr<const pos_current_echo_creator_msgs::msgs::PosCurrentEchoRequest> PosCurrentEchoRequestPtr; 
  

/////////////////////////////////////////////////
// Function is called everytime a message is received.
 
void cb(PosCurrentEchoRequestPtr &msg) 
{
   
   /* Dump the message contents to stdout */
   std::cout << "Output shaft position echo: " << msg->pos_out_shaft() << "\n";
   std::cout << "Motor 1 position echo: " << msg->pos_mot_1() << "\n";
   std::cout << "Motor 2 position echo: " << msg->pos_mot_2() << "\n";
   std::cout << "Motor 1 current echo: " << msg->curr_mot_1() << "\n";
   std::cout << "Motor 2 current echo: " << msg->curr_mot_2() << "\n"; 

}

/////////////////////////////////////////////////
int main(int argc, char ** argv)
{
      /* Load gazebo */
      gazebo::setupClient(argc, argv);

      /* Create our node for communication */
      gazebo::transport::NodePtr node(new gazebo::transport::Node());

      node->Init(); 

      int num = atoi(argv[1]);  

      double position = atoi(argv[2]);

      double stiffness = atoi(argv[3]);

      gazebo::transport::PublisherPtr publisher;

      gazebo::transport::SubscriberPtr subscriber;

      /*************************************************************************/

      /* string used to initialize publisher topics */
      std::string publisher_string = ""; 

      /* string used to initialize subscriber topics */
      std::string subscriber_string = "";
     
      publisher_string = "qbmove_" + boost::lexical_cast<std::string>(num) + "/position_stiffness/command"; 

      subscriber_string = "qbmove_" + boost::lexical_cast<std::string>(num) + "/pos_current/echo";

      std::cout << publisher_string << "\n";

      std::cout << subscriber_string << "\n";

      publisher = node->Advertise<position_stiffness_creator_msgs::msgs::PositionStiffnessRequest>(publisher_string);

      subscriber = node->Subscribe(subscriber_string, cb);

      position_stiffness_creator_msgs::msgs::PositionStiffnessRequest msg_pub; 

      msg_pub.set_stiffness(stiffness);

      msg_pub.set_position(position);

      /**************************************************************************/
           
      while (true)
      {                                      
           publisher->Publish(msg_pub);     
           gazebo::common::Time::MSleep(10);
      }
    
      return 0; 
 
}