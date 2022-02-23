#include "SystemManager.h"

void SystemManager::runSystem(std::string destination, std::string packages, std::string trucks, std::string missions, std::string output) // reads files, carries out operations, prepares output
{																																		   // in correct order, creates output file and writes in.
	std::ifstream fileDestinations(destination); // reading destinations file	argv[1] 
	std::ifstream filePackages(packages);		 // reading packages file		argv[2]	
	std::ifstream fileTrucks(trucks);			 // reading trucks file			argv[3] 
	std::ifstream fileMissions(missions);		 // reading missions file		argv[4]	
	
	std::map<std::string, Station> stations;

	for (std::string line; std::getline(fileDestinations, line);)
	{
		Station temp;
		temp.cityName = line;
		stations[line] = temp;
	}

	SplitByDelimiter SBD;
	for (std::string line; std::getline(fileTrucks, line);)
	{
		auto splitByWhitespace = SBD.split(line, ' ');
		Truck temp;
		temp.truckName = splitByWhitespace[0];
		stations[splitByWhitespace[1]].trucks.enqueue(temp);
	}

	for (std::string line; std::getline(filePackages, line);)
	{
		auto splitted = SBD.split(line, ' ');
		stations[splitted[1]].packages.push(splitted[0]);
	}

	for (std::string line; std::getline(fileMissions, line);)
	{
		auto splitted = SBD.split(line, '-');
		Station& startCity = stations[splitted[0]];
		Station& middleCity = stations[splitted[1]];
		Station& endCity = stations[splitted[2]];

		int firstPackageCountTaken = std::stoi(splitted[3]);
		int middlePackgeCountTaken = std::stoi(splitted[4]);

		Truck truck;
		startCity.trucks.getFront(truck);
		startCity.trucks.dequeue();

		auto splitIndices = SBD.split(splitted[5], ',');
		for (int i = 0; i < firstPackageCountTaken; i++)
		{
			std::string temp;
			startCity.packages.getTop(temp);
			startCity.packages.pop();

			truck.packages.addItem(temp);
		}

		for (int i = 0; i < middlePackgeCountTaken; i++)
		{
			std::string temp;
			middleCity.packages.getTop(temp);
			middleCity.packages.pop();

			truck.packages.addItem(temp);
		}
		std::vector<int> splitIndicesInt;

		for (std::string& indice : splitIndices)
		{
			int index = std::stoi(indice);
			splitIndicesInt.push_back(index);
		}

		for (int indice : splitIndicesInt)
		{
			middleCity.packages.push(truck.packages.getItemAtIndex(indice));
		}

		std::sort(splitIndicesInt.rbegin(), splitIndicesInt.rend());

		for (int indice : splitIndicesInt)
		{
			truck.packages.removeItemAtIndex(indice);
		}
		int temp = truck.packages.size;
		for (int i = 0; i < temp; i++)
		{
			endCity.packages.push(truck.packages.getItemAtIndex(0));
			truck.packages.removeItemAtIndex(0);
		}
		endCity.trucks.enqueue(truck);
	}

	std::ofstream writeOutput(output);			// output		 argv[5]  
	fileDestinations.close();

	std::ifstream fileOutput(destination);	    // destinations	 argv[1] putting city output in correct order 
	for (std::string line; std::getline(fileOutput, line);)

	{
		std::string cityName = line;
		Station& station = stations[cityName];
		writeOutput << cityName << std::endl;
		writeOutput << "Packages:" << std::endl;
		while (!station.packages.isEmpty())
		{
			std::string temp{};
			station.packages.getTop(temp);
			station.packages.pop();
			writeOutput << temp << std::endl;
		}
		writeOutput << "Trucks:" << std::endl;
		while (!station.trucks.isEmpty())
		{
			Truck temp{};
			station.trucks.getFront(temp);
			station.trucks.dequeue();
			writeOutput << temp.truckName << std::endl;
		}
		writeOutput << "-------------" << std::endl;
	}
}

