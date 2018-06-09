#pragma once


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name  
using namespace std::experimental::filesystem::v1;


using namespace std;

//Functions utilizing Stormlib
static int ExtractFile(char * szArchiveName, char * szArchivedFile, char * szFileName);
static int ModifyFile(char * szFileName);
static int WriteFile(char * szArchiveName, char * szArchivedFile, char * szFileName);

//Functions to determine target file
std::vector<std::string> getSubDirs(const std::string& s);
string findNewestVersionFolder();
string GetExeDir();

//Functions to modify extracted files
bool removeActivisionGames(string sourceQMLFile, string targetQMLFile);