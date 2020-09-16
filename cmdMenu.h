#pragma once
#include <iostream>
#include <string>
#include <vector>
struct entry {
	std::string text = "";
	std::string action = "";
};
class cmdMenu
{
private:
	int current_entry = 0;
	int total_entries = 0;
	std::vector<std::string> actions;
	std::vector<entry> entries;

public:
	void printMenu();
	void addEntry(std::string text, std::string action);
};

