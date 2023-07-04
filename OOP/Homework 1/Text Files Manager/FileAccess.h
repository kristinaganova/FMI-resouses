#pragma once
#include "constants.h"
#include <iostream>
#include "FileAccess.h"
#include "helpers.h"

class FileAccess {
private:
    char permissions[ACCES_RIGHTS_LEN + 1];
    char role;

public:
    FileAccess();

    FileAccess(const char* permissions);

    bool canRead(char role) const;

    bool canWrite(char role) const;

    bool canExecute(char role) const;

    void printRights(const FileAccess& fa, char role);
};

