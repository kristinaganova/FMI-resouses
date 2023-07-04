#pragma once
#include "constants.h"
#include "Row.h"

struct Column {
	char name[MAX_VALUE_SIZE];
	Row rows[MAX_ROWS];
};