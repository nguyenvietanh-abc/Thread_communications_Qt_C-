#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include "core/Book.h"

class Console
{
public:
    static std::string readLine();
    static void printBook(const Book& book);
    static void printHeader(const QString& text);
    static void printError(const QString& msg);
    static void clearLine();
};

#endif // CONSOLE_H
