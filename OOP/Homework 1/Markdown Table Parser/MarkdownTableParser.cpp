#include <iostream>
#include "Table.h"
#include "helperFunctions.h"
#include "constants.h"

using namespace std;

int main() 
{
    Table table;

    char command[MAX_COMMAND_LEN];
    while (true) {
        cout << "Enter a command (add, print, select, save, load, quit): ";
        cin >> command;
        if (strCmp(command, ADD_ROW_COMMAND) == 0) {
            cout << "Enter a row to add: ";
            char row[MAX_ROWS];
            cin >> row;
            table.addRow(row);
        }
        else if (strCmp(command, PRINT_COMMAND) == 0) {
            table.print();
        }
        else if (strCmp(command, SELECT_WHERE_COMMAND) == 0) {
            char column[MAX_COLS], value[MAX_VALUE_SIZE];
            cout << "Enter column name to search: ";
            cin >> column;
            cout << "Enter value to search: ";
            cin >> value;
            table.selectAndPrint(column, value);
        }
        else if (strCmp(command, SAVE_TO_FILE) == 0) {
            char fileName[MAX_VALUE_SIZE];
            cout << "Enter file name to save to: ";
            cin >> fileName;
            table.saveToFile(fileName);
        }
        else if (strCmp(command, LOAD_FROM_FILE) == 0) {
            char fileName[MAX_VALUE_SIZE];
            cout << "Enter file name to load from: ";
            cin >> fileName;
            table.loadFromFile(fileName);
        }
        else if (strCmp(command, QUIT_COMMAND) == 0) {
            break;
        }
        else {
            cout << "Invalid command. Try again." << endl;
        }
    }
    return 0;
}
