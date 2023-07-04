#include "constants.h"
#include "helperFunctions.h"
#include "Table.h"
#include <fstream>
#include <iostream>
#include <sstream>
#pragma warning (disable:4996)

void Table::tokenize(const char* input, char** output, char delimiter)
{
    char* token = strTok((char*)input, &delimiter);
    int i = 0;
    while (token != NULL) 
    {
        strCpy(output[i], token);
        token = strTok(NULL, &delimiter);
        i++;
    }
}

void Table::padString(char* input, int width) 
{
    int len = strLen(input);
    if (len < width) {
        for (int i = len; i < width; i++) 
        {
            input[i] = ' ';
        }
        input[width] = '\0';
    }
}

Table::Table(int rows, int cols)
{
    rows = this->numCols;
    cols = this->numRows;
}

Table::Table() :numRows(0), numCols(0) {};

void Table::setColumnName(int column, const char* name)
{
    strCpy(columns[column].name, name);
}

const char* Table::getValue(int row, int column) 
{
    if (row < 0 || row >= numRows || column < 0 || column >= numCols) 
    {
        return nullptr; 
    }
    return columns[column].rows[row].data[column];
}

const char* Table::getName(int column)
{
    if (column < 0 || column >= numCols) 
    {
        return nullptr; 
    }
    return columns[column].name;
}

int Table::getColIndex(const char* colName) {
    for (int i = 0; i < numCols; i++) {
        if (strcmp(columns[i].name, colName) == 0) {
            return i;
        }
    }
    return -1;
}

void Table::addRow(const char* row)
{
    char* rowData[MAX_COLS];
    tokenize(row, rowData, ',');

    for (int i = 0; i < numCols; i++)
    {
        int colIndex = getColIndex(getName(i));
        if (colIndex != -1) {
            setValue(numRows, colIndex, rowData[i]);
        }
    }

    numRows++;
}

void Table::setValue(int row, int column, const char* value)
{
    strCpy(columns[column].rows[row].data[column], value);
}

void Table::print() 
{
    for (int i = 0; i < numCols; i++) 
    {
        padString(columns[i].name, MAX_VALUE_SIZE);
        std::cout << columns[i].name << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            padString(columns[j].rows[i].data[j], MAX_VALUE_SIZE);
            std::cout << columns[j].rows[i].data[j] << " ";
        }
        std::cout << std::endl;
    }
}

void Table::selectAndPrint(const char* column, const char* value) 
{
    int colIndex = -1;
    for (int i = 0; i < numCols; i++)
    {
        if (strCmp(columns[i].name, column) == 0) 
        {
            colIndex = i;
            break;
        }
    }
    if (colIndex == -1) {
        std::cout << ERROR_COLUMN_FOUND << std::endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < numRows; i++) 
    {
        if (strCmp(columns[colIndex].rows[i].data[colIndex], value) == 0)
        {
            found = true;
            for (int j = 0; j < numCols; j++) {
                std::cout << columns[j].rows[i].data[j] << std::endl;
            }
            std::cout << std::endl;
        }
    }
    if (!found) {
        std::cout << ERROR_MATCHING_ROWS << std::endl;
    }
}

void Table::saveToFile(const char* fileName) 
{
    std::ofstream file(fileName);
    if (!file.is_open()) 
    {
        std::cout << OPEN_FILE_ERROR_MESSAGE << std::endl;
        return;
    }

    for (int i = 0; i < numCols; i++) 
    {
        file << columns[i].name << std::endl;
    }
    file << std::endl;

    for (int i = 0; i < numRows; i++) 
    {
        for (int j = 0; j < numCols; j++) 
        {
            file << columns[j].rows[i].data[j] << std::endl;
        }
        file << std::endl;
    }

    file.close();
    std::cout << SAVE_TO_FILE_MESSAGE << std::endl;
}

void Table::loadFromFile(const char* fileName)
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        std::cout << OPEN_FILE_ERROR_MESSAGE << std::endl;
        return;
    }

    char line[MAX_COLS * MAX_VALUE_SIZE];
    char columnNames[MAX_COLS][MAX_VALUE_SIZE];
    char columnName[MAX_VALUE_SIZE];
    int columnCount = 0;

    inputFile.getline(line, MAX_COLS * MAX_VALUE_SIZE);
    std::stringstream ss(line);

    while (ss.getline(columnName, MAX_VALUE_SIZE, ','))
    {
        strCpy(columnNames[columnCount], columnName);
        columnCount++;
        if (columnCount >= MAX_COLS)
        {
            std::cout << ERROR_MAXIMUM_COLUMNS << std::endl;
            return;
        }
    }
    numCols = columnCount;

    for (int i = 0; i < numCols; i++)
    {
        setColumnName(i, columnNames[i]);
    }

    int rowCount = 0;

    while (inputFile.getline(line, MAX_COLS * MAX_VALUE_SIZE) && rowCount < MAX_ROWS)
    {
        std::stringstream ss(line);
        char cellValue[MAX_VALUE_SIZE];
        int columnCount = 0;

        while (ss.getline(cellValue, MAX_VALUE_SIZE, ','))
        {
            setValue(rowCount, columnCount, cellValue);
            columnCount++;
            if (columnCount > numCols) {
                std::cout << ERROR_MAXIMUM_ROWS << rowCount + 1 << std::endl;
                return;
            }
        }

        if (columnCount < numCols)
        {
            std::cout << ERROR_MINIMUM_ROWS << rowCount + 1 << std::endl;
            return;
        }
        rowCount++;
    }
    numRows = rowCount;
    inputFile.close();
}