#include "BitField.h"
#include <string>
#include <sstream>
#include <math.h>
#include <vector>

template <T>
void myInput(T& obj);
void menuPrint();

int main() {
	bool flags[2];
	BitField bf_arr[2]{ BitField(2), BitField(2) };
	menuPrint();
}

void menuPrint() {
	std::cout << "-------------INTERFACE-------------";
	std::cout << "Options: 1. Input a bitfield.\n";
	std::cout << "\t 2. Change a bit.\n";
	std::cout << "\t 3. Check state of a bit.\n";
	std::cout << "\t 4. Test | operator.\n";
	std::cout << "\t 5. Test & operator.\n";
	std::cout << "\t 6. Print a bitfield.\n";
	std::cout << "\t 7. Print menu\n";
	std::cout << "\t 8. Exit.\n";
	std::cout << "Choose an option: ";
}