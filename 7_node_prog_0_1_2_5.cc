// Header Files

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("7_node_prog_0_1_2_5");

int main (int argc, char *argv[])
{
	Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

	NodeContainer nodes;
	nodes.Create (7);

	InternetStackHelper stack;
	stack.Install (nodes);

	PointToPointHelper p2p1;
	p2p1.SetDeviceAttribute ("DataRate", StringValue("5Mbps"));
	p2p1.SetChannelAttribute ("Delay", StringValue("1ms"));

	PointToPointHelper p2p2;
	p2p2.SetDeviceAttribute ("DataRate", StringValue("5Mbps"));
	p2p2.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p3;
	p2p3.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p3.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p4;
	p2p4.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p4.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p5;
	p2p5.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p5.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p6;
	p2p6.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p6.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p7;
	p2p7.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p7.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p8;
	p2p8.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p8.SetChannelAttribute("Delay", StringValue("1ms"));

    PointToPointHelper p2p9;
	p2p9.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p9.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p10;
	p2p10.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p10.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p11;
	p2p11.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p11.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p12;
	p2p12.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p12.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p13;
	p2p13.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p13.SetChannelAttribute("Delay", StringValue("1ms"));

	PointToPointHelper p2p14;
	p2p14.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
	p2p14.SetChannelAttribute("Delay", StringValue("1ms"));
	
	Ipv4AddressHelper address;
	NetDeviceContainer devices;
	//Ipv4InterfaceContainer interface;

	devices = p2p1.Install (nodes.Get(0), nodes.Get(1));
	address.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer interface = address.Assign (devices);

	devices = p2p2.Install (nodes.Get(1), nodes.Get(2));
	address.SetBase ("10.1.2.0", "255.255.255.0");
	interface = address.Assign (devices);

	devices = p2p3.Install (nodes.Get(2), nodes.Get(3));
	//address.SetBase ("10.1.3.0", "255.255.255.0");
	//interface = address.Assign (devices);

	devices = p2p4.Install (nodes.Get(3), nodes.Get(4));
	//address.SetBase ("10.1.4.0", "255.255.255.0");
	//interface = address.Assign (devices);	

	
	devices = p2p6.Install (nodes.Get(5), nodes.Get(6));
	//address.SetBase ("10.1.6.0", "255.255.255.0");
	//interface = address.Assign (devices);

	devices = p2p7.Install (nodes.Get(0), nodes.Get(6));
	//address.SetBase ("10.1.1.0", "255.255.255.0");
	//Ipv4InterfaceContainer interface = address.Assign (devices);

	
    devices = p2p13.Install (nodes.Get(6), nodes.Get(2));
	//address.SetBase ("10.1.2.0", "255.255.255.0");
	//interface = address.Assign (devices);
	

	devices = p2p8.Install (nodes.Get(0), nodes.Get(3));
	//address.SetBase ("10.1.1.0", "255.255.255.0");
	//interface = address.Assign (devices);

	devices = p2p9.Install (nodes.Get(0), nodes.Get(4));
	//address.SetBase ("10.1.1.0", "255.255.255.0");
	//Ipv4InterfaceContainer interface = address.Assign (devices);

	devices = p2p5.Install (nodes.Get(4), nodes.Get(5));
	//address.SetBase ("10.1.2.0", "255.255.255.0");
	//interface = address.Assign (devices);

	devices = p2p10.Install (nodes.Get(1), nodes.Get(4));
	//address.SetBase ("10.1.1.0", "255.255.255.0");
	//interface = address.Assign (devices);

	devices = p2p11.Install (nodes.Get(1), nodes.Get(5));
	//address.SetBase ("10.1.1.0", "255.255.255.0");
	//interface = address.Assign (devices);

    devices = p2p12.Install (nodes.Get(2), nodes.Get(5));
	address.SetBase ("10.1.3.0", "255.255.255.0");
	interface = address.Assign (devices);

	devices = p2p14.Install (nodes.Get(3), nodes.Get(6));
	//address.SetBase ("10.1.1.0", "255.255.255.0");
	//interface = address.Assign (devices);

	Ipv4GlobalRoutingHelper::PopulateRoutingTables();

	UdpEchoServerHelper echoServer(9);

	ApplicationContainer serverApps = echoServer.Install (nodes.Get(5));
	serverApps.Start (Seconds (1.0));
	serverApps.Stop (Seconds (20.0));

	UdpEchoClientHelper echoClient (interface.GetAddress (1), 9);
	echoClient.SetAttribute ("MaxPackets", UintegerValue(1));
	echoClient.SetAttribute ("Interval", TimeValue (Seconds(1.0)));
	echoClient.SetAttribute ("PacketSize", UintegerValue(1024));

	ApplicationContainer clientApps = echoClient.Install (nodes.Get(0));
	clientApps.Start (Seconds(2.0));
	clientApps.Stop (Seconds(20.0));

	AnimationInterface anim ("7_node_prog_0_1_2_5.xml");
	anim.SetConstantPosition (nodes.Get(0), 1.5, 0.0 );
	anim.UpdateNodeSize (0, 0.10, 0.10);
	anim.SetConstantPosition (nodes.Get(1), 3.0, 1.0 );
	anim.UpdateNodeSize (1, 0.10, 0.10);
	anim.SetConstantPosition (nodes.Get(2), 3.0, 2.5 );
	anim.UpdateNodeSize (2, 0.10, 0.10);
	anim.SetConstantPosition (nodes.Get(3), 2.0, 3.0 );
	anim.UpdateNodeSize (3, 0.10, 0.10);
	anim.SetConstantPosition (nodes.Get(4), 1.0, 3.0 );
	anim.UpdateNodeSize (4, 0.10, 0.10);
	anim.SetConstantPosition (nodes.Get(5), 0.0, 2.5 );
	anim.UpdateNodeSize (5, 0.10, 0.10);
	anim.SetConstantPosition (nodes.Get(6), 0.0, 1.0 );
	anim.UpdateNodeSize (6, 0.10, 0.10);
	
	  //
// Tracing
// 
 /* AsciiTraceHelper ascii;
  p2p1.EnableAscii(ascii.CreateFileStream ("7_node_prog.tr"), devices);
  p2p1.EnablePcap("7_node_prog", devices, false);
*/
//
// Calculate Throughput using Flowmonitor
//
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();


//
// Now, do the actual simulation.
//
  NS_LOG_INFO ("Run Simulation.");
 Simulator::Stop (Seconds(11.0));
  Simulator::Run ();

  monitor->CheckForLostPackets ();

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
      if ((t.sourceAddress=="10.1.1.1" && t.destinationAddress == "10.1.3.2"))
      {
          std::cout << "Flow " << i->first  << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")\n";
          std::cout << "  Tx Bytes:   " << i->second.txBytes << "\n";
          std::cout << "  Rx Bytes:   " << i->second.rxBytes << "\n";
          std::cout << "  Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds())/1024/1024  << " Mbps\n";
      }
  
}     
   
 // std::cout << "  Tx Bytes:   " << txBytes << "\n";
 //std::cout << "  Rx Bytes:   " << interfaces->second.rxBytes << "\n"; 
  //std::cout << "Throughput: " << "47" << " Mbit/s" << '\n';

  monitor->SerializeToXmlFile("7_node_prog_0_1_2_5.flowmon", true, true);
  
  Simulator::Destroy ();   
  return 0;


}