/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 6, Linked Lists
Song Library File
*/

#include "SongLibrary.h"
#include <string>

/***********************************************************
Default Value Constructor: SongLibrary()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This funciton sets num songs to 0, and dynamically allocates
memory to the amoutn fo songs. Songs points to nothing. 
Essentially it's a blank library. 
***********************************************************/
SongLibrary::SongLibrary() {
	// initialize to empty list
	head = NULL; 
	// default sort attribute is title
	sortAttribute = "title";
}

/***********************************************************
Copy Constructor: SongLibrary()
Inputs: Other SongLibrary
Outputs: Nothing
General Description: 

This constructor will copy what on library has, and gives it
to another library.
***********************************************************/
SongLibrary::SongLibrary(const SongLibrary& other) {
	if(other.head == NULL) {
		head = nullptr;
		return;
	}

	head = new Song(*(other.head));

	Song *currSong = head;
	Song *copySong = other.getHead()->getNext();

	while(copySong != NULL) {
		currSong->setNext(new Song(*copySong));
		currSong = currSong->getNext();
		copySong = copySong->getNext();
	}

}

/***********************************************************
Destructor: ~SongLibrary()
Inputs: Nothing
Outputs: Nothing
General Description: 

This function dealllocates memory and sets songs ptr to null.
Not poining to anything, also sets the amount of songs to 0.
***********************************************************/
SongLibrary::~SongLibrary() {
	if(head == nullptr) {
		return;
	}

	if(head->getNext() == nullptr) {
		delete head;
		return;
	}

	Song *currSong = head;
	Song *prevSong = NULL;

	while(currSong != NULL) {
		prevSong = currSong;
		currSong = currSong->getNext();
		delete prevSong;
	}
}

/***********************************************************
Member funciton: getHead()
Inputs: Nothing
Outputs: Returns head pointer
General Description: 

This function will give the head of the linekd list, the start
or the entire linkedlist
***********************************************************/
Song* SongLibrary::getHead() const {
	return head;
}

/***********************************************************
Member funciton: getHead()
Inputs: Nothing
Outputs: Returns head pointer
General Description: 

This function will give you the opporutinty to change the 
value of head
***********************************************************/
void SongLibrary::setHead(Song *newHead) {
	if (head != NULL) {
		delete head;
	}
	
	head = newHead;
}

/***********************************************************
Member funciton: getSortAttribute()
Inputs: Nothing
Outputs: Returns string
General Description: 

This function will return the sortAttirbute
***********************************************************/
string SongLibrary::getSortAttribute() const {
	return sortAttribute;
}

/***********************************************************
Member funciton: setSortAttribute()
Inputs: String of new attribute
Outputs: Returns nothing
General Description: 

This function will allow you to set the sort attribute
***********************************************************/
void SongLibrary::setSortAttribute(string newSortAttribute) {
	sortAttribute = newSortAttribute;
}

/***********************************************************
Member Function: performLoad()
Inputs: String name of the input file
Outputs: Nothing
General Description: 

This function reads in the input file which is "library.txt",
doing this, it creates a linked list and inserts nodes at 
the end of the list
***********************************************************/
void SongLibrary::performLoad(string filename) {
	ifstream inputFile;
	string title, artist, genre, trash;
	int rating;

	// Opening file and checking to see if they are open
	inputFile.open(filename);
	inputFileOpen(inputFile);

	while(!inputFile.eof()) {
		getline(inputFile, title);
		getline(inputFile, artist);
		getline(inputFile, genre);
		inputFile >> rating;

		getline(inputFile, trash);
		getline(inputFile, trash);

		Song *newSong = new Song(title, artist, genre, rating);
		performInsertSongInOrder(newSong);
	}

	// Closing the input file
	inputFile.close();
}

/***********************************************************
Member Function: performSave()
Inputs: String name of the output file
Outputs: Nothing
General Description: 

This function writes out the songs from a linked list to the
output file
***********************************************************/
void SongLibrary::performSave(string filename) {
	ofstream outputFile;

	outputFile.open(filename);
	outputFileOpen(outputFile);

	Song *currSong = head;

	while(currSong != NULL) {
		outputFile << currSong->getTitle() << endl;
		outputFile << currSong->getArtist() << endl;
		outputFile << currSong->getGenre() << endl;
		outputFile << currSong->getRating() << endl << endl;

		currSong = currSong->getNext();
	}
	outputFile.close();
}

/***********************************************************
Member Function: performSort()
Inputs: Nothing
Outputs: Nothing
General Description: 

This function will sort the linked list, not specific sorting
algorithm, it's divide and conquer. 
***********************************************************/
void SongLibrary::performSort() {
	if(head == NULL) {
		return;
	}

	Song *newHead = head;
	head = NULL;

	Song *cur = newHead;
	Song *next;

	while(cur != NULL) {
		next = cur->getNext();
		this->performInsertSongInOrder(cur);
		cur = next;
	}
	this->performInsertSongInOrder(cur);
}

