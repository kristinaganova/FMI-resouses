#pragma once
#include "TextFile.h"

class FileManager {
	TextFile* files;
	int maxFiles;
	int numFiles;
public:
	FileManager(const FileManager& other);
	FileManager& operator=(const FileManager& other);
	FileManager(const TextFile* files, int maxFiles,
		int numFiles, int findFileIndex(char* name));
	~FileManager();
	FileManager(int maxFiles);

	void addFile(const char* name, const Time& createdAt ,const char* accessRigths);
	void editFile(const char* name, const char* content, const Time& modifiedAt, const char role);
	void appendToFile(const char* name, const char* content, const Time& time);
	void deleteFile(const char* name);
	void changeAccessRights(const char* name, const char* rigths);
    void printFileInfo(const char* name, const char role);
    void printFileContent(const char* name,const  char role);
    void printAllFiles(const char role);

	void sortByName();
	void sortByCreationTime();
	void sortByModificationTime();
	void sortBySize();
	void sortFiles(bool (*comparator)(const TextFile&, const TextFile&));

private:
	int findFileIndex(const char* name);
	void updateAccessRights(TextFile* file, const char* newRigths);
	void copyFrom(const FileManager& other);
	void free();
};