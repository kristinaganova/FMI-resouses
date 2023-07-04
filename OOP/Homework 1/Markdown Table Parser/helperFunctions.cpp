#include "helperFunctions.h"
#include <iostream>

int strLen(const char* str) 
{
	int size = 0;
	while (str[size] != '\0') 
	{
		size++;
	}

	return size;
}

int strCmp(const char* str1, const char* str2)
{
	int i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
		i++;
	}
	return 0;
}

char* strCpy(char* destination, const char* source)
{
	char* ptr = destination;
	while (*source) 
	{
		*destination++ = *source++;
	}
	*destination = '\0';
	return ptr;
}

//help from chat gpt for strTok
char* strTok(char* str, const char* delim) 
{
	static char* nextToken = nullptr;
	if (str != nullptr) 
	{
		nextToken = str;
	}
	if (nextToken == nullptr) 
	{
		return nullptr;
	}
	char* token = nextToken;
	char* delimiter = nullptr;
	while (*nextToken != '\0') 
	{
		delimiter = (char*)delim;
		while (*delimiter != '\0') 
		{
			if (*nextToken == *delimiter) 
			{
				*nextToken = '\0';
				nextToken++;
				return token;
			}
			delimiter++;
		}
		nextToken++;
	}
	return token;
}

