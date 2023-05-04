/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 6, Linked Lists
PA6 File
*/

#include "PA6.h"
#include <string>

/***********************************************************
Function: displayMenu()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This function displays menu
***********************************************************/
void displayMenu() {
	cout << endl << "Welcome to the CPSC 122 Music Manager!!" << endl;
	cout << "Please choose from the following options: " << endl;
	cout << "1) Load library" << endl;
	cout << "2) Store library" << endl;
	cout << "3) Display library" << endl;
	cout << "4) Sort library" << endl;
	cout << "5) Search library" << endl;
	cout << "6) Insert song in order" << endl;
	cout << "7) Remove song" << endl;
	cout << "8) Edit song" << endl;
	cout << "9) Exit" << endl;
}

/***********************************************************
Function: getValidChoice()
Inputs: Nothign
Outputs: Returns int
General Description: 

This function checks to see if the user input is good input.
***********************************************************/
int getValidChoice() {
	int choice = -1;
	string temp;
	do {
		cout << "Choice: ";
		cin >> choice;
		if (choice < FIRST_OPTION || choice > LAST_OPTION) {
			cout << "That is not a valid option. Please try again." << endl;
		}
	} while (choice < FIRST_OPTION || choice > LAST_OPTION);
	getline(cin, temp); // flush the newline outta the buffer
	return choice;
}

/***********************************************************
Function: executeUserChoice()
Inputs: Song Library and user choice
Outputs: Returns nothing
General Description: 

This function performs tasks depending on what is the 
choice is. 
***********************************************************/
void executeUserChoice(int choice, SongLibrary& lib) {
	Song *songFound;
	string filename = "library.txt", anotherFileName, searchAttribute, searchAttributeValue, title, artist, genre, trash, changeAttribute, changedAttribute, searchAttributeGiven;
	bool foundSong;
	int indexOfSongFound, rating;

	switch (choice) {
		case 1:
			lib.performLoad(filename);
			break;
		case 2:
			anotherFileName = promptingUserForOutputFile();

			lib.performSave(anotherFileName);
			break;
		case 3: 
			lib.displayLibrary();
			break;
		case 4:
			cout << "What would you like to sort by?" << endl;
			cout << "Title | Artist | Genre | Rating" << endl;
			cin >> searchAttributeGiven;
			convertToLowercase(searchAttributeGiven);

			lib.setSortAttribute(searchAttributeGiven);
			
			lib.performSort();
			break;
		case 5:
			cout << "What attribute are you looking for?" << endl;
			getline(cin, searchAttribute);
			convertToLowercase(searchAttribute);

			cout << "What " << searchAttribute << " are you looking for?" << endl;
			getline(cin, searchAttributeValue);
			convertToLowercase(searchAttributeValue);

			songFound = lib.performSearch(searchAttribute, searchAttributeValue, &foundSong, &indexOfSongFound);

			if(foundSong) {
				cout << "We found the song!" << endl;
				cout << "Index that it was found: " << indexOfSongFound << endl << endl;
				songFound->displaySong();
			}
			else {
				cout << "We didn't find the song" << endl;
			}
			break;
		case 6:
			{
			cout << "What is the title of the new song?" << endl;
			getline(cin, title);
			convertToLowercase(title);

			cout << "Who is the artist/band of " << title << "?" << endl;
			getline(cin, artist);
			convertToLowercase(artist);
			
			cout << "What is the genre of " << title << "?" << endl;
			getline(cin, genre);
			convertToLowercase(genre);

			cout << "What would you rating " << title << " on a scale from 1-5?" << endl;
			cin >> rating;
			
			Song *newSong = new Song(title, artist, genre, rating);

			newSong->displaySong();

			lib.performInsertSongInOrder(newSong);
			}
			break;
		case 7:
			cout << "What attribute are you looking for? " << endl;
			getline(cin, searchAttribute);
			convertToLowercase(searchAttribute);

			cout << "What " << searchAttribute << " are you looking to remove" << endl;
			getline(cin, searchAttributeValue);
			convertToLowercase(searchAttributeValue);

			songFound = lib.performSearch(searchAttribute, searchAttributeValue, &foundSong, &indexOfSongFound);

			if(foundSong) {
				lib.performRemoveSong(songFound);
			}
			break;
		case 8:
			cout << "What attribute are you looking to change? " << endl;
			getline(cin, searchAttribute);
			convertToLowercase(searchAttribute);

			cout << "What " << searchAttribute << " are you looking for?" << endl;
			getline(cin, searchAttributeValue);
			convertToLowercase(searchAttributeValue);

			songFound = lib.performSearch(searchAttribute, searchAttributeValue, &foundSong, &indexOfSongFound);

			if(foundSong) {
				changedAttribute = change(searchAttribute);

				lib.performEditSong(songFound, searchAttribute, changedAttribute);
			}
			break;
		default:
			cout << "Unrecognized menu choice" << endl;
			break;
	}
}

/***********************************************************
Function: runMusicManger()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This function is a driver funciton for the displayMenu options.
It does what the title says, runs the music manager
***********************************************************/
void runMusicManager() {
	SongLibrary lib;
	
	int choice = -1;
	do {
		displayMenu();
		choice = getValidChoice();
		if (choice != QUIT_OPTION) {
			executeUserChoice(choice, lib);
		}
	} while (choice != QUIT_OPTION);
	cout << "Thanks for you using the CPSC 122 Music Manager!!" << endl;
}

string promptingUserForOutputFile(void) {
    string filename;

    cout << "Please enter the file that you would like to output to" << endl;
	cout << "<outputFileName>.txt" << endl;
    getline(cin, filename);
    
    return filename;
}

/***********************************************************
Function: change()
Inputs: Attribute that will be changed
Outputs: Returns the attribute value that will take place of
what's already there
General Description: 

This function takes in an attribtue and results the attribute 
value of what it will chagne. If it's an int, then it will further
prompt and make sure it won't bug out. 
***********************************************************/
string change(string attribute) {
	string change;

	if(attribute == "rating") {
		cout << "What are you changing the " << attribute << " to?" << endl;
		cout << "Please enter between 1-5" << endl;
		cin >> change;
		
		while(stoi(change) < 1 || stoi(change) > 5) {
			cout << "Not in range, please enter again" << endl;
			cin >> change;
		}
	}
	else {
		cout << "What are you changing the " << attribute << " to?" << endl;
		getline(cin, change);
	}

	return change;
}