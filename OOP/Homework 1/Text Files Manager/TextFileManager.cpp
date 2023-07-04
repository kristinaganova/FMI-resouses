#include "TextFile.h"
#include "FileManager.h"
#include "Time.h"
#include <iostream>

int main()
{
	FileManager fs(5);
	fs.addFile("test.txt", Time(2015, 02, 28, 12, 02, 23), "rwxr—r—");
	fs.editFile("test.txt", "Hello, world", Time(2023, 3, 20, 14, 10, 06), 'o');
	fs.printFileInfo("test.txt", 'a');
	fs.printAllFiles('o');

	return 0;
}