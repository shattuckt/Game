#include "pch.h"
#include "NEAT.h"
#include "Trait.h"
#include <map>


TEST(NEATUtilityTest, GetInnovationSameTrait) {
	Trait* t1 = new Trait(0, 1, 1, 1);
	Trait* t2 = new Trait(0, 1, 1, 1);

	int t1n = NEAT::getInnovationNum(t1);
	int t2n = NEAT::getInnovationNum(t2);


	EXPECT_EQ(t1n, t2n);

	delete(t1);
	delete(t2);
	NEAT::ResetGenerationMap();
}


TEST(NEATUtilityTest, GetInnovationDifferentTrait) {
	Trait* t1 = new Trait(0, 1, 1, 1);
	Trait* t2 = new Trait(0, 2, 1, 1);

	int t1n = NEAT::getInnovationNum(t1);
	int t2n = NEAT::getInnovationNum(t2);


	EXPECT_NE(t1n, t2n);

	delete(t1);
	delete(t2);
	NEAT::ResetGenerationMap();
}
