#include "BitField.h"
#include <string>
#include <sstream>

void MenuInput(const int& option) const;
void BitFieldRowInput(BitField& field);
void BitFieldPrint(const BitField& field) const;

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

	BitField* bitfield_array[2];
	bool* initialization_flags[2];

	std::fill_n(initialization_flags, 2, 0);

	MenuPrint();

	while (menu_option != exit_option)
	{
		switch (menu_option)
		{
		case 1:
			//Inputting bitfield as a row
		{
			bool which_bitfield;
			size_t bitfield_size = 0;

			std::cout << "Which bitfield do you want to input? A = 0, B = 1: ";
			Safecin(which_bitfield);

			std::cout << "Please input the size of the bitfield: ";
			Safecin(bitfield_size);

			bitfield_array[which_bitfield]->ChangeSize(bitfield_size);
			BitFieldRowInput(bitfield_array[which_bitfield]);
		}
			break;

		case 2:
			//Changing a single bit of a bitfield
		{
			bool which_bitfield;
			size_t bit_index;
			bool input_bit = 0;

			std::cout << "Which bitfield do you want to change a bit in? A = 0, B = 1: ";
			Safecin(which_bitfield);

			std::cout << "Please input the index of the bit: ";
			Safecin(bit_index);

			std::cout << "Please input the value of the bit: ";
			Safecin(input_bit);

			if (input_bit == 1) //If we want the value to be 1, then we need to invoke TurnOn(...) function
			{
				bitfield_array[which_bitfield]->TurnOn(bit_index);
			}
			else //If input_bit == 0, invoke TurnOff(...)
			{
				bitfield_array[which_bitfield]->TurnOff(bit_index);
			}
		}
			break;

		case 3:
			//Check state of a bit
		{
			bool which_bitfield;
			size_t bit_index;

			std::cout << "Which bitfield do you want to check a bit in? A = 0, B = 1: ";
			Safecin(which_bitfield);

			std::cout << "Please input the index of the bit: ";
			Safecin(bit_index);

			std::cout << bitfield_array[which_bitfield]->CheckState(bit_index);
		}
			break;

		case 4:
			//Test | operator


			break;

		case 5:
			//Test & operator


			break;

		case 6:
			//Print the bitfield


			break;

		case 7:
			//Print menu


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

	delete[] bitfield_array;
	delete[] initalization_flags;
}

void MenuInput(const int& option) const
{
	std::cout << "Please choose an option: ";
	std::cin >> option;
	std::cout << std::endl;
}

void BitFieldRowInput(BitField& field)
{
	bool* input_row = new bool[field.used_bits];
	std::fill_n(input_row, field.used_bits, 0);

	std::cout << "Please input the bitfield as a row: ";

	Safecin(input_row);
	
	for (size_t i = 0; i < field.used_bits; i++) //This part of the function is slow
	{
		if (input_row[i]) //== 1 (just for clarity)
		{
			field.TurnOn(i);
		}
	}

	delete[] input_row;
}

template<typename T>
void Safecin(T& input_container)
{
	do
	{
		std::cin >> input_container;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore('\n');
			std::cout << "Input error! Please try again\n";
		}
	} while (std::cin.fail());
}
