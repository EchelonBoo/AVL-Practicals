#include "AVLTree.h" //includes the header file with the AVL code
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int option = 0; //variable to store users option
	string str; //store the string that the user enters
	TreeType<string> AVL; //calls the TreeType and passes it a string --> creating a string AVL Tree
	do {

		//code to output option
		cout << "\n\n\t\t ****** AVL Tree Options ******\n"
			<< "\t\t1. Insert a string to the AVL Tree.\n"
			<< "\t\t2. Print the contents of the AVL Tree.\n"
			<< "\t\t3. Enter the String you would like to Search for.\n"
			<< "\t\t4. Enter a String to Delete.\n"
			<< "\t\t5. Exit the application\n"
			<< "\t\t\n Please choose an option:\n\n";

		cin >> option; //take in the users choice

		//switch statement to execute the right function based on users choice
		switch (option) {

		case 1: //insert
			cout << "\n\nPlease enter a string: \n";
			cin >> str;
			AVL.InsertItem(str);
			break;
		case 2: //print
			AVL.PrintItem();
			break;
		case 3: //search
			cout << "\n\nPlease enter a string: \n";
			cin >> str;
			AVL.SearchItem(str);
			break;
		case 4: //Delete
			cout << "\n\nPlease enter a string: \n";
			cin >> str;
			AVL.DeleteItem(str);
			break;
		case 5: //Exit
			break;
		default:
			"Please choose an option from the menu.\n";
			break;
		}
	} while (option != 5);

}

