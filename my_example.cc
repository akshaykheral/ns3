#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (4);

  InternetStackHelper stack;
  stack.Install (nodes);

  PointToPointHelper p2p1;
  p2p1.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p1.SetChannelAttribute ("Delay", StringValue ("1ms"));


  PointToPointHelper p2p2;
  p2p2.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p2.SetChannelAttribute ("Delay", StringValue ("5ms"));
  
  PointToPointHelper p2p3;
  p2p3.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p3.SetChannelAttribute ("Delay", StringValue ("5ms"));
  
  Ipv4AddressHelper address;
  NetDeviceContainer devices;
  devices = p2p1.Install (nodes.Get (0), nodes.Get(1));  
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer Interfaces = address.Assign (devices);

  devices = p2p2.Install (nodes.Get (1), nodes.Get(2));
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Interfaces = address.Assign (devices);

  devices = p2p3.Install (nodes.Get (2), nodes.Get(3));
  address.SetBase ("10.1.3.0", "255.255.255.0");
  Interfaces = address.Assign (devices);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (3));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (Interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  AnimationInterface anim ("my_example.xml");
  anim.SetConstantPosition(nodes.Get(0), 1.0, 2.0);
  anim.SetConstantPosition(nodes.Get(1), 2.0, 3.0);
  anim.SetConstantPosition(nodes.Get(2), 3.0, 4.0);
  anim.SetConstantPosition(nodes.Get(3), 4.0, 5.0);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
