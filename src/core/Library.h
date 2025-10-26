#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "Book.h"

class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject* parent = nullptr);

    bool addBook(const Book& book);
    bool borrowBook(const QString& isbn);
    bool returnBook(const QString& isbn);
    QVector<Book> searchByTitle(const QString& keyword) const;
    QVector<Book> searchByAuthor(const QString& keyword) const;
    QVector<Book> getAllBooksSortedByTitle() const;

signals:
    void bookAdded(const Book& book);
    void bookBorrowed(const QString& isbn);
    void bookReturned(const QString& isbn);
    void dataChanged();

private:
    void quickSort(QVector<Book>& books, int low, int high) const;
    int partition(QVector<Book>& books, int low, int high) const;
    Book findBookByTitleBinary(const QString& title, const QVector<Book>& sortedBooks) const;

    QMap<QString, Book> m_books;
};

#endif // LIBRARY_H
