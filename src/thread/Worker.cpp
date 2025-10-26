#include "Worker.h"
#include <QThread>

Worker::Worker(Library* library, QObject* parent) : QObject(parent), m_library(library)
{
}

void Worker::performSearch(const QString& keyword)
{
    QThread::msleep(200);
    emit progressUpdate(30);

    auto results = m_library->searchByTitle(keyword);
    QThread::msleep(300);
    emit progressUpdate(80);

    emit searchCompleted(results, keyword);
    emit progressUpdate(100);
    emit taskFinished();
}

void Worker::generateReportAndSort()
{
    QThread::msleep(200);
    emit progressUpdate(30);

    int total = m_library->getAllBooksSortedByTitle().size();
    int available = 0;
    for (const auto& book : m_library->getAllBooksSortedByTitle()) {
        if (book.isAvailable()) available++;
    }

    QThread::msleep(300);
    emit progressUpdate(80);

    auto sortedBooks = m_library->getAllBooksSortedByTitle();
    emit reportGenerated(total, available);
    emit sortedListReady(sortedBooks);
    emit progressUpdate(100);
    emit taskFinished();
}
