#pragma once
const int MAX_COLS = 10;
const int MAX_ROWS = 50;
const int MAX_VALUE_SIZE = 20;
const int MAX_BUFFER_SIZE = 70;
const int MAX_COMMAND_LEN = 10;

const char OPEN_FILE_ERROR_MESSAGE[] = "Error opening the file";
const char SAVE_TO_FILE_MESSAGE[] = "Table saved to file";
const char ERROR_SAVE_TO_FILE_MESSAGE[] = "Table did not save to file";
const char SUCCESSFUL_OPERATION_MESSAGE[] = "Operation successfully executed!";
const char UNSUCCESSFUL_OPERATION_MESSAGE[] = "Operation didn't execute successfully!";
const char ERROR_MATCHING_ROWS[] = "No matching rows found.";
const char ERROR_COLUMN_FOUND[] = "Column not found.";
const char ERROR_MAXIMUM_COLUMNS[] = "Error: Maximum number of columns exceeded";
const char ERROR_MAXIMUM_ROWS[] = "Error: Maximum number of rows exceeded";
const char ERROR_MINIMUM_ROWS[] = "Error: Too few columns in row ";

const char PRINT_COMMAND[] = "print";
const char CHANGE_ROW_COMMAND[] = "change row";
const char ADD_ROW_COMMAND[] = "add";
const char SELECT_WHERE_COMMAND[] = "select";
const char SAVE_TO_FILE[] = "save";
const char LOAD_FROM_FILE[] = "load";
const char QUIT_COMMAND[] = "quit";
