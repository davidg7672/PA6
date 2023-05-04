/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 6, Linked Lists
Song File
*/

#include "Song.h"
#include <string>

/***********************************************************
Function: coverToLowercase()
Inputs: String value
Outputs: Lowercase string value
General Description: 

This function takes in a string, and converts it into a lower
case string
***********************************************************/
string convertToLowercase(string s) {
	for(int i = 0; i < s.length(); i++) {
		tolower(s[i]);
	}
	return s;
}

/***********************************************************
Default Value Constructor: Song()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This constructor sets all attributes to default values
***********************************************************/
Song::Song() {
	title = "";
	artist = "";
	genre = "";
	rating = 1;

	next = nullptr;
}

/***********************************************************
Explicit Value Constructor: Song()
Inputs: Title, artist, genre, and rating
Outputs: Returns nothing
General Description: 

This EVC changes all the parameters
***********************************************************/
Song::Song(string titleParam, string artistParam, string genreParam, int ratingParam) {
	title = titleParam;
	artist = artistParam;
	genre = genreParam;
	setRating(ratingParam);

	next = NULL;
}

/***********************************************************
Destructor: ~Song()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This function sets everything back to default values
***********************************************************/
Song::Song(const Song& other) {
	title = other.title;
	artist = other.artist;
	genre = other.genre;
	setRating(other.rating);

	next = NULL;
}

/***********************************************************
Member Function: getTitle()
Inputs: Output File
Outputs: Returns string
General Description: 

This member function 
***********************************************************/
string Song::getTitle() {
	return title;
}

/***********************************************************
Member Function: setTitle()
Inputs: Title name
Outputs: Returns nothing
General Description: 

This funciton sets title to the new title being passed in. 
Used to change title name of current song.
***********************************************************/
void Song::setTitle(string newTitle) {
	title = convertToLowercase(newTitle);
}

/***********************************************************
Member Function: getArtist()
Inputs: Nothing
Outputs: Returns string
General Description: 

This member funciton returns the artist name of the current
song being called.
***********************************************************/
string Song::getArtist() {
	return artist;
}

/***********************************************************
Member Function: setArtist()
Inputs: Takes in a new artist
Outputs: Returns nothing
General Description: 

This function sets artist to the artist being passed in. 
***********************************************************/
void Song::setArtist(string newArtist) {
	artist = convertToLowercase(newArtist);
}

/***********************************************************
Member Function: getGenre()
Inputs: Nothing
Outputs: Returns nothing
General Description: 

This function returns genre
***********************************************************/
string Song::getGenre() {
	return genre;
}

/***********************************************************
Member Function: setGenre()
Inputs: New Genre that is being set
Outputs: Returns nothing
General Description: 

This funciton sets genre to the new genre
***********************************************************/
void Song::setGenre(string newGenre) {
	genre = convertToLowercase(newGenre);
}

/***********************************************************
Member Function: getRating();
Inputs: Nothing
Outputs: Returns int
General Description: 

Returns rating of current Song object
***********************************************************/
int Song::getRating() {
	return rating;
}

/***********************************************************
Member Function: setRating()
Inputs: New Rating
Outputs: Returns nothing
General Description: 

This function checks to see if the new rating that is passed
through, marks the boxes of the conditions. Which would be 
new rating being, between 1 and 5
***********************************************************/
void Song::setRating(int newRating) {
	if (newRating < MIN_RATING || newRating > MAX_RATING) {
		cout << "Rating must be in [" << MIN_RATING << ", " << MAX_RATING << "]" << endl;
	}
	if (newRating < MIN_RATING) {
		rating = MIN_RATING;
	}
	else if (newRating > MAX_RATING) {
		rating = MAX_RATING;
	}
	else {
		rating = newRating;
	}
}

/***********************************************************
Member Function: getNext()
Inputs: Nothing
Outputs: Returns pointer
General Description: 

This function returns the next element in the linked list,
via pointer
***********************************************************/
Song* Song::getNext() {
	return next;
}

/***********************************************************
Member Function: setNext()
Inputs: New Next pointer
Outputs: Returns nothing
General Description: 

This function will set the value of 'next' to the parameters
passed in. Change what comes next in the linked list
***********************************************************/
void Song::setNext(Song *newNext) {
	next = newNext;
}

/***********************************************************
Member Function: getStringAttributeValue()
Inputs: String of Attribute
Outputs: Return the attribute real value
General Description: 

This function takes in a a string of an attribute, and returns
the actual value according to what was passed in.
***********************************************************/
string Song::getStringAttributeValue(string attribute) {
	if(attribute == "title") {
		return title;
	}
	else if (attribute == "artist") {
		return artist;
	}
	else if(attribute == "genre") {
		return genre;
	}
	else if(attribute == "rating") {
		return to_string(rating);
	}
	return "";
}

/***********************************************************
Member Function: displaySong()
Inputs: Nothign
Outputs: Returns nothing
General Description: 

This member funciton outputs the songs' title, artist, genre
and rating when called
***********************************************************/
void Song::displaySong() {
	cout << title << endl;
	cout << artist << endl;
	cout << genre << endl;
	cout << rating << endl << endl;
}