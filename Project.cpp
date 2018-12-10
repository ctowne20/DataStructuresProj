//Data Structures Semester Project
//Carrieann Towne
//v1.0- October 28, 2018

// Math Homework Grading

/* Details of Project:
- Queue
- 2 MODES: 
	* Practice... doesn't save solutions or steps, but it creates a file with the 
		number of practice problems completed
	* Homework... stores each step of solution in file

- Store in .txt file
- Highlight answer in .txt file
- Display student/assignments as header in file
- Implemented voice reader to read out problems to grader
	* ISSUE: won't read x^2 as "x squared"
- Automatic grading?
*/

/* Project Notes:
For realism purposes, this project is based on Algebraic mathematics problems. 
It could be altered to tackle problems in the realm of calculus, trigonometry, etc. 
*/

#include <iostream>
#include <fstream>
#include <cwchar>
#include <windows.h>
#include <queue>
#include <string>
#include <vector>

using namespace std;

#define problem "x^2 + 3x - 4"

//Function prototypes
string steps();
void answer(string step);
void fileStuff(ofstream& FILE, queue<string> solution);

int main()
{
	queue<string> solution;
	string fileName, fName, lName, instructor, ID, problemNumber, userProblem;
	bool option, cont = 0;
	//CTextSpeaker voice; //Text to Speech implementation??

	//Display effects
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 0;
	font.dwFontSize.Y = 20;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy_s(font.FaceName, L"Calibri");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
	//REFERENCES: https://docs.microsoft.com/en-us/windows/console/console-font-infoex
	//			  https://stackoverflow.com/questions/35382432/how-to-change-the-console-font-size

	do
	{
		cout << "Welcome to the Mathematics Process Tracker! \n";
		cout << "Would you like to work on practice problems (enter 0) or homework problems (enter 1)? \n";
		cin >> option;

		cout << "First Name: ";
		cin >> fName;
		cout << endl << "Last Name: ";
		cin >> lName;
		cout << endl << "Instructor: ";
		cin >> instructor;
		cout << endl << "ID Number: ";
		cin >> ID;
		cout << endl << "Problem Number: ";
		cin >> problemNumber;

		if (!option)
		{
			ofstream PFILE;
			fileName = "PracticeFile.txt";
			PFILE.open(fileName);

			//Print header in output file
			PFILE << fName << " " << lName << endl << "Professor " << instructor << endl
				<< "Student Number " << ID << endl << "Problem " << problemNumber << ":" << endl;

			fileStuff(PFILE, solution);
			PFILE.close();


		}
		else if (option)
		{
			ofstream HFILE;
			fileName = "HomeworkFile.txt";
			HFILE.open(fileName);

			//Print header in output file
			HFILE << fName << " " << lName << endl << "Professor " << instructor << endl
				<< "Student Number " << ID << endl << "Problem " << problemNumber << ":" << endl;

			// 2 IMPLEMENTATION OPTIONS...
			// 1) User inputs problem
			cout << endl << endl << "Enter problem: ";
			cin >> userProblem;
			HFILE << "\t" << userProblem << endl << endl;

			// 2) Program displays problem
			cout << endl << endl << "Your problem:  " << problem << endl << endl;
			HFILE << problem << endl << endl;


			fileStuff(HFILE, solution);
			HFILE.close();

		}
		else
		{
			"Please enter 0 or 1!";
			cont = 1;
			continue;
		}
		cout << "Would you like to begin another assignment / practice? (Enter 1 to continue, 0 to exit)" << endl;
		cin >> cont;

	} while (cont);

	//voice.Speak(Lproblem); //Text to speech implementation??

	//Begin reading in solution
	solution.push(steps()); //push the string of each step into the stack 
							//by calling "steps" function

	system("pause");
	return 0;
}

string steps()
{
	string step;
	bool stop = 0;

	cout << "Solution: " << endl;
	cin >> step;

	if (step[0] == '*' && step[1] == '*')
		answer(step);

	return step;
}

void answer(string step)
{


}

void practice(ofstream PFILE)
{
	//print out practice problems
	//read in user data
	//if ouput equals "FINAL", system("cls"), print new problem
	//keep track of number of problems

	int practiceTracker = 0;
	string read;

	for (int i = 0; i < read.size(); i++)
	{
		PFILE << read[i];
	}

}

void fileStuff(ofstream& FILE, queue<string> solution)
{
	for (int i = 0; i < solution.size(); i++)
	{
		//pop for queue elements and display them in the file
		string temp = solution.front();
		solution.pop();
		FILE << temp << endl;
	}
	
}