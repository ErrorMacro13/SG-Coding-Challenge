//Author: Ben Owens
//Solution: SGInteractive Problem 1
//Date: 10/18/17
//Written in C++ using Visual Studio 2017
//Description: 
//-"Given a list of people with their birth and end years (all between 1900 and 2000), find the year with the most number of people alive."
//-This program loops through a number of years that it's given, reads through a list of people written on a .txt file, checks to see if those people were alive on the current year,
//-then returns which year had the most people alive. It then shows how many people were alive in each year given. The output is written to a console window.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//Year object to keep track of how many people are alive in the current year
struct Year
{
	unsigned yearNum;
	unsigned numPplAlive;
};

//Function to find out which year (between _minYear & _maxYear) has the most people alive
unsigned YearWithMostPeopleAlive(unsigned _minYear, unsigned _maxYear, vector<Year> &_years);

//Main function
void main()
{
	vector<Year> years;
	//Write the return value of the function to the console window
	cout << "Given the data submitted, the year with the highest number of people alive is: \n" << YearWithMostPeopleAlive(1900, 2000, years) << endl << endl;
	for (unsigned int i = 0; i < years.size(); i++)
	{
		cout << years[i].yearNum << ": " << years[i].numPplAlive << endl;
	}

	system("pause");
	return;
}

//Reads through a text file that has a list of people with their birth and death dates, and determines which year has the most people alive
//This function assumes that the list is in order of when the people were born. 
//This function assumes that the word "Birth:" is in front of the birth year and "Death:" in front of the death year.
//Arguments: _minYear & _maxYear. The range of years that the function searches.
//Return type: Unsigned int
unsigned YearWithMostPeopleAlive(unsigned _minYear, unsigned _maxYear, vector<Year> &years)
{
	//Start on the first year
	unsigned currentYear = _minYear;

	//Value to keep track of which year has the most people
	Year yearWithMost;
	yearWithMost.yearNum = currentYear;
	yearWithMost.numPplAlive = 0;
	

	//Loop from _minYear to _maxYear
	for (; currentYear < (_maxYear + 1); currentYear++)
	{
		//Create a pointer to the current year
		Year* currYearPtr = new Year();
		currYearPtr->yearNum = currentYear;
		currYearPtr->numPplAlive = 0;

		//Begin reading text file
		ifstream file;

		file.open("Problem1Data.txt");
		if (!file.is_open())
			cout << "File Not Found" << endl;

		//Strings to hold returned data
		string stringBuffer;
		string birthYear, deathYear;

		//Read the file word-by-word
		while (file >> stringBuffer)
		{
			//Check to see if the "Birth:" or "Death:" identifiers are present
			if (stringBuffer == "Birth:")
			{
				//Convert the string to a number
				file >> birthYear;
				stringstream birthStream(birthYear);
				int birthNum = 0;
				birthStream >> birthNum;
				
				//If the person was born after the year that we're checking, close out of the file and start over
				if (birthNum > currentYear)
				{
					file.close();
				}
				else if (birthNum <= currentYear)
				{
					//If the person was born before or during the current year, add them to the number of people alive
					currYearPtr->numPplAlive++;
				}
			}
			else if (stringBuffer == "Death:")
			{
				file >> deathYear;
				stringstream deathStream(deathYear);
				int deathNum = 0;
				deathStream >> deathNum;
				if (deathNum <= currentYear)
				{
					//If the person died on the current year, remove them from the number of people alive
					currYearPtr->numPplAlive--;
				}
			}

			//Close the file
			if (file.eof())
				file.close();
		}
		
		//If the year that was just checked has more people in it, set that to the year with the most people.
		//If the years have the same amount of people, set to the more recent year
		if (currYearPtr->numPplAlive >= yearWithMost.numPplAlive)
			yearWithMost = *currYearPtr;

		years.push_back(*currYearPtr);

		delete currYearPtr;
	}

	return yearWithMost.yearNum;
}