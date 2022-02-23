#pragma once
#include <string>
#include "DoublyLinkedList.h"

class Truck
{
public:
	DoublyLinkedList<std::string> packages;
	std::string truckName;	
};
