#include "main.h"
#include "./Stormlib/Stormlib.h"

int main(void) {
	char * mpqFile = _strdup("Battle.net.mpq");
	char * targetFile = _strdup("resources\\play\\GameTabList.qml");
	char * resultingFile = _strdup("GameTabListOld.qml");
	char * finishedFile = _strdup("GameTabList.qml");
	
	//Find .mpq file
	string highestVersionFolder = findNewestVersionFolder();
	string targetString = highestVersionFolder + "\\" + mpqFile;
	char* targetMPQFile = _strdup(targetString.c_str());

	cout << "Target has been identified as " << endl << targetString << endl;
	//Extract GameTabList.qml for editing
	ExtractFile(targetMPQFile, targetFile, resultingFile);

	//Edit GameTabList.qml
	removeActivisionGames(GetExeDir() + resultingFile, GetExeDir() + finishedFile);

	//Write changed GameTabList.qml back into the .mpq archive

	free(mpqFile);
	free(targetFile);
	free(resultingFile);
	free(finishedFile);
	free(targetMPQFile);
	

	return 0;
}

bool removeActivisionGames(string sourceQMLFile, string targetQMLFile) {
	string searchString = "visible:{return gameController.activisionProductsModel.count>0";
	string replaceString = "visible:{return false";//"visible:{return false";

	ifstream filein(sourceQMLFile, ios::in);
	ifstream fileout(targetQMLFile, ios::trunc);
	
	filein >> noskipws;

	if (!filein.is_open() || !filein) {
		return -1;
	}
	
	int foundAtPos = -1;
	string buffer;

	getline(filein, buffer);
	cout << buffer;
	foundAtPos = buffer.find_first_of(searchString);

	//TODO: Replace part and store buffer to file
	
	return 0;
}

string findNewestVersionFolder() {
	string path = GetExeDir();
	vector<string> existingDirs = getSubDirs(path);
	string highestFolder;
	int highestVersionNumber = 0;
	for (auto & dir : existingDirs) {
		int currentVersion = stoi(dir.substr(dir.length() - 5, dir.length()));
		if (currentVersion > highestVersionNumber) {
			highestFolder = dir;
			cout << "Highest version folder seems to be " << dir.substr(dir.length()-16, dir.length()) << endl;
		}
	}
	return highestFolder;
}

vector<string> getSubDirs(const std::string& s)
{
	std::vector<string> r;
	for (auto& p : directory_iterator(s))
		if (p.status().type() == file_type::directory) {
			cout << "Identified subdirectory " << p.path().string() << endl;
			r.push_back(p.path().string());
		}
	return r;
}

string GetExeDir() {
	TCHAR filename[MAX_PATH + 1];
	string strExe;
	if (GetModuleFileName(NULL, filename, MAX_PATH) != 0)
	{
		strExe = filename;
	}
	int cutOff = strExe.find_last_of('\\');
	return strExe.substr(0, cutOff+1);
}

//-----------------------------------------------------------------------------
// Opens an archived file and writes a file into it.
//
// Parameters :
//
//   char * szArchiveName  - Archive file name
//   char * szArchivedFile - Name/number of archived file.
//   char * szFileName     - Name of the target disk file.
static int ModifyFile(char * szFileName) {

}

//-----------------------------------------------------------------------------
// Opens an archived file and writes a file into it.
//
// Parameters :
//
//   char * szArchiveName  - Archive file name
//   char * szArchivedFile - Name/number of archived file.
//   char * szFileName     - Name of the target disk file.

static int WriteFile(char * szArchiveName, char * szArchivedFile, char * szFileName) {

}

//-----------------------------------------------------------------------------
// Extracts an archived file and saves it to the disk.
//
// Parameters :
//
//   char * szArchiveName  - Archive file name
//   char * szArchivedFile - Name/number of archived file.
//   char * szFileName     - Name of the target disk file.

static int ExtractFile(char * szArchiveName, char * szArchivedFile, char * szFileName)
{
	HANDLE hMpq = NULL;          // Open archive handle
	HANDLE hFile = NULL;          // Archived file handle
	HANDLE handle = NULL;          // Disk file handle
	int    nError = ERROR_SUCCESS; // Result value

								   // Open an archive, e.g. "d2music.mpq"
	if (nError == ERROR_SUCCESS)
	{
		if (!SFileOpenArchive(szArchiveName, 0, 0, &hMpq))
			nError = GetLastError();
	}

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if (nError == ERROR_SUCCESS)
	{
		if (!SFileOpenFileEx(hMpq, szArchivedFile, 0, &hFile))
			nError = GetLastError();
	}

	// Create the target file
	if (nError == ERROR_SUCCESS)
	{
		handle = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
		if (handle == INVALID_HANDLE_VALUE)
			nError = GetLastError();
	}

	// Read the file from the archive
	if (nError == ERROR_SUCCESS)
	{
		char  szBuffer[0x10000];
		DWORD dwBytes = 1;

		while (dwBytes > 0)
		{
			SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
			if (dwBytes > 0)
				WriteFile(handle, szBuffer, dwBytes, &dwBytes, NULL);
		}
	}

	// Cleanup and exit
	if (handle != NULL)
		CloseHandle(handle);
	if (hFile != NULL)
		SFileCloseFile(hFile);
	if (hMpq != NULL)
		SFileCloseArchive(hMpq);

	return nError;
}