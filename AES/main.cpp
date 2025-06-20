#include "mainwindow.h"
#include <QStyleFactory>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set application properties
    a.setApplicationName("AES File Encryption Tool");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("Your Company");

    QFile qssFile(":/resources/styles/macos.qss");  // đường dẫn đúng theo qrc
    if (qssFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = qssFile.readAll();
        a.setStyleSheet(styleSheet);
        qDebug() << "Loaded macOS QSS from local file";
    }

    // Set application icon if available
    a.setWindowIcon(QIcon(":/resources/icons/icon.ico"));

    // Dùng style Fusion (đồng nhất giữa các OS)
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    // Tạo giao diện sáng
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, QColor(245, 245, 245));
    lightPalette.setColor(QPalette::AlternateBase, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Highlight, QColor(76, 163, 224));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    a.setPalette(lightPalette);

    QString inputPath;
    // Nhận đường dẫn từ dòng lệnh nếu có (bỏ argv[0])
    if (argc >= 2) {
        inputPath = QString::fromLocal8Bit(argv[1]);

        // Debug: In ra đường dẫn nhận được
        qDebug() << "Raw input path from argv[1]:" << inputPath;

        // Loại bỏ dấu ngoặc kép nếu có
        if (inputPath.startsWith('"') && inputPath.endsWith('"')) {
            inputPath = inputPath.mid(1, inputPath.length() - 2);
            qDebug() << "Removed quotes, new path:" << inputPath;
        }

        // Kiểm tra đường dẫn có tồn tại không
        QFileInfo fileInfo(inputPath);
        if (!fileInfo.exists()) {
            qDebug() << "Path does not exist:" << inputPath;
            qDebug() << "Absolute path:" << fileInfo.absoluteFilePath();
            qDebug() << "Is file:" << fileInfo.isFile();
            qDebug() << "Is dir:" << fileInfo.isDir();
        } else {
            qDebug() << "Path exists and valid:" << inputPath;
            qDebug() << "Is file:" << fileInfo.isFile();
            qDebug() << "Is dir:" << fileInfo.isDir();
        }
    }

    MainWindow w;
    if (!inputPath.isEmpty()) {
        w.setInputPath(inputPath);
    }

    w.show();

    return a.exec();
}
