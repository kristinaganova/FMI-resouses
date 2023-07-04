#include "helpers.h"
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