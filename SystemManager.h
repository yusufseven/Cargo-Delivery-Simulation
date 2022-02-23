#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "Station.h"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>



class SystemManager
{
public:
	void runSystem(std::string destination, std::string packages, std::string trucks, std::string missions, std::string output);

private:
	struct SplitByDelimiter     // required for reading commands properly
	{
        template <typename Out>
        inline void split(const std::string& s, char delimiter, Out result) {
            std::istringstream x_iStringStream(s);
            std::string item;
            while (std::getline(x_iStringStream, item, delimiter)) {
                *result++ = item;
            }
        }

        inline std::vector<std::string> split(const std::string& strRef, char delimiter) {
            std::vector<std::string> splitByDelim;
            split(strRef, delimiter, std::back_inserter(splitByDelim));
            return splitByDelim;
        }
	};
};

