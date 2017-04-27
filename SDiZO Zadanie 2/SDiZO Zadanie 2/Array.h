#pragma once
#include "stdafx.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <random>
#include "DataStructure.h"
#include "DataStructureExceptions.h"


//Vector-like data structure
class Array : public DataStructure
{
public:

	Array();
	Array(const Array &obj);			
	Array(int capacity);

	virtual ~Array();						


	//Adding and manipulating data

	void PushBack(int key);		
	void Set(int position, int key);	
	void Insert(int position, int key);	
	void Swap(int position1, int position2);

	//Deleting data

	void DeletePosition(int position);	
	void DeleteKey(int key);

	//Data access

	int Get(int position) const;
	int FindKey(int key);
	int &operator[](int i)					//Added for increased readability				
	{
		if (i > size_)
		{
			std::cout << "Index out of bounds" << std::endl;
			return data_[0];
		}
		return data_[i];
	}			
	int GetSize() const;
	int GetCapacity()const;

	//Utility

	bool IsInArray(int key);

	void ReadFromFile(std::string filename);
	void GenerateRandom(int size, int min , int max);
	void Display();

protected:

	//Utility

	bool IsEmpty();
	void SetCapacity(int capacity);			//Creates new array, copies the data	

	//Fields

	int *data_;		//pointer to the first element of array
	int capacity_;	//number of elements array can hold
	int size_;		//Current number of elements in array
};