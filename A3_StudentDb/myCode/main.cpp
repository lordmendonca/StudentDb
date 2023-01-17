/* Standard (system) header files */
#include <iostream>
#include <cstdlib>

/* Project header files */
#include "StudentDb.h"
#include "SimpleUI.h"

/* Main program */
int main ()
{
	StudentDb sDB;
	SimpleUI sUI(sDB);
	sUI.run();

	return 0;
}