/***********************************************************
Member Function: performSearch()
Inputs: Search attribute, search attribute value, bool ptr,
index ptr.
Outputs: Nothing
General Description: 

This funciton performs a linear serach and walks thorugh head 
node in the linked list. Returns true if found, and false NULL,
if not found.
***********************************************************/
Song* SongLibrary::performSearch(string searchAttribute, string searchAttributeValue, bool *found, int *index) {
	if(head == NULL) {
		cout << "Empty List" << endl;
		return NULL;
	}
	
	Song *currSong = head;
	string s;
	int counter = 0;
	
	while(currSong != NULL) {
		s = currSong->getStringAttributeValue(searchAttribute);

		if(s == searchAttributeValue) {
			*found = true;
			*index = counter;
			return currSong;
		}
		currSong = currSong->getNext();
		counter++;
	}
	return NULL; 
}

/***********************************************************
Member Function: performInsertSongInOrder()
Inputs: Song to add memory address
Outputs: Returns Nothing
General Description: 

This function will insert a song in order via alphabetically,
depending on wha the user wants to insert it order by.
***********************************************************/
void SongLibrary::performInsertSongInOrder(Song *songToInsert) {
	if(head == NULL) {
		head = songToInsert;
		head->setNext(NULL);
		return;
	}

	Song * cur = head;
	Song * prev = NULL;

	// Moves the two node pointers along the list
    while(cur != nullptr && cur->getStringAttributeValue(sortAttribute) < songToInsert->getStringAttributeValue(sortAttribute)){ 
        prev = cur;
        cur = cur->getNext();
    }

    // Handles case of insertion at the front
    if(prev == nullptr) {
        songToInsert->setNext(head);
        head = songToInsert;
    }
    // Handles case of insertion anywhere else in the list
    else {
        prev->setNext(songToInsert);
        songToInsert->setNext(cur);
    }
}

/***********************************************************
Member Function: performRemoveSong()
Inputs: Index of a song
Outputs: Returns Nothing
General Description: 

This function searches for the song to remove. When it finds
the song, pass over it. Deallocates memory of the song to 
remove. Remoevs from library
***********************************************************/
void SongLibrary::performRemoveSong(Song *songToRemove) {
	if(head == NULL) {
		return;
	}

	Song *currSong = head;
	Song *prevSong = NULL;

	while(currSong != NULL && currSong != songToRemove) {
		prevSong = currSong;
		currSong = currSong->getNext();
	}

	if(prevSong == NULL) {
		head = head->getNext();
		delete currSong;
	}
	else if (currSong == NULL) {
		cout << "Didn't find value that you were looking for" << endl;
		return;
	}
	else {
		prevSong->setNext(currSong->getNext());
		delete currSong;
	}
}

/***********************************************************
Member Function:: performEditSong()
Inputs: Memory address of song to edit, attribute that will
		be edited, and the values that that attribute will
		turn to.

Outputs: Returns nothing
General Description: 

This funciton edits the value of attribute that is given,
so if someone passes in title as attribute, then you are 
given the ablitity to change the attribute
***********************************************************/
void SongLibrary::performEditSong(Song *songToEdit, string attribute, string newAttributeValue) {	
	Song *currSong = head;

	while(currSong != songToEdit) {
		currSong = currSong->getNext();
	}
	
	if(attribute == "title") {
		currSong->setTitle(newAttributeValue);
	}
	else if (attribute == "artist") {
		currSong->setArtist(newAttributeValue);
	}
	else if(attribute == "genre") {
		currSong->setGenre(newAttributeValue);
	}
	else {
		currSong->setRating(stoi(newAttributeValue));
	}
}

/***********************************************************
Function: inputFileOpen()
Inputs: Input file
Outputs: Returns nothing
General Description: 

This function checks to see if the input file is open
***********************************************************/
void inputFileOpen(ifstream& inputFile) {
    if(!inputFile.is_open()) {
        cout << "File failed to open" << endl;
        exit(-1);
    }
}

/***********************************************************
Member Function: displayLibrary()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This member function displays the library by find couting
each song, until currSong equals nullptr
***********************************************************/
void SongLibrary::displayLibrary() {
	Song *currSong = head;
	
	while(currSong != NULL) {
		currSong->displaySong();
		currSong = currSong->getNext();
	}
}

/***********************************************************
Function: outputFileOpen()
Inputs: Output File
Outputs: Returns nothing
General Description: 

This function checks to see if the output file is open
***********************************************************/
void outputFileOpen(ofstream& outputFile) {
    if(!outputFile.is_open()) {
        cout << "File failed to open" << endl;
        exit(-1);
    }
}