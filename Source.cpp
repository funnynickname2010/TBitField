#include "BitField.h"
#include <string>
#include <sstream>

void CorrectInput(int left_index, int right_index);
void Interface();
void InputRow(BitField& obj);
void OutputRow(BitField& obj);
unsigned int bit_field_len = 30;

int main()
{

	int option;
	unsigned int ind, val;
	BitField field1(bit_field_len);
	BitField field2(bit_field_len);
	BitField field_result(bit_field_len);
	Interface();

	do
	{
		std::cout << "\nChoose an option: ";
		std::cin >> option;

		switch (option)
		{
		case 1:

			InputRow(field1);
			break;

		case 2:

			do
			{
				std::cout << "Input index: ";
				std::cin >> ind;
			} while (ind > (field1.reserved_ints * 32) || ind < 0);

			do
			{
				std::cout << "Input value: ";
				std::cin >> val;
			} while (val != 0 && val != 1);

			if (val == 0)
			{
				field1.TurnOff(ind);
			}
			else if (val == 1)
			{
				field1.TurnOn(ind);
			}

			if (field1.used_bits <= ind)
			{
				field1.used_bits = ind + 1;
			}

			break;

		case 3:

			do
			{
				std::cout << "Input index: ";
				std::cin >> ind;
			} while (ind > (field1.reserved_ints * 32) || ind < 0);

			std::cout << "Bit with an index " << ind << " equals to " << field1.CheckState(ind) << std::endl;

			break;

		case 4:

			std::cout << "\nInput second bitfield: ";
			InputRow(field2);

			field_result = (field1 | field2);

			OutputRow(field_result);
			break;

		case 5:

			std::cout << "\nInput second bitfield: ";
			InputRow(field2);

			field_result = (field1 & field2);

			OutputRow(field_result);
			break;

		case 6:

			OutputRow(field1);

		case 7:

			std::cout << "\n";
			Interface();
		}

	} while (option != 8 || option < 1 || option > 8);
}

void Interface()
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

void InputRow(BitField& obj)
{
	char* input;
	input = new char[bit_field_len * 32];
	std::cin.clear();
	std::cin >> input;

	for (int i = 0; i < (bit_field_len * 32); i++)
	{
		if (input[i] == '1')
		{
			obj.TurnOn(i);
			obj.used_bits += 1;
		}
		else if (input[i] == '0')
		{
			obj.TurnOff(i);
			obj.used_bits += 1;
		}
		else
		{
			break;
		}
	}
}

void OutputRow(BitField& obj)
{
	int* output = new int[obj.reserved_ints + 1];
	for (int i = 0; i <= obj.reserved_ints; i++)
	{
		output[i] = 0;
	}

	for (unsigned int i = 0; i <= obj.reserved_ints; i++)
	{
		output[i] = (obj.CheckState(i));
	}

	std::cout << "\n";
	
	for (int i = 0; i <= obj.reserved_ints; i++)
	{
		std::cout << output[i];
	}

	std::cout << "\n";

	delete[] output;
}
