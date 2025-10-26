#include "Console.h"
#include <QDebug>
#include <iostream>

std::string Console::readLine()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void Console::printBook(const Book& book)
{
    std::cout << book.toString().toStdString() << "\n";
}

void Console::printHeader(const QString& text)
{
    qDebug() << "Printing header:" << text;
    std::cout << "\n=== " << text.toStdString() << " ===\n";
}

void Console::printError(const QString& msg)
{
    std::cout << "Lỗi: " << msg.toStdString() << "\n";
}

void Console::clearLine()
{
    std::cout << "\r" << std::string(80, ' ') << "\r";
}
