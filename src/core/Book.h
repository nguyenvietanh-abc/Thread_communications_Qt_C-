#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    Book() = default;
    Book(const QString& isbn, const QString& title, const QString& author, int year, bool available = true);

    QString isbn() const { return m_isbn; }
    QString title() const { return m_title; }
    QString author() const { return m_author; }
    int year() const { return m_year; }
    bool isAvailable() const { return m_available; }

    void setAvailable(bool available) { m_available = available; }
    QString toString() const;

private:
    QString m_isbn;
    QString m_title;
    QString m_author;
    int m_year = 0;
    bool m_available = true;
};

#endif // BOOK_H
