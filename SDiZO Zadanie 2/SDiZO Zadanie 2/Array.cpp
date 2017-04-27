#include "stdafx.h"
#include "Array.h"
#include <string>

//Creates emptry array able to hold 50 integers
Array::Array()
	: capacity_(50)
	, size_(0)
	, data_(new int[50]())		// () - set the elements of new array to 0
{}

//Copy constructor
Array::Array(const Array & obj)
	: size_(obj.size_)
	, capacity_(obj.capacity_)
	, data_(new int[obj.size_])
{
	for (int i = 0; i < size_; i++)
		data_[i] = obj.data_[i];
}

//Creates empty array of given capacity
Array::Array(int capacity)
{
	if (capacity < 0)
	{
		const char *message = "Attempted to create array of negative size";
		throw InvalidStructureSize(message);
	}
	else
	{
		capacity_ = capacity;
		size_ = 0;
		data_ = new int[capacity_]();
	}	
}

//Deletes the array
Array::~Array()
{
	delete[] data_;
}

//Returns the current number of elements in the array
int Array::GetSize() const
{
	return size_;
}

//Returns how many elements can given array store (size of alocated memory)
int Array::GetCapacity() const
{
	return capacity_;
}

//Pushes back key to the end of array
void Array::PushBack(int key)		//Given key
{
	if (size_ >= capacity_)			//If there's no more place
		SetCapacity(2 * capacity_); //Allocates new array and copies data
	data_[size_] = key;				//Place key at the end
	++size_;						//Increment size
}

//Creates new array of given capacity, copies data from the old one
void Array::SetCapacity(int size)
{
	if (size <= capacity_)			
		return;

	int *new_data = new int[size]();	//new array

	for (int i = 0; i < size_; i++)	//copy old data into new array
		new_data[i] = data_[i];

	capacity_ = size;					//set the new capacity
	delete[] data_;						//delete the old array		
	data_ = new_data;
}

//Replaces key at given position with a new key.
//The size of array is not changed in process
void Array::Set(int position, int key)
{
	if (position < 0 || position >= size_)
	{
		const char * message = "Attempted to set key at position outside of range";
		throw OutOfRange(message);
	}			
	else		
		data_[position] = key;
}

//Inserts the key at given position, increases the size of array
//Moves the keys at higher positions 1 up
void Array::Insert(int position, int key)
{
	int old_size = GetSize();
	if (position < 0)
	{
		position = position * -1;
		SetCapacity(old_size + position);
		Insert(0, key);
		for (int i = 0; i < position-1; i++)
			Insert(1, 0);
		return;
	}
	if ( position > size_)
	{	
		SetCapacity(position);
		for (int i = old_size - 1; i < position; i++)
			PushBack(0);
		data_[position] = key;
		return;
	}
	PushBack(0);		//Increase the size of array by 1
	
	//Move all elements from position to end of the array
	//Start from the "right" side of the array

	for (int i = size_ - 1; i > position; --i)
		data_[i] = data_[i - 1];

	//Put key into Array
	data_[position] = key;
}

//Swaps keys at two given position
void Array::Swap(int position1, int position2)
{
	//Error handling provided by set and get methods
	int temp = Get(position1);
	Set(position1, Get(position2));
	Set(position2, temp);
}

//Remove key from the given position, move data down if needed
void Array::DeletePosition(int position)
{
	if (position < 0 || position >= size_)
	{
		const char* message = "Attempted to remove key from position outside of range";
		throw OutOfRange(message);
	}
	else
	{
		for (int i = position; i < size_; i++)	//Move data on position down
			data_[i] = data_[i + 1];
		--size_;
	}
}

//Searches for and deletes key
void Array::DeleteKey(int key)
{
	int position = FindKey(key);
	DeletePosition(position);
}

//Returns key from the given position
int Array::Get(int position) const
{
	if (position < 0 || position >= size_)
	{
		const char* message = "Attempted to retrieve key from position outside of range";
		throw OutOfRange(message);
	}
	else		
		return data_[position];
}

bool Array::IsInArray(int key)
{
	for (int i = 0; i < size_; i++)
	{
		if (data_[i] == key)
		{
			return true;
		}
	}
	return false;
}

//Searches for the key in the array, returns the position
int Array::FindKey(int key)
{
	for (int i = 0; i < size_; i++)
	{
		if (data_[i] == key)
		{
			return i;
		}
	}
}

//Adds the content of a file to the array
//File format: first line size, values separated by newline
void Array::ReadFromFile(std::string filepath)
{
	std::fstream file;
	int key, size;

	file.open(filepath, std::ios_base::in); 

	if (!file)
		throw std::runtime_error("Could not open the file");

	file >> size;
	SetCapacity(size_+ size);
	while (file >> key)
		PushBack(key);

	file.close();
}

//Adds to array random numbers in range min - max
void Array::GenerateRandom(int size, int min, int max)
{
	std::random_device rd;								//Uniformly-distributed pseudo random number generator
	std::mt19937 rng(rd());								//using the Mersenne Twister Algorithm
	std::uniform_int_distribution<int> uni(min, max);

	for (int i = 0; i < size; i++)
		PushBack(uni(rng));
}

//Displays the array, values separeted by " "
void Array::Display() 
{
	for (int i = 0; i < size_; i++)
	{
		std::cout << Get(i) << " ";
	}
	std::cout << std::endl;
}

//Checks if Empty
bool Array::IsEmpty()
{
	return size_ == 0 ? true : false;
}




