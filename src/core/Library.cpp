#include "Library.h"
#include <QDebug>

Library::Library(QObject* parent) : QObject(parent)
{
}

bool Library::addBook(const Book& book)
{
    if (m_books.contains(book.isbn())) {
        return false;
    }
    m_books[book.isbn()] = book;
    emit bookAdded(book);
    emit dataChanged();
    return true;
}

bool Library::borrowBook(const QString& isbn)
{
    if (!m_books.contains(isbn) || !m_books[isbn].isAvailable()) {
        return false;
    }
    m_books[isbn].setAvailable(false);
    emit bookBorrowed(isbn);
    emit dataChanged();
    return true;
}

bool Library::returnBook(const QString& isbn)
{
    if (!m_books.contains(isbn) || m_books[isbn].isAvailable()) {
        return false;
    }
    m_books[isbn].setAvailable(true);
    emit bookReturned(isbn);
    emit dataChanged();
    return true;
}

QVector<Book> Library::searchByTitle(const QString& keyword) const
{
    QVector<Book> results;
    for (const auto& book : m_books) {
        if (book.title().contains(keyword, Qt::CaseInsensitive)) {
            results.append(book);
        }
    }
    return results;
}

QVector<Book> Library::searchByAuthor(const QString& keyword) const
{
    QVector<Book> results;
    for (const auto& book : m_books) {
        if (book.author().contains(keyword, Qt::CaseInsensitive)) {
            results.append(book);
        }
    }
    return results;
}

QVector<Book> Library::getAllBooksSortedByTitle() const
{
    QVector<Book> list = m_books.values().toVector();
    const_cast<Library*>(this)->quickSort(list, 0, list.size() - 1);
    return list;
}

void Library::quickSort(QVector<Book>& books, int low, int high) const
{
    if (low < high) {
        int pi = partition(books, low, high);
        quickSort(books, low, pi - 1);
        quickSort(books, pi + 1, high);
    }
}

int Library::partition(QVector<Book>& books, int low, int high) const
{
    QString pivot = books[high].title();
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (books[j].title().compare(pivot, Qt::CaseInsensitive) <= 0) {
            i++;
            books.swapItemsAt(i, j);
        }
    }
    books.swapItemsAt(i + 1, high);
    return i + 1;
}

Book Library::findBookByTitleBinary(const QString& title, const QVector<Book>& sortedBooks) const
{
    int left = 0, right = sortedBooks.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = sortedBooks[mid].title().compare(title, Qt::CaseInsensitive);
        if (cmp == 0) return sortedBooks[mid];
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return Book();
}
