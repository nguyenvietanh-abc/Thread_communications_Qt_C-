#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include "core/Library.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(Library* library, QObject* parent = nullptr);

public slots:
    void performSearch(const QString& keyword);
    void generateReportAndSort();

signals:
    void searchCompleted(const QVector<Book>& results, const QString& keyword);
    void sortedListReady(const QVector<Book>& books);
    void reportGenerated(int totalBooks, int availableBooks);
    void progressUpdate(int progress);
    void taskFinished();

private:
    Library* m_library;
};

#endif // WORKER_H
