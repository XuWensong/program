#include "abstract_factory.hpp"

void FactoryLowLevel::create_product_low_level()
{
	ProductLowLevelA* low_level_a = new ProductLowLevelA();
	ProductLowLevelB* low_level_b = new ProductLowLevelB();

	delete low_level_a;
	low_level_a = NULL;
	delete low_level_b;
	low_level_b = NULL;
}

void FactoryMiddleLevel::create_product_middle_level()
{
	ProductMilddleLevelA* middle_level_a = new ProductMilddleLevelA();
	ProductMiddleLevelB* middle_level_b = new ProductMiddleLevelB();

	delete middle_level_a;
	middle_level_a = NULL;
	delete middle_level_b;
	middle_level_b = NULL;
}

void FactoryHighLevel::create_product_high_level()
{
	ProductHighLevelA* high_level_a = new ProductHighLevelA();
	ProductHighLevelB* high_level_b = new ProductHighLevelB();

	delete high_level_a;
	high_level_a = NULL;
	delete high_level_b;
	high_level_b = NULL;
}

