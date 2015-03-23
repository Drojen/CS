// CS318 - Warehouse
// Jason Jendro

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

std::ifstream inFile;
std::ofstream outFile;

struct itemRec {
	int				id,
					qty;
	std::string		warehouse,
					name;
	float			wholesale,
					markup, // % markup stored in format XX
					retail;
};

// comparisons for sorting
bool compByWarehouse(const itemRec &a, const itemRec &b) { return a.warehouse < b.warehouse; }
bool compById(const itemRec &a, const itemRec &b) { return a.id < b.id; }

int getIndexByName(std::vector<itemRec> &v, std::string key) {
	int notFound = -1;
	for (std::vector<itemRec>::size_type i = 0; i < v.size(); i++) {
		if (v[i].name == key) {
			return i;
		}
	}
	return notFound;
}

int getIndexById(std::vector<itemRec> &v, int key) {
	int notFound = -1;
	for (std::vector<itemRec>::size_type i = 0; i < v.size(); i++) {
		if (v[i].id == key) {
			return i;
		}
	}
	return notFound;
}

void getData(std::vector<itemRec> &inventory, int dataSource) { 
	// variables used in cases
	std::string name, warehouse, id, qty, wholesale, markup, line;

	switch (dataSource) {
	case 1: // id -> name ... loads ids and names, this one will run first and push back all the intial structs since id and name will be our keys
		inFile.open("WLL1.dat");

		while (inFile >> id >> name) {
			itemRec temp;
			temp.id = std::stoi(id, nullptr, 10);
			temp.name = name;
			temp.qty = 0;
			temp.markup = 0.0;
			temp.retail = 0.0;
			temp.wholesale = 0.0;
			temp.warehouse = "none";
			inventory.push_back(temp);
		}

		inFile.close();
		break;

	case 2: // id -> warehouse ... use id to add warehouses
		inFile.open("WLL2.dat");

		while (inFile.good()) {
			std::getline(inFile, line);

			if (line.length() > 0) { // check empty lines being pulled in

				// do work on line to get variables....
				id = line.substr(0, 4);
				warehouse = line.substr(5);

				int x = std::stoi(id, nullptr, 10); // convert id str to int for function pass
				int i = getIndexById(inventory, x);
				if (i > -1) { inventory[i].warehouse = warehouse; }

			}
		}

		inFile.close();
		break;

	case 3: // name -> qty ... use name to add qtys
		inFile.open("WLL3.dat");

		while (inFile >> name >> qty) {
			int i = getIndexByName(inventory, name);
			if (i > -1) { inventory[i].qty = std::stoi(qty, nullptr, 10); }
		}

		inFile.close();
		break;

	case 4: // name-id -> wholesale -> markup ... use id or name to add wholesale and markup
		inFile.open("WLL4.dat");

		while (inFile.good()) {
			std::getline(inFile, line);

			if (line.length() > 0) { // check empty lines being pulled in

				// substring variables for positioning the pointer
				size_t	startPos = 0,
						len = 0,
						endPos = 0;

				// get id from string
				endPos = line.find_first_of(" ");
				startPos = endPos - 4;
				len = endPos - startPos;
				id = line.substr(startPos, len);
				int newId = std::stoi(id);

				// get wholesale from string
				startPos = endPos + 1;
				endPos = line.find_last_of(" ");
				len = endPos - startPos;
				wholesale = line.substr(startPos, len);

				// get markup from string
				startPos = endPos + 1;
				endPos = line.find("%");
				len = endPos - startPos;
				markup = line.substr(startPos, len);

				// assign to struct and convert to correct data types
				int i = getIndexById(inventory, newId);
				if (i > -1) {
					inventory[i].wholesale = std::stof(wholesale);
					inventory[i].markup = std::stof(markup);
				}
			}
		}

		inFile.close();
		break;

	default:
		std::cerr << "Invalid data source input in getData...\n";
	}
}

void calcRetail(std::vector<itemRec> &v) {
	// calc retail using markup and wholesale
	for (std::vector<itemRec>::size_type i = 0; i < v.size(); i++) {
		v[i].retail = v[i].wholesale + (v[i].wholesale * (v[i].markup / 100));
	}
}

void printHeader(std::string name) {
	outFile << "                         " << name <<  std::endl;
	outFile << std::left << std::setw(5) << "ID" << std::setw(18) << "Name" << std::setw(6) << "Qty" << std::setw(10) << "Retail" << std::setw(10) << " Wholesale" << std::setw(5) << "  Markup" << std::setw(15) << "   Warehouse" << std::endl;
	outFile << "---- ----------------- ----- ---------  ---------  ------   -----------" << std::endl;
}

void printInventory(std::vector<itemRec> &v) {
	// variables for switching warehouse display and running totals
	std::string comp = v[0].warehouse;
	bool warehouseSwitch = false;
	float totalRetail = 0.0;
	
	// set cout format
	outFile.precision(2);
	outFile << std::fixed << std::left;
	printHeader(v[0].warehouse); // print intial header 

	// loop through vector
	for (std::vector<itemRec>::size_type i = 0; i < v.size(); i++) {
		
		if (comp != v[i].warehouse) {
			comp = v[i].warehouse;
			warehouseSwitch = true;
		}

		if (warehouseSwitch) {
			outFile << "\n" << std::setw(55) << std::right << "Total Retail: $" << totalRetail << std::endl;
			warehouseSwitch = false; // reset switch
			totalRetail = 0.0; // reset total
			outFile << "\n";
			printHeader(v[i].warehouse);
		}
		
		outFile << std::left << std::setw(5) << v[i].id << std::setw(18) << v[i].name << std::setw(6) << v[i].qty << "$" << std::setw(10) << v[i].retail << "$" << std::setw(10) << v[i].wholesale << std::right << std::setw(5) << v[i].markup << "%   " << std::setw(15) << std::left << v[i].warehouse << "\n";
		totalRetail += v[i].retail;	
	}
	outFile << "\n" << std::setw(55) << std::right << "Total Retail: $" << totalRetail << std::endl; // print final total
}

int main() {

	outFile.open("warehouse-output.txt");
	std::vector<itemRec> whInventory;

	// Read in data from all four sources
	getData(whInventory, 1);
	getData(whInventory, 2);
	getData(whInventory, 3);
	getData(whInventory, 4);

	// calculate retail
	calcRetail(whInventory);

	// sort properly
	std::sort(whInventory.begin(), whInventory.end(), compById);
	std::stable_sort(whInventory.begin(), whInventory.end(), compByWarehouse);

	// print results
	printInventory(whInventory);

	std::cout << "Printed results to warehouse-output.txt\n\n";
	outFile.close();

	return 0;
}


