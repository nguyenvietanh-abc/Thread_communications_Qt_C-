#include "Book.h"

Book::Book(const QString& isbn, const QString& title, const QString& author, int year, bool available)
    : m_isbn(isbn), m_title(title), m_author(author), m_year(year), m_available(available)
{
}

QString Book::toString() const
{
    return QString("ISBN: %1 | Tiêu đề: %2 | Tác giả: %3 | Năm: %4 | Trạng thái: %5")
        .arg(m_isbn, m_title, m_author, QString::number(m_year), m_available ? "Có sẵn" : "Đã mượn");
}
