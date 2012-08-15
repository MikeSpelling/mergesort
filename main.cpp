// C++ program to read numbers from a file and print the lowest, median and highest values.
// Created by Michael R Spelling, 2009.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct data // Structure to hold the numbers entered and their original positions.
{
	double value;
	int position;
};

void sort(vector<data> &number, vector<data> &temp, int start, int end);
void merge(vector<data> &number, vector<data> &temp, int start, int centre, int end);

int main()
{
	vector<data> number; // Vector to hold numbers as they are entered.
	vector<data> temp; // Temporary vector to be used to merge numbers.
	data current;
	string number_string;
	char filename[32]; // Assume file name less than 32 characters long. If longer program may crash. In practice this should not be a problem.
	int place = 0;
	int length;
	cout << "Enter name of file to be opened: ";
	cin >> filename;
	ifstream file(filename); // Open desired file.
	if(!file)
	{
		cout << "Error: Can't open the file named " << filename << ".\n";
		return(0);
	}
	 while(!file.eof()) // Read input from the file, convert to double and enter it into the vector with its position.
	{
		place++;
		getline(file, number_string);
		current.value = strtod(number_string.c_str(), NULL);
		current.position = place;
		number.push_back(current);
	}
	temp.resize((number.size() + 1 )/ 2); // Resize temporary vector to be half the size of the real vector

	// Merge sort was chosen for the sort algorithm as it is O[NLog(N)] and so one of the most efficient sorting algorithms.
	// Unlike quicksort its worst case is still O(NLog(N)), not O(N^2) and so will not create delays for certain
	// sequences of numbers. As there are an arbitrary amount of numbers being entered there could be quite a lot
	// so it is important that the sorting algorithm performs quikly.
	// It does use additional memory to store a temporary vector in order to swap values but this only has
	// a size n/2 due to the implementation. As memory is not a problem and the specification
	// makes no mention of it, it was assumed that this additional memory would cause no problems.
	// Due to its stability, efficiency and divide and conquer strategy, merge sort was decided to be
	// the best option for this task.

	sort(number, temp, 0, number.size() - 1);

	length = number.size() - 1;

	place = 0; // Print out the lowest number and check if it is repeated to also show its multiple input positions.
	while(number[place].value == number[place + 1].value)
		place++;
	cout << endl << "Lowest value = " << number[place].value << " at line " << number[place].position;
	while(place-- > 0)
		cout << " and " << number[place].position;
	cout << "." << endl;

	place = length; // Print out the highest number and check if it is repeated to also show its multiple input positions.
	while(number[place].value == number[place - 1].value)
		place--;
	cout << "Highest value = " << number[place].value << " at line " << number[place].position;
	while(place++ < length)
		cout << " and " << number[place].position;
	cout << "." << endl;

	cout << "Median value = "; // Check if vector is of odd length and if so print out middle value and position.

	// To check whether the vector is odd divide the length by 2. If it is odd (i.e. 7) then this will give
	// 3.5 as the answer, this will then be rounded down to 3 as it is only an integer. When it is then multiplied
	// back by 2 the answer will be 6 rather than the original 7.

	if((number.size() / 2) * 2 != number.size())
		cout << number[length / 2].value << " at line " << number[length / 2].position << "." << endl << endl;
	else // Else print the average of middle 2 numbers and their positions.
		cout << (number[length / 2].value + number[(length / 2) + 1].value) / 2 << " from lines "
		<< number[length / 2].position << " and " << number[(length / 2) + 1].position << "." << endl << endl;

	file.close();
	return(0);
}

void sort(vector<data> &number, vector<data> &temp, int start, int end)
{
	if(start < end)
	{
		 int centre = (start + end) / 2;
		 sort(number, temp, start, centre);
		 sort(number, temp, centre+1, end);
		 merge(number, temp, start, centre, end);
	}
}

void merge(vector<data> &number, vector<data> &temp, int start, int centre, int end)
{
	 int tmp_pos = 0;
	 int num_pos = start;
	 int final_pos = start;

	 while(num_pos <= centre)
	 {
		 temp[tmp_pos].value = number[num_pos].value;
		 temp[tmp_pos++].position = number[num_pos++].position;
	 }

	 tmp_pos = 0;

	 while(final_pos < num_pos && num_pos <= end)
	 {
		if(temp[tmp_pos].value <= number[num_pos].value)
		{
			 number[final_pos].value = temp[tmp_pos].value;
			 number[final_pos++].position = temp[tmp_pos++].position;
	 }
	 else
	 {
		 number[final_pos].value = number[num_pos].value;
		 number[final_pos++].position = number[num_pos++].position;
	 }
	 }

	 while(final_pos < num_pos)
	 {
		 number[final_pos].value = temp[tmp_pos].value;
		 number[final_pos++].position = temp[tmp_pos++].position;
	 }
}
