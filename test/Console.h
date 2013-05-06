#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include "Prerequisites.h"
#include "adams_macros.h"

void CenterConsole();
void CenteredConsoleOutput(char* s, unsigned int consoleWidthInChars = 80);
void CenteredConsoleOutputEndl(char* s, unsigned int consoleWidthInChars = 80);
inline void hr() { Eighty(say "=") endline }

#endif