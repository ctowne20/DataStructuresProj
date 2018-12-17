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
#include <ShlObj.h>
#pragma comment (lib, "shell32.lib") // HELP ON FILE PATH:
	//https://stackoverflow.com/questions/2414828/get-path-to-my-documents
using namespace std;

//EMAIL HELP https://www.emailarchitect.net/easendmail/ex/vc/14.aspx

//Function prototypes
bool answer(queue<string> solution, ofstream& FILE, vector<string> answers);
queue<string> practice(queue<string> solution, vector<string>& assignmentVector, int pTracker);
queue<string> homework(queue<string> solution, vector<string> assignmentVector, int hTracker);
void fileStuff(ofstream& FILE, queue<string> solution);

int main()
{
	queue<string> solution;
	vector<string> assignmentVector, answerVector;
	string probFileName, outFileName, ansFileName, gradeFileName,
		fName, lName, instructor, ID,  userProblem; //problemNumber,
	bool option, cont = 0;
	int practiceTracker = 0, homeworkTracker = 0, gradeTracker = 0;;
	//CTextSpeaker voice; //Text to Speech implementation??
	ifstream ASSIGNMENT, ANSWERS;
	ofstream HFILE, PFILE, GRADES;

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	string myDocumentString(my_documents);

	//Display effects
	/*CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 10;
	font.dwFontSize.Y = 20;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = 700;
	//wcscpy_s(font.FaceName, L"Calibri");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
	//REFERENCES: https://docs.microsoft.com/en-us/windows/console/console-font-infoex
	//			  https://stackoverflow.com/questions/35382432/how-to-change-the-console-font-size*/

	cout << "Welcome to the Mathematics Process Tracker! \n";
	cout << "Would you like to work on practice problems (enter 0) or homework problems (enter 1)?  ";
	cin >> option;

	cout <<  endl << "First Name: ";
	cin >> fName;
	cout << "Last Name: ";
	cin >> lName;
	cout << "Instructor: ";
	cin >> instructor;
	cout << "ID Number: ";
	cin >> ID;

	if (!option) //Practice
	{
		probFileName = myDocumentString + "/Visual Studio 2017/practiceProblems.txt"; 
		outFileName = myDocumentString + "/Visual Studio 2017/PracticeFile.txt";
		ansFileName = myDocumentString + "/Visual Studio 2017/practiceAnswers.txt";
		gradeFileName = myDocumentString + "/Visual Studio 2017/" + lName + "GradeFile.txt";

		//open practice
		PFILE.open(outFileName);
		if (!PFILE)
		{
			cout << endl << "Unable to open output file" << endl;
			system("pause");
			exit(1);
		}

		//Professor will provide a file with assignment problems. These lines open the file
		ASSIGNMENT.open(probFileName); //"C:/Users/ctowne/Documents/Visual Studio 2017/practiceProblems.txt"
		if (!ASSIGNMENT)
		{
			cout << "Unable to open problem file" << endl;
			system("pause");
			exit(1);
		}

		//open problem answer file
		ANSWERS.open(ansFileName);
		if (!ANSWERS)
		{
			cout << "Unable to open problem file" << endl;
			system("pause");
			exit(1);
		}

		//open grade file
		GRADES.open(gradeFileName);
		if (!GRADES)
		{
			cout << "Unable to open problem file" << endl;
			system("pause");
			exit(1);
		}

		//Read professor's file into a vector
		string line;
		while (getline(ASSIGNMENT, line))
		{
			assignmentVector.push_back(line);
		}

		//Read professor's answer file into a vector
		string aLine;
		while (getline(ANSWERS, aLine))
		{
			answerVector.push_back(aLine);
		}

		cout << "Practice Assignment: " << endl;
		//Print header in output file
		PFILE << "Practice Assignment" << endl << endl << fName << " " << lName << endl << "Professor " << instructor << endl
			<< "Student Number " << ID;


		//continue through problems until the user wants to stop
		do 
		{
			system("cls");
			
			//erase the queue
			while (!solution.empty())
				solution.pop();

			PFILE << endl << endl << "Problem: " << assignmentVector.front() << endl << "Steps: " << endl;

			solution = practice(solution, assignmentVector, practiceTracker);
			fileStuff(PFILE, solution);
			practiceTracker++;
			if (answer(solution, PFILE, answerVector))
				gradeTracker++;

			//remove the first element in the "answer" vector
			answerVector.erase(answerVector.begin());

			cout << endl << endl << "Would you like to continue practicing? (Enter 1 to continue, 0 to exit)" << endl;
			cin >> cont;

			//assignmentVector.erase(assignmentVector.begin());

		} while (cont && !assignmentVector.empty());

		//print grades to file!
		GRADES << "Practice Assignment" << endl << endl << fName << " " << lName << endl << "Professor "
			<< instructor << endl << "Student Number " << ID;
		GRADES << endl << endl << "Final Grade: " << gradeTracker << "/" << practiceTracker;

		//tell user the file name
		cout << endl << "Thank you for completing this practice! Your file has been saved as PracticeFile.txt";
	}
	else if (option) //Homework
	{
		outFileName = myDocumentString + "/Visual Studio 2017/HomeworkFile.txt";
		probFileName = myDocumentString + "/Visual Studio 2017/assignedProblems.txt";
		ansFileName = myDocumentString + "/Visual Studio 2017/assignmentAnswers.txt";
		gradeFileName = myDocumentString + "/Visual Studio 2017/gradeFile.txt";
		
		//open output file
		HFILE.open(outFileName);
		if (!HFILE)
		{
			cout << "Unable to open output file" << endl;
			system("pause");
			exit(1);
		}

		//open grades file
		gradeFileName = "C:/Users/ctowne/Documents/Visual Studio 2017/" + lName + "Grade.txt";
		GRADES.open(gradeFileName);
		if (!GRADES)
		{
			cout << "Unable to open grade file" << endl;
			system("pause");
			exit(1);
		}

		//open output problem file
		ASSIGNMENT.open(probFileName);
		if (!ASSIGNMENT)
		{
			cout << "Unable to open problem file" << endl;
			system("pause");
			exit(1);
		}

		//open problem answer file
		ANSWERS.open(ansFileName);
		if (!ANSWERS)
		{
			cout << "Unable to open problem file" << endl;
			system("pause");
			exit(1);
		}

		//Read professor's file into a vector
		string line;
		while (getline(ASSIGNMENT, line))
		{
			assignmentVector.push_back(line);
		}

		//Read professor's answer file into a vector
		string aLine;
		while (getline(ANSWERS, aLine))
		{
			answerVector.push_back(aLine);
		}


		cout << "Homework Assignment: " << endl;

		//Print header in output file
		PFILE << "Homework Assignment" << endl << endl << fName << " " << lName << endl << "Professor " << instructor << endl
			<< "Student Number " << ID;

		do 
		{
			system("cls");

			//erase the queue
			while (!solution.empty())
				solution.pop();

			HFILE << endl << endl << "Problem: " << assignmentVector.front() << endl << "Steps: " << endl;

			solution = homework(solution, assignmentVector, homeworkTracker);
			fileStuff(HFILE, solution);
			homeworkTracker++;
			if (answer(solution, HFILE, answerVector))
				gradeTracker++;

			//erase front of answer vector
			answerVector.erase(answerVector.begin());

			cout << endl << endl << "Would you like to continue on the assignment? (Enter 1 to continue, 0 to exit)" << endl;
			cin >> cont;

			//assignmentVector.erase(assignmentVector.begin());

		} while (cont && !assignmentVector.empty());

		//output grades to file!
		GRADES << "Homework Assignment" << endl << endl << fName << " " << lName << endl << "Professor " 
			<< instructor << endl << "Student Number " << ID;
		GRADES << endl << endl <<"Final Grade: " << gradeTracker << "/" << homeworkTracker;

		//tell user the file name
		cout << endl << "Thank you for completing this assignment! Your file has been saved as HomeworkFile.txt";
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
	ASSIGNMENT.close();

	cout << endl;
	system("pause");
	return 0;
}

//print out answer at the end of the File and at the bottom of the screen
bool answer(queue<string> solution, ofstream& FILE, vector<string> answers)
{
	cout << endl <<  "Final Solution: " << endl << solution.back();
	FILE << endl << endl <<  "Final Solution: " << endl << solution.back();

	if (solution.back() == answers.front())
	{
		cout << endl << "Solution is correct!";
		FILE << "\nCORRECT!" << endl;

		return TRUE;
	}
	else
	{
		cout << endl << "Solution is incorrect!";
		FILE << "\nINCORRECT!" << endl;

		return FALSE;
	}
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

	while (step != "FINAL")
	{
		cin >> step;
		if (step == "FINAL")
			continue;

		solution.push(step);
	}
	return solution;

}

queue<string> homework(queue<string> solution, vector<string> assignmentVector, int hTracker)
{
	hTracker++;
	string step;

	cout << "Problem: " << assignmentVector.front();
	assignmentVector.erase(assignmentVector.begin());
	cout << endl << "Please enter each step of your work. Press enter "
		<< "between lines. Enter FINAL to finish the problem." << endl;

	while (step != "FINAL")
	{
		cin >> step;
		if (step == "FINAL")
			continue;

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
		FILE << temp;
	}
}