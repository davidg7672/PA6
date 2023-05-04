/*
David Sosa Vidal
CPSC 122
Professor Jacob Shea
Programming Assignment 6, Linked Lists
PA6 Header File
*/

#ifndef PA6_H
#define PA6_H

#include <iostream>
#include <fstream>
#include <string>
#include "Song.h"
#include "SongLibrary.h"

using namespace std;

const int QUIT_OPTION = 9;
const int FIRST_OPTION = 1;
const int LAST_OPTION = 9;

string change(string attribute);
void displayMenu();
int getValidChoice();
void executeUserChoice(int, SongLibrary&);
void runMusicManager();
string promptingUserForOutputFile(void);

#endif