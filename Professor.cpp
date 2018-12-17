//File creation for professor

#include <iostream>
#include <fstream>
#include <string>
#include <shlobj.h>
using namespace std;

#pragma comment(lib, "shell32.lib")

int main()
{
	ofstream PROBLEMS, ANSWERS;
	int answer;
	bool retry = 0, stop = 0;
	string temp, probFileName, ansFileName;

	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	string myDocumentString(my_documents);

	do {

		cout << "Would you like to create practice or homework problems? (0 for practice, 1 for homework)  ";
		cin >> answer;

		retry = 0;
		if (answer == 0)
		{
			system("cls");
			probFileName = myDocumentString + "/Visual Studio 2017/practiceProblems.txt";
			PROBLEMS.open(probFileName);

			cout << "Enter problems below (without spaces)!" << endl <<
				"Press Enter to move to the next problem. Enter 'END' to finish assignment. " << endl << endl;

			while (!stop)
			{
				cin >> temp;
				if (temp != "END")
					PROBLEMS << temp << endl;
				else
					stop = 1;
			}

			PROBLEMS.close();

			cout << endl << "Thank you for entering the problems! Your file has been created as practiceProblems.txt" << endl << endl; //<< probFileName << endl << endl;
			cout << "Enter solutions for your problems below (without spaces)!" << endl <<
				"Press Enter to move to the next problem. Enter 'END' to finish the answer key. " << endl << endl;

			ansFileName = myDocumentString + "/Visual Studio 2017/practiceAnswers.txt";
			ANSWERS.open(ansFileName);

			stop = 0;
			while (!stop)
			{
				cin >> temp;
				if (temp != "END")
					ANSWERS << temp << endl;
				else
					stop = 1;
			}

			ANSWERS.close();

			cout << endl << "Thank you for entering the problems! Your file has been created as practiceAnswers.txt" //<< ansFileName << endl <<
				<< endl << endl;
		}

		else if (answer == 1)
		{
			system("cls");
			probFileName = myDocumentString + "/Visual Studio 2017/assignedProblems.txt";
			PROBLEMS.open(probFileName);

			cout << "Enter problems below (without spaces)!" << endl <<
				"Press Enter to move to the next problem. Enter 'END' to finish assignment. " << endl << endl;

			while (!stop)
			{
				cin >> temp;
				if (temp != "END")
					PROBLEMS << temp << endl;
				else
					stop = 1;
			}

			PROBLEMS.close();

			cout << endl << "Thank you for entering the problems! Your file has been created as assignedProblems.txt" << endl << endl; //<< probFileName << endl << endl;
			cout << "Enter solutions for your problems below (without spaces):" << endl <<
				"Press Enter to move to the next problem. Enter 'END' to finish the answer key. " << endl << endl;

			ansFileName = myDocumentString + "/Visual Studio 2017/assignmentAnswers.txt";
			ANSWERS.open(ansFileName);

			stop = 0;
			while (!stop)
			{
				cin >> temp;
				if (temp != "END")
					ANSWERS << temp << endl;
				else
					stop = 1;
			}

			ANSWERS.close();

			cout << endl << "Thank you for entering the problems! Your file has been created as assignmentAnswers.txt" << endl << //<< ansFileName << endl <<
				"Happy grading! :)" << endl << endl;
		}
		else
		{
			cout << "Error! Enter 0 for practice or 1 for homework." << endl;
			retry = 1;
			system("cls");
		}

	} while (retry);

	system("pause");
	return 0;
}