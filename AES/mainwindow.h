#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QThread>
#include <QButtonGroup>
#include <QTimer>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QUrl>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QDialog>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <filesystem>
#include <chrono>

// Include các header từ dự án AES
#include "aes.h"
#include "hash.h"
#include "hmac.h"
#include "compressor.h"
#include "readFile.h"
#include "writeFile.h"
#include "encryptionFormat.h"
#include "decryptionFormat.h"

// Forward declaration để tránh circular dependency
class SuccessDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace fs = std::filesystem;
using namespace std::chrono;

// Cấu trúc PerformanceMetrics (từ file gốc)
struct PerformanceMetrics {
    long long compression_time = 0;
    long long read_time = 0;
    long long hash_time = 0;
    long long format_time = 0;
    long long encrypt_decrypt_time = 0;
    long long write_time = 0;
    long long decompress_time = 0;
    long long total_time = 0;
    double read_speed = 0.0;
    double encrypt_decrypt_speed = 0.0;
    double write_speed = 0.0;
    size_t file_size = 0;
};

// Cấu trúc ProcessMetrics (giống file tham khảo)
struct ProcessMetrics {
    long long compress_ms = 0;
    long long read_ms = 0;
    long long hash_ms = 0;
    long long format_ms = 0;
    long long encrypt_ms = 0;
    long long write_ms = 0;
    long long decompress_ms = 0;
    long long total_ms = 0;
    double read_mbps = 0.0;
    double encrypt_mbps = 0.0;
    double write_mbps = 0.0;
};

// Worker class cho encryption
class EncryptWorker : public QObject
{
    Q_OBJECT

public:
    EncryptWorker(const QString& inputPath, const QString& outputPath,
                  const QString& password, AES::Mode mode);

public slots:
    void process();

signals:
    void finished(const ProcessMetrics& metrics);
    void error(QString err);
    void progressUpdate(int percentage, QString status);

private:
    QString m_inputPath;
    QString m_outputPath;
    QString m_password;
    AES::Mode m_mode;
};

// Worker class cho decryption
class DecryptWorker : public QObject
{
    Q_OBJECT

public:
    DecryptWorker(const QString& inputPath, const QString& outputPath,
                  const QString& password);

public slots:
    void process();

signals:
    void finished(const ProcessMetrics& metrics);
    void error(QString err);
    void progressUpdate(int percentage, QString status);

private:
    QString m_inputPath;
    QString m_outputPath;
    QString m_password;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void setInputPath(const QString& path);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // File selection
    void on_pushButton_selectFolder_clicked();
    void on_pushButton_3_clicked();

    // Main actions
    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();

    // Password visibility
    void on_pushButton_5_clicked(); // Encrypt tab
    void on_pushButton_6_clicked(); // Decrypt tab

    // Tab switching
    void on_tabWidget_currentChanged(int index);
    void on_lineEdit_file_textChanged(const QString &text);

    // Worker signals
    void onEncryptFinished(const ProcessMetrics& metrics);
    void onDecryptFinished(const ProcessMetrics& metrics);
    void onProcessError(const QString& error);
    void onProgressUpdate(int percentage, const QString& status);

private:
    Ui::MainWindow *ui;
    QButtonGroup *m_keySizeButtonGroup;
    QProgressDialog *m_progressDialog;
    QThread *m_workerThread;

    // Methods
    void setupUI();
    void setupEncryptionModes();
    bool validateEncryptInputs();
    bool validateDecryptInputs();
    void showError(const QString& message);
    void showSuccess(const QString& message);
    QString formatFileSize(qint64 bytes);
    AES::Mode getSelectedMode();

    void showSuccessDialog(const QString& message, const ProcessMetrics& metrics);

    // Decrypt info methods
    bool readAesFileInfo(const QString& filePath, int& keysize, QString& mode);
    QString getModeString(int modeCode);
    void updateDecryptionInfo(const QString& filePath);
};

#endif // MAINWINDOW_H
