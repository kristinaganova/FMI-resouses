#pragma once
#include "constants.h"
#include "Column.h"

class Table {
private:
	int numRows;
	int numCols;
	Column columns[MAX_COLS];


	void tokenize(const char* input, char** output, char delimiter);
	void padString(char* input, int width);
public:
	Table();
	Table(int rows, int cols);

	const char* getValue(int row, int column);
	const char* getName(int column);
	int getColIndex(const char* colName);
	void loadFromFile(const char* fileName);
	void print();
	void setColumnName(int column, const char* name);
	void addRow(const char* row);
	void setValue(int row, int column, const char* value);
	void selectAndPrint(const char* column, const char* value);
	void saveToFile(const char* fileName);
	
};