#pragma once
#include <string>
#include "Queue.h"
#include "Stack.h"
#include "Truck.h"

class Station
{
public:
	Stack<std::string> packages;
	Queue<Truck> trucks;

	std::string cityName{};
};

