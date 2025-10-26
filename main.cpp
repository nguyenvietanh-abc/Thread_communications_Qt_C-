#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <iostream>
#include "core/Library.h"
#include "thread/Worker.h"
#include "utils/Console.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qDebug() << "Starting library application...";

    Library library;
    qDebug() << "Library initialized";

    QThread workerThread;
    Worker worker(&library);
    qDebug() << "Worker created";

    worker.moveToThread(&workerThread);
    qDebug() << "Worker moved to thread";

    // Kết nối signal
    QObject::connect(&worker, &Worker::searchCompleted, [](const QVector<Book>& results, const QString& kw) {
        qDebug() << "Search completed for keyword:" << kw;
        Console::printHeader("Kết quả tìm kiếm: \"" + kw + "\"");
        if (results.isEmpty()) {
            std::cout << "Không tìm thấy sách.\n";
        } else {
            for (const auto& b : results) Console::printBook(b);
        }
    });
    qDebug() << "Connected searchCompleted signal";

    QObject::connect(&worker, &Worker::sortedListReady, [](const QVector<Book>& books) {
        qDebug() << "Sorted list ready";
        Console::printHeader("Danh sách đã sắp xếp (QuickSort)");
        for (const auto& b : books) Console::printBook(b);
    });
    qDebug() << "Connected sortedListReady signal";

    QObject::connect(&worker, &Worker::reportGenerated, [](int total, int avail) {
        qDebug() << "Report generated: total =" << total << ", available =" << avail;
        std::cout << "Báo cáo: Tổng: " << total << " | Có sẵn: " << avail << "\n";
    });
    qDebug() << "Connected reportGenerated signal";

    QObject::connect(&worker, &Worker::progressUpdate, [](int p) {
        qDebug() << "Progress update:" << p;
        Console::clearLine();
        std::cout << "Tiến trình: " << p << "%" << std::flush;
    });
    qDebug() << "Connected progressUpdate signal";

    QObject::connect(&worker, &Worker::taskFinished, [&workerThread]() {
        qDebug() << "Task finished, quitting thread";
        workerThread.quit();
    });
    qDebug() << "Connected taskFinished signal";

    QObject::connect(&workerThread, &QThread::finished, &workerThread, &QObject::deleteLater);
    qDebug() << "Connected thread finished signal";

    // Dữ liệu mẫu
    library.addBook(Book("978-0-13-110362-7", "The C Programming Language", "Kernighan & Ritchie", 1978));
    library.addBook(Book("978-0-321-56384-2", "Effective Modern C++", "Scott Meyers", 2014));
    library.addBook(Book("978-0-596-00782-9", "Head First Design Patterns", "Eric Freeman", 2004, false));
    library.addBook(Book("978-1-491-90163-2", "Clean Code", "Robert C. Martin", 2008));
    qDebug() << "Sample data added";

    // Menu
    Console::printHeader("QUẢN LÝ THƯ VIỆN SÁCH - OOP + THREAD + ALGO");
    qDebug() << "Printed header";
    std::cout << "Lệnh: add, list, search <kw>, borrow <isbn>, return <isbn>, report, sort, quit\n> ";
    qDebug() << "Printed menu prompt";

    QString line;
    while ((line = QString::fromStdString(Console::readLine()).trimmed()) != "quit") {
        QStringList parts = line.split(' ', Qt::SkipEmptyParts);
        if (parts.isEmpty()) continue;

        if (parts[0] == "add" && parts.size() >= 5) {
            Book b(parts[1], parts[2] + " " + parts[3], parts[4], parts.size() > 5 ? parts[5].toInt() : 2020);
            if (library.addBook(b)) {
                std::cout << "Đã thêm sách.\n";
            } else {
                Console::printError("ISBN đã tồn tại!");
            }
        }
        else if (parts[0] == "search" && parts.size() > 1) {
            QString kw = parts.mid(1).join(" ");
            qDebug() << "Starting search for:" << kw;
            QMetaObject::invokeMethod(&worker, "performSearch", Qt::QueuedConnection, Q_ARG(QString, kw));
            workerThread.start();
        }
        else if (parts[0] == "borrow" && parts.size() > 1) {
            if (library.borrowBook(parts[1])) {
                std::cout << "Mượn thành công.\n";
            } else {
                Console::printError("Không thể mượn.");
            }
        }
        else if (parts[0] == "return" && parts.size() > 1) {
            if (library.returnBook(parts[1])) {
                std::cout << "Trả thành công.\n";
            } else {
                Console::printError("Không thể trả.");
            }
        }
        else if (parts[0] == "list") {
            auto list = library.getAllBooksSortedByTitle();
            Console::printHeader("Tất cả sách");
            for (const auto& b : list) Console::printBook(b);
        }
        else if (parts[0] == "report") {
            qDebug() << "Starting report generation";
            QMetaObject::invokeMethod(&worker, "generateReportAndSort", Qt::QueuedConnection);
            workerThread.start();
        }
        else if (parts[0] == "sort") {
            auto sorted = library.getAllBooksSortedByTitle();
            Console::printHeader("Sắp xếp theo tiêu đề");
            for (const auto& b : sorted) Console::printBook(b);
        }
        else {
            Console::printError("Lệnh không hợp lệ.");
        }

        std::cout << "> ";
    }

    workerThread.quit();
    workerThread.wait();
    qDebug() << "Application exiting";
    return 0;
}
