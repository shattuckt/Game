#include "pch.h"
//#include "Synapse.h"
//#include "SynapseSortHelper.h"
//#include <map>
//
//
//TEST(SynapseTest, HashMapOrderTest) {
//	std::multimap<Synapse*, int, SynapseCompare> synapseMap;
//	Neuron* n1 = new Neuron(0, 0);
//	Neuron* n2 = new Neuron(0, 1);
//	Synapse* s1 = new Synapse(n1, n2, 1);
//	Synapse* s2 = new Synapse(n2, n1, 1);
//
//	synapseMap.insert(std::make_pair(s1, 1));
//	synapseMap.insert(std::make_pair(s2, 2));
//
//	int s1n = synapseMap.find(s1)->second;
//	int s2n = synapseMap.find(s2)->second;
//
//	EXPECT_NE(s1n, s2n);
//
//	delete(n1);
//	delete(n2);
//	delete(s1);
//	delete(s2);
//}
//
//TEST(SynapseTest, HashMapMatchTest) {
//	std::multimap<Synapse*, int, SynapseCompare> synapseMap;
//	Neuron* n1 = new Neuron(0, 0);
//	Neuron* n2 = new Neuron(0, 1);
//	Synapse* s1 = new Synapse(n1, n2, 1);
//	Synapse* s2 = new Synapse(n1, n2, 1);
//
//	synapseMap.insert(std::make_pair(s1, 1));
//	synapseMap.insert(std::make_pair(s2, 2));
//
//	int s1n = synapseMap.find(s1)->second;
//	int s2n = synapseMap.find(s2)->second;
//
//	EXPECT_EQ(s1n, s2n);
//
//	delete(n1);
//	delete(n2);
//	delete(s1);
//	delete(s2);
//}
//
//TEST(SynapseTest, HashMapNonMatchTest) {
//	std::multimap<Synapse*, int, SynapseCompare> synapseMap;
//	Neuron* n1 = new Neuron(0, 0);
//	Neuron* n2 = new Neuron(0, 1);
//	Neuron* n3 = new Neuron(0, 2);
//	Synapse* s1 = new Synapse(n1, n2, 1);
//	Synapse* s2 = new Synapse(n1, n3, 1);
//
//	synapseMap.insert(std::make_pair(s1, 1));
//	synapseMap.insert(std::make_pair(s2, 2));
//
//	int s1n = synapseMap.find(s1)->second;
//	int s2n = synapseMap.find(s2)->second;
//
//	EXPECT_NE(s1n, s2n);
//
//	delete(n1);
//	delete(n2);
//	delete(n3);
//	delete(s1);
//	delete(s2);
//}
