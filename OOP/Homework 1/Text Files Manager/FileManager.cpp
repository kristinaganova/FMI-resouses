#include "fileManager.h"
#include "helpers.h"
#include "errorList.h"
#include <iostream>

void FileManager::copyFrom(const FileManager& other)
{
	if (numFiles > maxFiles)
	{
		std::cout << ERROR_MAXIMUM_REACHED << std::endl;
		return;
	}

	maxFiles = other.maxFiles;
	numFiles = other.numFiles;
	files = new TextFile[maxFiles];

	for (int i = 0; i < maxFiles; i++)
	{
		files[i] = other.files[i];
	}
}

void FileManager::free()
{
	delete[] files;
}

FileManager::FileManager(const FileManager& other)
{
	copyFrom(other);
}

FileManager& FileManager:: operator=(const FileManager& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

FileManager::FileManager(const TextFile* files, int maxFiles,
	int numFiles, int findFileIndex(char* name))
{
	for (int i = 0; i < numFiles; i++)
	{
		this->files[i] = files[i];
	}
	this->maxFiles = maxFiles;
	this->numFiles = numFiles;
}

FileManager::FileManager(int maxFiles)
{
	this->maxFiles = maxFiles;
	this->numFiles = 0;
	this->files = new TextFile[maxFiles];
}

FileManager::~FileManager()
{
	free();
}

void FileManager::updateAccessRights(TextFile* file, const char* newRights)
{
	if (newRights == nullptr)
	{
		std::cout << ERROR_NULLPTR << std::endl;
		return;
	}

	FileAccess rights(newRights);
	file->setAccessRigths(rights);
}

int FileManager::findFileIndex(const char* name)
{
	for (int i = 0; i < numFiles; i++)
	{
		if (strCmp(files[i].getName(), name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void FileManager::addFile(const char* name, const Time& createdAt, const char* accessRights) 
{
	if (numFiles == maxFiles) 
	{
		std::cout << ERROR_MAXIMUM_REACHED << std::endl;
		return;
	}

	if (findFileIndex(name) != -1) 
	{
		std::cout << ERROR_DUBLICATES << std::endl;
		return;
	}

	files[numFiles] = TextFile(name, createdAt, accessRights);
	numFiles++;
	std::cout << FILE_SAVED_SUCCESS << std::endl;
}

void FileManager::editFile(const char* name, const char* content, const Time& modifiedAt, const char role)
{
	int index = findFileIndex(name);
	if (index == -1) 
	{
		std::cout << ERROR_FILE_NOT_FOUND << std::endl;
		return;
	}

	if (!files[index].hasAccess(role)) 
	{
		std::cout << ERROR_NO_ACCESS_EDDIT << std::endl;
		return;
	}

	files[index].setContent(content);
	files[index].setModifiedAt(modifiedAt);
	std::cout << FILE_EDITED_SUCCESS << std::endl;
}

void FileManager::appendToFile(const char* name, const char* content, const Time& time)
{
	int index = findFileIndex(name);
	if (index == -1) 
	{
		std::cout << ERROR_FILE_NOT_FOUND  << std::endl;
		return;
	}

	if (!files[index].hasAccess('w')) 
	{
		std::cout << ERROR_NO_ACCESS_APPEND << std::endl;
		return;
	}

	files[index].appendContent(content);
	files[index].setModifiedAt(time);
	std::cout << FILE_APPEND_SUCCESS << std::endl;
}

void FileManager::deleteFile(const char* name)
{
	int index = findFileIndex(name);
	if (index == -1)
	{
		std::cout << ERROR_FILE_NOT_FOUND << std::endl;
		return;
	}
	for (int i = index; i < numFiles - 1; i++) 
	{
		files[i] = files[i + 1];
	}
	numFiles--;
	std::cout << FILE_DELETED_SUCCESS << std::endl;
}

void FileManager::changeAccessRights(const char* name, const char* rights) 
{
	int index = findFileIndex(name);
	if (index == -1)
	{
		std::cout << ERROR_FILE_NOT_FOUND << std::endl;
		return;
	}
	TextFile* file = &files[index];
	updateAccessRights(file, rights);
}

void FileManager::printFileInfo(const char* name, const char role)
{
	int index = findFileIndex(name);
	if (index == -1)
	{
		std::cout << ERROR_FILE_NOT_FOUND << std::endl;
		return;
	}

	TextFile* file = &files[index];
	if (!file->hasAccess(role))
	{
		std::cout << ERROR_NO_ACCESS_VIEW << name << std::endl;
		return;
	}
	file->printInfo(role);
}

void FileManager::printFileContent(const char* name, const char role)
{
	int index = findFileIndex(name);
	if (index == -1) 
	{
		std::cout << ERROR_FILE_NOT_FOUND << std::endl;
		return;
	}

	TextFile& file = files[index];
	FileAccess rigths = file.getAccessRights();
	if (!file.hasAccess(role))
	{
		std::cout << ERROR_NO_ACCESS_READ << std::endl;
		return;
	}

	file.printContent();
}

void FileManager::printAllFiles(const char role)
{
	for (int i = 0; i < numFiles; i++) 
	{
		TextFile& file = files[i];
		FileAccess rigths = file.getAccessRights();

		if (file.hasAccess(role)) 
		{
			file.printInfo(role);
		}
	}
}

void FileManager::sortFiles(bool (*comparator)(const TextFile&, const TextFile&)) 
{
	bool swapped;
	do {
		swapped = false;
		for (std::size_t i = 1; i < numFiles; ++i)
		{
			if (comparator(files[i - 1], files[i])) 
			{
				std::exchange(files[i - 1], files[i]);
				swapped = true;
			}
		}
	} while (swapped);
}

void FileManager::sortByName()
{
	sortFiles([](const TextFile& a, const TextFile& b)
		{
		return a.compareByName(b);
		});
}

void FileManager::sortByCreationTime()
{
	sortFiles([](const TextFile& a, const TextFile& b) 
		{
		return a.compareByCreationTime(b);
		});
}

void FileManager::sortByModificationTime()
{
	sortFiles([](const TextFile& a, const TextFile& b) 
		{
		return a.compareByModificationTime(b);
		});
}

void FileManager::sortBySize() 
{
	sortFiles([](const TextFile& a, const TextFile& b) 
		{
		return a.compareBySize(b);
		});
}