#include "pch.h"
#include "MutableGenome.h"
#include "TestBase\XOROutputNeuronFactory.h"
#include "TestBase\GenomeTestBase.h"


TEST(MutableGenomeTest, MutateAddNeuronTest) {
	std::string path = "Networks\\XORBasic.nn";
	std::istream* stream = GenomeTestBase::SetUp(path);

	XORActivationReturn* value = new XORActivationReturn();
	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
	MutableGenome genome = MutableGenome(*stream, xorFactory);
	genome.MutateAddNeuron();

	std::map<std::string, double> inputs = { {"XOR1", 0}, {"XOR2", 1} };
	genome.execute(inputs);

	int expected = 1;
	int actual = value->getValue();
	EXPECT_EQ(expected, actual);

	NEAT::innovations.clear();
	GenomeTestBase::TearDown();
	delete xorFactory;
	delete value;
}




TEST(MutableGenomeTest, MateTest) {
	std::string path1 = "Networks\\XORIncompleteMother.nn";
	std::istream* stream = GenomeTestBase::SetUp(path1);

	XORActivationReturn* value = new XORActivationReturn();
	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
	MutableGenome mother = MutableGenome(*stream, xorFactory);

	GenomeTestBase::TearDown();
	std::string path2 = "Networks\\XORIncompleteFather.nn";
	stream = GenomeTestBase::SetUp(path2);
	MutableGenome father = MutableGenome(*stream, xorFactory);

	MutableGenome*child = mother.Mate(&father);

	std::map<std::string, double> inputs = { {"XOR1", 1}, {"XOR2", 1} };
	child->execute(inputs);

	int expected = 0;
	int actual = value->getValue();
	EXPECT_EQ(expected, actual);

	GenomeTestBase::TearDown();
	delete xorFactory;
	delete child;
	delete value;
}

////This is a sloppy ass test, but nessessary.
//TEST(MutableGenomeTest, MutateAddSynapseTest) {
//	std::string path = Utility::GetSolutionDir().append("TestNEAT\\Networks\\XORBasic.nn");
//	std::filebuf fb;
//	if (!fb.open(path, std::ios::in)) {
//		std::stringstream ss;
//		ss << "Could not open file " << path << std::endl;
//		throw std::exception(ss.str().c_str());
//	}
//
//	std::istream stream(&fb);
//	std::string header = FileUtility::readChar4(stream);
//	u8 version = FileUtility::readByte(stream);
//	u32 generation = FileUtility::readUnsignedInt(stream);
//
//	XORActivationReturn* value = new XORActivationReturn();
//	XOROutputNeuronFactory* xorFactory = new XOROutputNeuronFactory(value);
//	MutableGenome genome = MutableGenome(stream, xorFactory);
//
//
//	std::map<std::string, double> inputs = { {"XOR1", 0}, {"XOR2", 1} };
//	genome.execute(inputs);
//	int value1 = value->getValue();
//
//	genome.MutateAddSynapse();
//
//	genome.execute(inputs);
//	int value2 = value->getValue();
//
//	EXPECT_EQ(expected, actual);
//
//
//
//	
//
//	NEAT::innovations.clear();
//	delete xorFactory;
//}

