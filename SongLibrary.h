/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 6, Linked Lists
Song Library Header File
*/

#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Song.h"

using namespace std;

void inputFileOpen(ifstream& inputFile);
void outputFileOpen(ofstream& outputFile);

class SongLibrary {
	private:
		Song *head;
		string sortAttribute;
	public:
		SongLibrary();
		SongLibrary(const SongLibrary&);
		~SongLibrary();
		Song* getHead() const; 
		void setHead(Song *); 
		string getSortAttribute() const; 
		void setSortAttribute(string); 
		
		void performLoad(string);
		void performSave(string);
		void performSort(); 
		Song* performSearch(string, string, bool *, int *); 
		void performInsertSongInOrder(Song *); 
		void performRemoveSong(Song *); 
		void performEditSong(Song *, string, string);
		void displayLibrary(void);
		void addToEnd(string title, string artist, string genre, int rating); 
};

#endif