#include "pch.h"
#include "Genome.h"
#include "TestBase\XOROutputNeuron.h"
#include "TestBase\XOROutputNeuronFactory.h"
#include "TestBase\GenomeTestBase.h"
#include "FileUtility.h"
#include <string>



TEST(GenomeTest, LodeGenomeTest) {
	std::string path = "Networks\\XORBasic.nn";
	std::istream* stream = GenomeTestBase::SetUp(path);

	XORActivationReturn* value = new XORActivationReturn();
	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
	Genome genome = Genome(*stream, xorFactory);

	EXPECT_TRUE(true, "File did not load corretly");

	GenomeTestBase::TearDown();
	delete xorFactory;
	delete value;
}


TEST(GenomeTest, ActivateGenomeXORSimple) {
	std::string path = "Networks\\XORBasic.nn";
	std::istream* stream = GenomeTestBase::SetUp(path);

	XORActivationReturn* value = new XORActivationReturn();
	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
	Genome genome = Genome(*stream, xorFactory);	
	std::map<std::string, double> inputs = { {"XOR1", 0}, {"XOR2", 1} };

	genome.execute(inputs);

	int expected = 1;
	int actual = value->getValue();
	EXPECT_EQ(expected, actual);

	GenomeTestBase::TearDown();
	delete xorFactory;
	delete value;
}


TEST(GenomeTest, ActivateGenomeXORComplete) {
	std::string path = "Networks\\XORComplete.nn";
	std::istream* stream = GenomeTestBase::SetUp(path);

	XORActivationReturn* value = new XORActivationReturn();
	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
	Genome genome = Genome(*stream, xorFactory);
	std::map<std::string, double> inputs = { {"XOR1", 1}, {"XOR2", 1} };

	genome.execute(inputs);

	int expected = 0;
	int actual = value->getValue();
	EXPECT_EQ(expected, actual);

	GenomeTestBase::TearDown();
	delete xorFactory;
	delete value;
}


TEST(GenomeTest, ActivateGenomeXORSimpleWithReset) {
	std::string path = "Networks\\XORBasic.nn";
	std::istream* stream = GenomeTestBase::SetUp(path);

	XORActivationReturn* value = new XORActivationReturn();
	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
	Genome genome = Genome(*stream, xorFactory);
	std::map<std::string, double> inputs = { {"XOR1", 0}, {"XOR2", 1} };

	genome.execute(inputs);
	int expected = 1;
	int actual = value->getValue();
	EXPECT_EQ(expected, actual);


	genome.resetNeurons();
	std::map<std::string, double> secondInput = { {"XOR1", 1}, {"XOR2", 0} };

	genome.execute(secondInput);
	expected = 1;
	actual = value->getValue();
	EXPECT_EQ(expected, actual);

	GenomeTestBase::TearDown();
	delete xorFactory;
	delete value;
}