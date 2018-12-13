//File creation for professor

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	ofstream PROBLEMS, ANSWERS;
	int answer;
	bool retry = 0, stop = 0;
	string temp, probFileName, ansFileName;

	do {
	
		cout << "Would you like to create practice or homework problems? (0 for practice, 1 for homework)  ";
		cin >> answer;
			
		retry = 0;
		
		if (answer == 0 || answer == 1)
		{
			cout << "Enter the name of your file: ";
			cin >> probFileName; // = "C:/Users/ctowne/Documents/Visual Studio 2017/practiceProblems.txt";
			PROBLEMS.open(probFileName);
			
			system("cls");
			
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

			cout << endl << "Thank you for entering the problems! Your file has been created as " << probFileName << endl << endl; //<< probFileName << endl << endl;

			cout << "Enter the name of your solution file: ";
			cin >> ansFileName;

			cout << endl << endl << "Enter solutions for your problems below (without spaces)!" << endl <<
				"Press Enter to move to the next problem. Enter 'END' to finish the answer key. " << endl << endl;

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

			cout << endl << "Thank you for entering the problems! Your file has been created as " << ansFileName
				<< endl << endl;
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