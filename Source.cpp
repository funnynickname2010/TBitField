#include "BitField.h"
#include <string>
#include <sstream>
#include <math.h>
#include <vector>

void MenuInput(int& option);
void BitFieldRowInput(BitField& field);
void BitFieldPrint(const BitField& field);

template <typename T>
void BitFieldNotInitialized(const T& which_bitfield);

template <typename T>
void Safecin(T& input_container);

void MenuPrint()
{
	std::cout << "1. Input a bitfitfield as a row\n";
	std::cout << "2. Change a single bit of a bitfield\n";
	std::cout << "3. Check state of a bit\n";
	std::cout << "4. Test | operator\n";
	std::cout << "5. Test & operator\n";
	std::cout << "6. Print the bitfield\n";
	std::cout << "7. Print menu\n";
	std::cout << "8. Exit\n";
}

int main()
{
	int menu_option = 0;
	int exit_option = 8;

	BitField bfield_1(32), bfield_2(32);

	BitField bitfield_array[2] = {bfield_1, bfield_2};
	bool initialization_flags[2] = {0, 0};

	MenuPrint();

	while (menu_option != exit_option)
	{
		MenuInput(menu_option);

		switch (menu_option)
		{
		case 1:
			//Inputting bitfield as a row
		{
			size_t which_bitfield;
			size_t bitfield_size = 0;

			std::cout << "Which bitfield do you want to input? A = 0, B = 1: ";
			Safecin(which_bitfield);

			std::cout << "Please input the size of the bitfield: ";
			Safecin(bitfield_size);

			bitfield_array[which_bitfield].ChangeSize(bitfield_size);
			BitFieldRowInput(bitfield_array[which_bitfield]);

			initialization_flags[which_bitfield] = 1;
		}
		break;

		case 2:
			//Changing a single bit of a bitfield
		{
			size_t which_bitfield;
			unsigned int bit_index;
			bool input_bit = 0;

			std::cout << "Which bitfield do you want to change a bit in? A = 0, B = 1: ";
			Safecin(which_bitfield);

			if (initialization_flags[which_bitfield])
			{

				std::cout << "Please input the index of the bit: ";
				Safecin(bit_index);

				std::cout << "Please input the value of the bit: ";
				Safecin(input_bit);

				if (input_bit == 1) //If we want the value to be 1, then we need to invoke TurnOn(...) function
				{
					bitfield_array[which_bitfield].TurnOn(bit_index);
				}
				else //If input_bit == 0, invoke TurnOff(...)
				{
					bitfield_array[which_bitfield].TurnOff(bit_index);
				}
			}
			else //I really wanted to make it pretty, there's actually no need for that
			{
				BitFieldNotInitialized(which_bitfield);
			}
		}
		break;

		case 3:
			//Check state of a bit
		{
			size_t which_bitfield;
			size_t bit_index;

			std::cout << "Which bitfield do you want to check a bit in? A = 0, B = 1: ";
			Safecin(which_bitfield);

			if (initialization_flags[which_bitfield])
			{
				std::cout << "Please input the index of the bit: ";
				Safecin(bit_index);

				std::cout << bitfield_array[which_bitfield].CheckState(bit_index);
			}
			else
			{
				BitFieldNotInitialized(which_bitfield);
			}
		}
		break;

		case 4:
			//Test | operator
		{
			if (initialization_flags[0] && initialization_flags[1])
			{
				BitField bitfield_temp = (bitfield_array[0] | bitfield_array[1]);
				BitFieldPrint(bitfield_temp);
			}
			else
			{
				if (!initialization_flags[0]) { BitFieldNotInitialized(0); }
				if (!initialization_flags[1]) { BitFieldNotInitialized(1); }
			}
		}
		break;

		case 5:
			//Test & operator
		{
			if (initialization_flags[0] && initialization_flags[1])
			{
				BitField bitfield_temp = (bitfield_array[0] & bitfield_array[1]);
				BitFieldPrint(bitfield_temp);
			}
			else
			{
				if (!initialization_flags[0]) { BitFieldNotInitialized(0); }
				if (!initialization_flags[1]) { BitFieldNotInitialized(1); }
			}
		}

			break;

		case 6:
			//Print the bitfield
		{
			bool which_bitfield;

			std::cout << "Which bitfield do you want to print? A = 0, B = 1: ";
			Safecin(which_bitfield);

			if (initialization_flags[which_bitfield])
			{
				BitFieldPrint(bitfield_array[which_bitfield]);
			}
			else
			{
				BitFieldNotInitialized(which_bitfield);
			}
		}
			break;

		case 7:
			//Print menu
			
			MenuPrint();

			break;

		case 8:
			//Exit
			break;

		default:
			//Incorrect input feedback

			std::cout << "Error: Incorrect input, please try again\n";
			break;

		}
	}

}

void MenuInput(int& option)
{
	std::cout << "Please choose an option: ";
	std::cin >> option;
}

void BitFieldRowInput(BitField& field) //Nedds complete rehaul
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	size_t bit_size = field.GetUsedBitSize();
	std::string input_string = "";
	std::string temp_string = "";
	input_string.resize(bit_size, '0');
	temp_string.resize(bit_size, '0');

	std::cout << "String size: " << input_string.size() << "\t" << input_string << std::endl;

	std::cout << "Please input the bitfield: ";

	std::getline(std::cin, temp_string);

	for (size_t j = 0; j < temp_string.size(); j++)
	{
		input_string[j] = temp_string[j];
	}
	
	for (size_t i = 0; i < bit_size; i++)
	{
		if (input_string[i] == '1')
		{
			field.TurnOn(i);
		}
		else if (input_string[i] == '0')
		{
			field.TurnOff(i);
		}
		else
		{
			break;
		}
	}

	if (std::cin.fail())
	{
		std::cin.ignore();
		std::cin.clear();
	}
}

void BitFieldPrint(const BitField& field)
{
	std::string output_str = "";
	size_t bit_size = field.GetUsedBitSize();

	for (size_t i = 0; i < bit_size; i++)
	{
		if (field.CheckState(i))
		{
			output_str.append("1");
		}
		else
		{
			output_str.append("0");
		}
	}

	std::cout << output_str << std::endl;
}

template<typename T>
void BitFieldNotInitialized(const T& which_bitfield)
{
	std::cout << "Error: bitfield ";
	if (which_bitfield == 0) { std::cout << "A "; }
	else { std::cout << "B "; }
	std::cout << "is not initialized!\n";
}

template<typename T>
void Safecin(T& input_container)
{
	do
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore('\n');
			std::cout << "Input error! Please try again\n";
		}
		std::cin >> input_container;

	} while (std::cin.fail());
}
