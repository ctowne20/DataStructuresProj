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

//EMAIL HELP https://www.emailarchitect.net/easendmail/ex/vc/14.aspx

//Function prototypes
void answer(queue<string> solution, ofstream& FILE);
queue<string> practice(queue<string> solution, vector<string>& assignmentVector, int pTracker);
queue<string> homework(queue<string> solution, vector<string> assignmentVector, int hTracker);
void fileStuff(ofstream& FILE, queue<string> solution);

int main()
{
	queue<string> solution;
	vector<string> assignmentVector;
	string fileName, fName, lName, instructor, ID, problemNumber, userProblem;
	bool option, cont = 0;
	int practiceTracker = 0, homeworkTracker = 0;
	//CTextSpeaker voice; //Text to Speech implementation??
	ifstream assignment;
	ofstream HFILE, PFILE;

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

	cout << "Welcome to the Mathematics Process Tracker! \n";
	cout << "Would you like to work on practice problems (enter 0) or homework problems (enter 1)? \n";
	cin >> option;

	cout << "First Name: ";
	cin >> fName;
	cout << "Last Name: ";
	cin >> lName;
	cout << "Instructor: ";
	cin >> instructor;
	cout << "ID Number: ";
	cin >> ID;

	if (!option) //Practice
	{
		fileName = "PracticeFile.txt";
		PFILE.open(fileName);

		assignment.open("C:/Users/ctowne/Documents/Visual Studio 2017/practiceProblems.txt");
		if (!assignment)
		{
			cout << "Unable to open file" << endl;
			system("pause");
			exit(1);
		}


		//Read professor's file into a vector
		string line;
		while (getline(assignment, line))
		{
			assignmentVector.push_back(line);
		}


		cout << "Practice Assignment: " << endl;

		do 
		{
			system("cls");
			//Print header in output file
			PFILE << "Practice Assignment" << endl << endl << fName << " " << lName << endl << "Professor " << instructor << endl
				<< "Student Number " << ID << endl << "Problem " << problemNumber << ":" << endl;

			solution = practice(solution, assignmentVector, practiceTracker);
			fileStuff(PFILE, solution);
			answer(solution, PFILE);

			cout << endl << endl << "Would you like to begin another assignment / practice? (Enter 1 to continue, 0 to exit)" << endl;
			cin >> cont;

		} while (cont);

	}
	else if (option) //Homework
	{
		fileName = "HomeworkFile.txt";
		HFILE.open(fileName);

		ofstream Grades;
		string gradefileName = lName + "Grade";
		Grades.open(gradefileName);

		assignment.open("assignedProblems.txt");
		if (!assignment)
		{
			cout << "Unable to open file" << endl;
			system("pause");
			exit(1);
		}

		//Print header in output file
		HFILE << fName << " " << lName << endl << "Professor " << instructor << endl
			<< "Student Number " << ID << endl << "Problem " << problemNumber << ":" << endl;

		solution = homework(solution, assignmentVector, homeworkTracker);
		fileStuff(HFILE, solution);
		answer(solution, HFILE);
	}
	else
	{
		cout << "Error: You must enter 0 for practice or 1 for homework";
		system("pause");
		exit(1);
	}

	//voice.Speak(Lproblem); //Text to speech implementation??
	HFILE.close();
	PFILE.close();
	assignment.close();

	system("pause");
	return 0;
}

//print out answer at the end of the File and at the bottom of the screen
void answer(queue<string> solution, ofstream& FILE)
{
	cout << endl <<  "Final Solution: " << endl << solution.back();
	FILE << endl <<  "Final Solution: " << endl << solution.back();
}

//read in user data for practice problems
//If output equals "FINAL", system("cls"), print the next problem
//keep track of number of problems
queue<string> practice(queue<string> solution, vector<string>& assignmentVector, int pTracker)
{
	pTracker++;
	string step;

	cout << "Problem: " << assignmentVector.front();
	assignmentVector.erase(assignmentVector.begin());
	cout << endl << "Please enter each step of your work. Press enter" 
		<< " between lines. Enter FINAL to finish the problem." << endl;

	do
	{
		cin >> step;
		solution.push(step);
	} while (step != "FINAL");

	return solution;
}

queue<string> homework(queue<string> solution, vector<string> assignmentVector, int hTracker)
{
	hTracker++;
	string step;

	cout << "Please enter each step of your work. Press enter"
		<< "between lines. Enter FINAL to finish the problem." << endl;

	while (step != "FINAL")
	{
		cin >> step;
		solution.push(step);
	}

	return solution;
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