#include "SystemManager.h"

int main(int argc, char** argv)
{
	SystemManager systemManager;
	systemManager.runSystem(argv[1], argv[2], argv[3], argv[4], argv[5]);
	return 0;
}
