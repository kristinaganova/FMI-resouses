#include <iostream>
#include "FileAccess.h"
#include "helpers.h"

FileAccess::FileAccess(const char* permissions)
{
	strCpy(this->permissions, permissions);
	this->permissions[ACCES_RIGHTS_LEN] = '\0';
}

FileAccess::FileAccess() : permissions(""), role('\0') {}

bool FileAccess::canRead(char role) const
{
	switch (role)
	{
	case 'o':
		return permissions[0] == 'r';
	case 'g': 
		return permissions[3] == 'r';
	case 'a': 
		return permissions[6] == 'r';
	default:
		return false;
	}
}

bool FileAccess::canWrite(char role) const 
{
	switch (role) 
	{
	case 'o':
		return permissions[1] == 'w';
	case 'g': 
		return permissions[4] == 'w';
	case 'a': 
		return permissions[7] == 'w';
	default:
		return false;
	}
}

bool FileAccess::canExecute(char role) const 
{
	switch (role)
	{
	case 'o': 
		return permissions[2] == 'x';
	case 'g': 
		return permissions[5] == 'x';
	case 'a': 
		return permissions[8] == 'x';
	default:
		return false;
	}
}

void FileAccess::printRights(const FileAccess& fa, char role)
{
	std::cout << "Rights for role " << role << ": ";
	if (fa.canRead(role)) 
	{
		std::cout << "read ";
	}
	if (fa.canWrite(role)) 
	{
		std::cout << "write ";
	}
	if (fa.canExecute(role)) 
	{
		std::cout << "execute ";
	}
	if (!fa.canRead(role) && !fa.canWrite(role) && !fa.canExecute(role))
	{
		std::cout << "no permissions";
	}
	std::cout << std::endl;
}
