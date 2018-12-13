#include "stdafx.h"
#include "Tilemap.h"
#include <fstream>
#include <iostream>
#include <string>

Tilemap::Tilemap(int _numColumns, int _numRows, int ** _data)
{
	// Dimensions of the map
	numColumns = _numColumns;
	numRows = _numRows;

	// The map data (a 2D array)
	data = _data;
		
}

Tilemap::~Tilemap()
{
	// Deleting the 2D array of tiles
	// delete in the opposite order of creation
	for (int r = 0; r < numColumns; ++r)
	{
		delete[] data[r]; // delete each allocated row with array delete
		data[r] = nullptr; // safely set to nullptr
	}
	// Use array delete, since array new was used in allocation
	delete[] data;
	data = nullptr; // safely set to nullptr.
}

unsigned Tilemap::GetWidth() const
{
	return numColumns;
}

unsigned Tilemap::GetHeight() const
{
	return numRows;
}

int Tilemap::GetCellValue(int column, int row) const
{
	//if given row or column is outside of the array then just return -1
	if ((column >= numColumns || column < 0) || (row >= numRows || row < 0)) {
		return -1;
	}
	//other wise return the correct value
	return data[column][row];
}

void Tilemap::SetCellValue(int column, int row, int newValue) const {
	//if given row or column is outside of the array then just return
	if ((column >= numColumns || column < 0) || (row >= numRows || row < 0)) {
		return;
	}

	data[column][row] = newValue;

	/*//loop through each value in the 2D array of tiles and print out its value
	for (unsigned r = 0; r < GetHeight(); r++)
	{
		for (unsigned c = 0; c < GetWidth(); c++)
		{
			std::cout << GetCellValue(c, r) << " ";
		}
		std::cout << std::endl;
	}*/
}

Tilemap * Tilemap::CreateTilemapFromFile(const std::string & filename)
{
	std::ifstream infile(filename);
	if (!infile.is_open()) 
	{ 
		std::cout << "Can't open file '" + filename + "'." << std::endl;
		return nullptr;
	}
	
	int rows = -1;
	int columns = -1;

	ReadIntegerVariable(infile, "width", columns);
	ReadIntegerVariable(infile, "height", rows);

	int** data = ReadArrayVariable(infile, "data", columns, rows);

	Tilemap* output = new Tilemap(columns, rows, data);

	infile.close();

	//print out data from tilemap to check if it was read sucessfully
	std::cout << "Height : " << output->GetHeight() << std::endl;
	std::cout << "Width : " << output->GetWidth() << std::endl;
	
	//loop through each value in the 2D array of tiles and print out its value
	for (unsigned r = 0; r < output->GetHeight(); r++)
	{
		for (unsigned c = 0; c < output->GetWidth(); c++)
		{
			std::cout << output->GetCellValue(c, r) << " ";
		}
		std::cout << std::endl;
	}
	
	return output;
}

bool Tilemap::ReadIntegerVariable(std::ifstream & file, const std::string & name, int & variable)
{
	std::string str;
	//read name
	file >> str;
	//if correct name then return true and put stuff in variable
	if (str == name) {
		file >> variable;
		return true;
	}
	//we didn't find it and we are failures!
	return false;
}

int ** Tilemap::ReadArrayVariable(std::ifstream & file, const std::string & name, int columns, int rows)
{

	std::string str;
	//read name
	file >> str;

	if (str != name) {
		return nullptr;
	}

	//make a new 2D int array
	int ** data = new int *[columns];
	for (int r = 0; r < columns; ++r)
	{
		data[r] = new int[rows];
	}

	//loop through each value in the 2D array of tiles and set each one to the correct one here
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			//read the next int
			int value;
			file >> value;
			//set that value in output
			data[c][r] = value;
		}
	}

	return data;
}
