#include "factory.hpp"
#include <string.h>

AbstractProduct* Factory::create_product(string product)
{
	if (strcmp(product.c_str(), "ProductA") == 0) {
		return new ProductA();
	} else if (strcmp(product.c_str(), "ProductB") == 0) {
		return new ProductB();
	} else {
		return NULL;
	}
}

