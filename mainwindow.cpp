#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "successdialog.h"
#include <iostream>
#include <filesystem>
#include <QWidget>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>

namespace fs = std::filesystem;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_progressDialog(nullptr)
    , m_workerThread(nullptr)
{
    ui->setupUi(this);
    setupUI();
    setupEncryptionModes();
}

MainWindow::~MainWindow()
{
    if (m_workerThread && m_workerThread->isRunning()) {
        m_workerThread->quit();
        m_workerThread->wait(2000);
    }
    delete m_progressDialog;
    delete m_workerThread;
    delete ui;
}

void MainWindow::setInputPath(const QString& path)
{
    qDebug() << "MainWindow::setInputPath called with:" << path;

    QFileInfo fileInfo(path);

    qDebug() << "File exists:" << fileInfo.exists();
    qDebug() << "Is file:" << fileInfo.isFile();
    qDebug() << "Is dir:" << fileInfo.isDir();
    qDebug() << "Absolute path:" << fileInfo.absoluteFilePath();
    qDebug() << "Suffix:" << fileInfo.suffix().toLower();

    if (!fileInfo.exists()) {
        showError("The specified file or folder does not exist:\n" + path);
        return;
    }

    if (fileInfo.suffix().toLower() == "aes") {
        ui->tabWidget->setCurrentIndex(1);
        ui->lineEdit_file->setText(path);
        updateDecryptionInfo(path);
        QString outputPath = fileInfo.absolutePath();
        ui->lineEdit_encrypted_path_output->setText(outputPath);
        ui->lineEdit_password_decrypt->clear();
    } else {
        ui->tabWidget->setCurrentIndex(0);
        ui->lineEdit_file->setText(path);

        QString outputPath;
        if (fileInfo.isDir()) {
            outputPath = fileInfo.absoluteFilePath() + ".aes";
        } else {
            outputPath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + ".aes";
        }
        ui->lineEdit_encrypted_path_output->setText(outputPath);
        ui->lineEdit_password_encrypt->clear();
        ui->lineEdit_verify->clear();
    }

    qDebug() << "setInputPath completed successfully";
}

void MainWindow::setupUI()
{
    statusBar()->hide();
    this->setFixedSize(451, 374);
    setWindowTitle("AES File Encryption Tool");
    ui->pushButton_5->setIcon(QIcon(":/resources/icons/eye0.png"));
    ui->pushButton_6->setIcon(QIcon(":/resources/icons/eye0.png"));

    m_keySizeButtonGroup = new QButtonGroup(this);
    m_keySizeButtonGroup->addButton(ui->radioButton_128bit, 128);
    m_keySizeButtonGroup->addButton(ui->radioButton_192bit, 192);
    m_keySizeButtonGroup->addButton(ui->radioButton_256bit, 256);

    ui->radioButton_256bit->setChecked(true);
    ui->tabWidget->setCurrentIndex(0);

    ui->lineEdit_file->setPlaceholderText("Select file or folder...");
    ui->lineEdit_encrypted_path_output->setPlaceholderText("Output location...");
    ui->lineEdit_password_encrypt->setPlaceholderText("Enter password...");
    ui->lineEdit_verify->setPlaceholderText("Re-enter password...");
    ui->lineEdit_password_decrypt->setPlaceholderText("Enter password...");

    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());
}

void MainWindow::setupEncryptionModes()
{
    ui->comboBox_encryMode->addItem("ECB", static_cast<int>(AES::Mode::ECB));
    ui->comboBox_encryMode->addItem("CBC", static_cast<int>(AES::Mode::CBC));
    ui->comboBox_encryMode->addItem("CFB", static_cast<int>(AES::Mode::CFB));
    ui->comboBox_encryMode->addItem("OFB", static_cast<int>(AES::Mode::OFB));
    ui->comboBox_encryMode->setCurrentIndex(1);
}

bool MainWindow::readAesFileInfo(const QString& filePath, int& keysize, QString& mode)
{
    try {
        std::vector<uint8_t> buffer = readFileAsBytes(fs::path(filePath.toStdString()));
        if (buffer.size() < 64) {
            return false;
        }

        size_t offset = 32; // Skip HMAC

        if (offset < buffer.size()) {
            uint8_t modeCode = buffer[offset];
            mode = getModeString(modeCode);
            offset++;
        }

        if (offset < buffer.size()) {
            uint8_t keyLen = buffer[offset];
            keysize = keyLen * 8;
        }

        return true;
    } catch (const std::exception& e) {
        std::cout << "Error reading AES file info: " << e.what() << std::endl;
        return false;
    }
}

QString MainWindow::getModeString(int modeCode)
{
    switch(modeCode) {
    case 0: return "ECB";
    case 1: return "CBC";
    case 2: return "CFB";
    case 3: return "OFB";
    default: return "Unknown";
    }
}

void MainWindow::updateDecryptionInfo(const QString& filePath)
{
    int keysize;
    QString mode;

    if (readAesFileInfo(filePath, keysize, mode)) {
        qDebug() << "AES file info - Key Size:" << keysize << "bits, Mode:" << mode;
    } else {
        qDebug() << "Unable to detect AES file info";
    }
}

void MainWindow::on_lineEdit_file_textChanged(const QString &text)
{
    if (ui->tabWidget->currentIndex() == 1 && !text.isEmpty()) {
        updateDecryptionInfo(text);
    }
}

void MainWindow::on_pushButton_selectFolder_clicked()
{
    QString path;

    if (ui->tabWidget->currentIndex() == 0) {
        path = QFileDialog::getExistingDirectory(this,
                                                 "Select Folder to Encrypt",
                                                 QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
        if (path.isEmpty()) {
            path = QFileDialog::getOpenFileName(this,
                                                "Select File to Encrypt",
                                                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                                "All Files (*)");
        }
    } else {
        path = QFileDialog::getOpenFileName(this,
                                            "Select Encrypted File",
                                            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
                                            "AES Files (*.aes);;All Files (*)");
    }

    if (!path.isEmpty()) {
        ui->lineEdit_file->setText(path);

        QFileInfo fileInfo(path);
        QString outputPath;

        if (ui->tabWidget->currentIndex() == 0) {
            if (fileInfo.isDir()) {
                outputPath = fileInfo.absoluteFilePath() + ".aes";
            } else {
                outputPath = fileInfo.absolutePath() + "/" + fileInfo.baseName() + ".aes";
            }
        } else {
            outputPath = fileInfo.absolutePath();
            updateDecryptionInfo(path);
        }

        ui->lineEdit_encrypted_path_output->setText(outputPath);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString path;

    if (ui->tabWidget->currentIndex() == 0) {
        path = QFileDialog::getSaveFileName(this,
                                            "Save Encrypted File As",
                                            ui->lineEdit_encrypted_path_output->text(),
                                            "AES Files (*.aes)");
    } else {
        path = QFileDialog::getExistingDirectory(this,
                                                 "Select Output Directory",
                                                 ui->lineEdit_encrypted_path_output->text());
    }

    if (!path.isEmpty()) {
        ui->lineEdit_encrypted_path_output->setText(path);
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->lineEdit_file->clear();
    ui->lineEdit_encrypted_path_output->clear();

    if (index == 0) {
        ui->pushButton_save->setText("Encrypt");
        ui->groupBox_3->setTitle("File Selection");
    } else {
        ui->pushButton_save->setText("Decrypt");
        ui->groupBox_3->setTitle("File Selection");
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    QString outputPath = ui->lineEdit_encrypted_path_output->text();

    if (ui->tabWidget->currentIndex() == 0) {
        if (!validateEncryptInputs()) {
            return;
        }

        QString inputPath = ui->lineEdit_file->text();
        QString password = ui->lineEdit_password_encrypt->text();
        AES::Mode mode = getSelectedMode();

        m_progressDialog = new QProgressDialog("Encrypting...", "Cancel", 0, 100, this);
        m_progressDialog->setWindowModality(Qt::WindowModal);
        m_progressDialog->setAutoClose(false);
        m_progressDialog->setAutoReset(false);

        m_workerThread = new QThread;
        EncryptWorker *worker = new EncryptWorker(inputPath, outputPath, password, mode);
        worker->moveToThread(m_workerThread);

        connect(m_workerThread, &QThread::started, worker, &EncryptWorker::process);
        connect(worker, &EncryptWorker::finished, this, &MainWindow::onEncryptFinished);
        connect(worker, &EncryptWorker::error, this, &MainWindow::onProcessError);
        connect(worker, &EncryptWorker::progressUpdate, this, &MainWindow::onProgressUpdate);
        connect(worker, &EncryptWorker::finished, worker, &QObject::deleteLater);
        connect(worker, &EncryptWorker::finished, m_workerThread, &QThread::quit);
        connect(m_workerThread, &QThread::finished, m_workerThread, &QObject::deleteLater);

        connect(m_progressDialog, &QProgressDialog::canceled, [this]() {
            if (m_workerThread && m_workerThread->isRunning()) {
                m_workerThread->quit();
                if (!m_workerThread->wait(1000)) {
                    m_workerThread->terminate();
                    m_workerThread->wait();
                }
            }
        });

        m_workerThread->start();
        m_progressDialog->show();

    } else {
        if (!validateDecryptInputs()) {
            return;
        }

        QString inputPath = ui->lineEdit_file->text();
        QString password = ui->lineEdit_password_decrypt->text();

        m_progressDialog = new QProgressDialog("Decrypting...", "Cancel", 0, 100, this);
        m_progressDialog->setWindowModality(Qt::WindowModal);
        m_progressDialog->setAutoClose(false);
        m_progressDialog->setAutoReset(false);

        m_workerThread = new QThread;
        DecryptWorker *worker = new DecryptWorker(inputPath, outputPath, password);
        worker->moveToThread(m_workerThread);

        connect(m_workerThread, &QThread::started, worker, &DecryptWorker::process);
        connect(worker, &DecryptWorker::finished, this, &MainWindow::onDecryptFinished);
        connect(worker, &DecryptWorker::error, this, &MainWindow::onProcessError);
        connect(worker, &DecryptWorker::progressUpdate, this, &MainWindow::onProgressUpdate);
        connect(worker, &DecryptWorker::finished, worker, &QObject::deleteLater);
        connect(worker, &DecryptWorker::finished, m_workerThread, &QThread::quit);
        connect(m_workerThread, &QThread::finished, m_workerThread, &QObject::deleteLater);

        connect(m_progressDialog, &QProgressDialog::canceled, [this]() {
            if (m_workerThread && m_workerThread->isRunning()) {
                m_workerThread->quit();
                if (!m_workerThread->wait(1000)) {
                    m_workerThread->terminate();
                    m_workerThread->wait();
                }
            }
        });

        m_workerThread->start();
        m_progressDialog->show();
    }
}

void MainWindow::on_pushButton_cancel_clicked()
{
    close();
}

void MainWindow::on_pushButton_5_clicked()
{
    bool isHidden = ui->lineEdit_password_encrypt->echoMode() == QLineEdit::Password;

    ui->lineEdit_password_encrypt->setEchoMode(isHidden ? QLineEdit::Normal : QLineEdit::Password);
    ui->lineEdit_verify->setEchoMode(isHidden ? QLineEdit::Normal : QLineEdit::Password);

    QIcon icon(isHidden ? ":/resources/icons/eye1.png" : ":/resources/icons/eye0.png");
    ui->pushButton_5->setIcon(icon);
}

void MainWindow::on_pushButton_6_clicked()
{
    bool isHidden = ui->lineEdit_password_decrypt->echoMode() == QLineEdit::Password;

    ui->lineEdit_password_decrypt->setEchoMode(isHidden ? QLineEdit::Normal : QLineEdit::Password);

    QIcon icon(isHidden ? ":/resources/icons/eye1.png" : ":/resources/icons/eye0.png");
    ui->pushButton_6->setIcon(icon);
}

bool MainWindow::validateEncryptInputs()
{
    if (ui->lineEdit_file->text().isEmpty()) {
        showError("Please select a file or folder to encrypt.");
        return false;
    }
    if (ui->lineEdit_encrypted_path_output->text().isEmpty()) {
        showError("Please specify an output location.");
        return false;
    }
    if (ui->lineEdit_password_encrypt->text().isEmpty()) {
        showError("Please enter a password.");
        return false;
    }
    if (ui->lineEdit_password_encrypt->text() != ui->lineEdit_verify->text()) {
        showError("Passwords do not match.");
        return false;
    }
    if (ui->lineEdit_password_encrypt->text().length() < 4) {
        showError("Password must be at least 4 characters long.");
        return false;
    }

    QString inputPath = ui->lineEdit_file->text();
    QFileInfo fileInfo(inputPath);

    if (!fileInfo.exists()) {
        showError("Selected file or folder does not exist:\n" + inputPath);
        return false;
    }

    qDebug() << "Validation passed for:" << inputPath;
    qDebug() << "Is file:" << fileInfo.isFile();
    qDebug() << "Is dir:" << fileInfo.isDir();

    return true;
}

bool MainWindow::validateDecryptInputs()
{
    if (ui->lineEdit_file->text().isEmpty()) {
        showError("Please select an encrypted file to decrypt.");
        return false;
    }
    if (ui->lineEdit_encrypted_path_output->text().isEmpty()) {
        showError("Please specify an output location.");
        return false;
    }
    if (ui->lineEdit_password_decrypt->text().isEmpty()) {
        showError("Please enter the password.");
        return false;
    }
    if (!QFile::exists(ui->lineEdit_file->text())) {
        showError("Selected file does not exist.");
        return false;
    }

    return true;
}

AES::Mode MainWindow::getSelectedMode()
{
    return static_cast<AES::Mode>(ui->comboBox_encryMode->currentData().toInt());
}

void MainWindow::onEncryptFinished(const ProcessMetrics& metrics)
{
    if (m_progressDialog) {
        m_progressDialog->close();
        delete m_progressDialog;
        m_progressDialog = nullptr;
    }

    QString outputPath = ui->lineEdit_encrypted_path_output->text();
    QString message = QString("Encryption completed successfully!\nOutput: %1\n\n===== Time and Speed =====\n")
                          .arg(outputPath.isEmpty() ? "Unknown location" : outputPath);
    message += QString("Compression: %1 ms\n").arg(metrics.compress_ms);
    message += QString("Read file: %1 ms (%2 MB/s)\n").arg(metrics.read_ms).arg(metrics.read_mbps, 0, 'f', 2);
    message += QString("Hash key: %1 ms\n").arg(metrics.hash_ms);
    message += QString("AES Encryption: %1 ms (%2 MB/s)\n").arg(metrics.encrypt_ms).arg(metrics.encrypt_mbps, 0, 'f', 2);
    message += QString("Build format: %1 ms\n").arg(metrics.format_ms);
    message += QString("Write file: %1 ms (%2 MB/s)\n").arg(metrics.write_ms).arg(metrics.write_mbps, 0, 'f', 2);
    message += QString("Total time: %1 ms").arg(metrics.total_ms);

    qDebug() << "Encryption success:" << message;
    if (metrics.total_ms > 0) {
        showSuccessDialog(message, metrics);
        // Reset input fields
        ui->lineEdit_file->clear();
        ui->lineEdit_encrypted_path_output->clear();
        ui->lineEdit_password_encrypt->clear();
        ui->lineEdit_verify->clear();
    } else {
        qDebug() << "Warning: Metrics total_ms is 0";
    }

    if (this->isVisible()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Open Output Folder",
                                                                  "Would you like to open the output folder?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QFileInfo fileInfo(outputPath);
            if (QDir(fileInfo.absolutePath()).exists()) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
            } else {
                QMessageBox::warning(this, "Warning", "Output directory does not exist!");
            }
        }
    }
}

void MainWindow::onDecryptFinished(const ProcessMetrics& metrics)
{
    if (m_progressDialog) {
        m_progressDialog->close();
        delete m_progressDialog;
        m_progressDialog = nullptr;
    }

    QString outputPath = ui->lineEdit_encrypted_path_output->text();
    QString message = QString("Decryption completed successfully!\nOutput: %1\n\n===== Time and Speed =====\n")
                          .arg(outputPath.isEmpty() ? "Unknown location" : outputPath);
    message += QString("Read encrypted file: %1 ms (%2 MB/s)\n").arg(metrics.read_ms).arg(metrics.read_mbps, 0, 'f', 2);
    message += QString("Hash key: %1 ms\n").arg(metrics.hash_ms);
    message += QString("Parse format: %1 ms\n").arg(metrics.format_ms);
    message += QString("AES Decryption: %1 ms (%2 MB/s)\n").arg(metrics.encrypt_ms).arg(metrics.encrypt_mbps, 0, 'f', 2);
    message += QString("Write compressed file: %1 ms (%2 MB/s)\n").arg(metrics.write_ms).arg(metrics.write_mbps, 0, 'f', 2);
    message += QString("Decompression: %1 ms\n").arg(metrics.decompress_ms);
    message += QString("Total time: %1 ms").arg(metrics.total_ms);

    qDebug() << "Decryption success:" << message;
    if (metrics.total_ms > 0) {
        showSuccessDialog(message, metrics);
        // Reset input fields
        ui->lineEdit_file->clear();
        ui->lineEdit_encrypted_path_output->clear();
        ui->lineEdit_password_decrypt->clear();
    } else {
        qDebug() << "Warning: Metrics total_ms is 0";
    }

    if (this->isVisible()) {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Open Output Folder",
                                                                  "Would you like to open the output folder?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QFileInfo fileInfo(outputPath);
            if (QDir(fileInfo.absolutePath()).exists()) {
                QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absolutePath()));
            } else {
                QMessageBox::warning(this, "Warning", "Output directory does not exist!");
            }
        }
    }
}

void MainWindow::showSuccessDialog(const QString& message, const ProcessMetrics&)
{
    qDebug() << "Showing SuccessDialog with message:" << message;
    if (this->isVisible()) {
        SuccessDialog dialog(this);
        dialog.setMessage(message);
        int result = dialog.exec();
        qDebug() << "Dialog closed with result:" << result;
    } else {
        qDebug() << "MainWindow is not visible, skipping SuccessDialog";
    }
}

void MainWindow::onProcessError(const QString& error)
{
    if (m_progressDialog) {
        m_progressDialog->close();
        delete m_progressDialog;
        m_progressDialog = nullptr;
    }

    qDebug() << "Process error:" << error;
    showError("Operation failed:\n" + error);
}

void MainWindow::onProgressUpdate(int percentage, const QString& status)
{
    if (m_progressDialog) {
        m_progressDialog->setValue(percentage);
        m_progressDialog->setLabelText(status);
        qDebug() << "Progress:" << percentage << "%" << status;
    }
}

void MainWindow::showError(const QString& message)
{
    qDebug() << "Error:" << message;
    if (this->isVisible()) {
        QMessageBox::critical(this, "Error", message);
    }
}

QString MainWindow::formatFileSize(qint64 bytes)
{
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;

    if (bytes >= GB) {
        return QString::number(bytes / GB, 'f', 2) + " GB";
    } else if (bytes >= MB) {
        return QString::number(bytes / MB, 'f', 2) + " MB";
    } else if (bytes >= KB) {
        return QString::number(bytes / KB, 'f', 2) + " KB";
    } else {
        return QString::number(bytes) + " bytes";
    }
}

// EncryptWorker Implementation
EncryptWorker::EncryptWorker(const QString& inputPath, const QString& outputPath,
                             const QString& password, AES::Mode mode)
    : m_inputPath(inputPath), m_outputPath(outputPath), m_password(password), m_mode(mode)
{
}

void EncryptWorker::process()
{
    try {
        ProcessMetrics metrics;
        auto total_start = high_resolution_clock::now();
        fs::path inputPath(m_inputPath.toStdString());
        fs::path outputPath(m_outputPath.toStdString());
        std::error_code ec;

        // Step 1: Compression
        emit progressUpdate(10, "Compressing data...");
        auto compress_start = high_resolution_clock::now();
        Compressor compressor(inputPath);
        if (!compressor.compress()) {
            emit error("Compression failed");
            return;
        }
        std::string zipFile = compressor.getOutputName();
        auto compress_end = high_resolution_clock::now();
        metrics.compress_ms = duration_cast<milliseconds>(compress_end - compress_start).count();

        // Step 2: Read compressed file
        emit progressUpdate(25, "Reading compressed file...");
        auto read_start = high_resolution_clock::now();
        fs::path inputZipFile = inputPath.parent_path() / zipFile;
        std::vector<uint8_t> buffer = readFileAsBytes(inputZipFile);
        if (buffer.empty()) {
            emit error("Failed to read compressed file or file is empty");
            return;
        }
        auto read_end = high_resolution_clock::now();
        metrics.read_ms = duration_cast<milliseconds>(read_end - read_start).count();
        metrics.read_mbps = (buffer.size() / (1024.0 * 1024.0)) /
                            (duration_cast<duration<double>>(read_end - read_start).count() ?: 1e-6);

        // Step 3: Hash key
        emit progressUpdate(40, "Hashing key...");
        auto hash_start = high_resolution_clock::now();
        SHA256 hash;
        std::string password_str = m_password.toStdString();
        std::vector<uint8_t> password_bytes(password_str.begin(), password_str.end());
        std::vector<uint8_t> key = hash.hash(password_bytes);
        auto hash_end = high_resolution_clock::now();
        metrics.hash_ms = duration_cast<milliseconds>(hash_end - hash_start).count();

        // Step 4: AES Encryption
        emit progressUpdate(60, "Encrypting with AES...");
        auto encrypt_start = high_resolution_clock::now();
        AES aes(key, m_mode);
        std::vector<uint8_t> iv;
        if (m_mode != AES::Mode::ECB) {
            iv = aes.generateRandomIV();
        }
        std::vector<uint8_t> ciphertext = aes.encrypt(buffer, iv);
        auto encrypt_end = high_resolution_clock::now();
        metrics.encrypt_ms = duration_cast<milliseconds>(encrypt_end - encrypt_start).count();
        metrics.encrypt_mbps = (buffer.size() / (1024.0 * 1024.0)) /
                               (duration_cast<duration<double>>(encrypt_end - encrypt_start).count() ?: 1e-6);

        // Step 5: Build encrypted format
        emit progressUpdate(80, "Building encrypted format...");
        auto format_start = high_resolution_clock::now();
        ciphertext = buildEncryptedFormat(ciphertext, key, iv, static_cast<uint8_t>(m_mode));
        auto format_end = high_resolution_clock::now();
        metrics.format_ms = duration_cast<milliseconds>(format_end - format_start).count();

        // Step 6: Write encrypted file
        emit progressUpdate(90, "Writing encrypted file...");
        auto write_start = high_resolution_clock::now();
        if (!writeFileAsBytes(outputPath, ciphertext)) {
            emit error("Failed to write encrypted file");
            return;
        }
        auto write_end = high_resolution_clock::now();
        metrics.write_ms = duration_cast<milliseconds>(write_end - write_start).count();
        metrics.write_mbps = (ciphertext.size() / (1024.0 * 1024.0)) /
                             (duration_cast<duration<double>>(write_end - write_start).count() ?: 1e-6);

        // Cleanup
        emit progressUpdate(95, "Cleaning up...");
        if (inputPath != outputPath) {
            fs::remove_all(inputPath, ec);
            if (ec) qDebug() << "Warning: Failed to remove input file:" << ec.message().c_str();
        }
        fs::remove_all(inputZipFile, ec);
        if (ec) qDebug() << "Warning: Failed to remove zip file:" << ec.message().c_str();

        metrics.total_ms = duration_cast<milliseconds>(high_resolution_clock::now() - total_start).count();
        qDebug() << "Encryption finished with total_ms:" << metrics.total_ms;
        emit progressUpdate(100, "Encryption completed successfully!");
        emit finished(metrics);
    } catch (const std::exception& e) {
        emit error("Encryption failed: " + QString::fromStdString(e.what()));
    } catch (...) {
        emit error("Unknown error during encryption");
    }
}

// DecryptWorker Implementation
DecryptWorker::DecryptWorker(const QString& inputPath, const QString& outputPath,
                             const QString& password)
    : m_inputPath(inputPath), m_outputPath(outputPath), m_password(password)
{
}

void DecryptWorker::process()
{
    try {
        ProcessMetrics metrics;
        auto total_start = high_resolution_clock::now();
        fs::path inputPath(m_inputPath.toStdString());
        fs::path outputPath(m_outputPath.toStdString());
        std::error_code ec;

        // Step 1: Read encrypted file
        emit progressUpdate(10, "Reading encrypted file...");
        auto read_start = high_resolution_clock::now();
        if (!fs::exists(inputPath)) {
            emit error("Encrypted file does not exist: " + QString::fromStdString(inputPath.string()));
            return;
        }
        auto file_size = fs::file_size(inputPath, ec);
        if (ec) {
            emit error("Cannot get encrypted file size: " + QString::fromStdString(ec.message()));
            return;
        }
        if (file_size == 0) {
            emit error("Encrypted file is empty.");
            return;
        }
        if (file_size > 1024ULL * 1024 * 1024) {
            emit error("Encrypted file is too large: " + QString::number(file_size) + " bytes.");
            return;
        }
        std::vector<uint8_t> buffer = readFileAsBytes(inputPath);
        if (buffer.empty()) {
            emit error("Failed to read encrypted file or file is empty.");
            return;
        }
        auto read_end = high_resolution_clock::now();
        metrics.read_ms = duration_cast<milliseconds>(read_end - read_start).count();
        metrics.read_mbps = (buffer.size() / (1024.0 * 1024.0)) /
                            (duration_cast<duration<double>>(read_end - read_start).count() ?: 1e-6);

        // Step 2: Hash key
        emit progressUpdate(25, "Hashing key...");
        auto hash_start = high_resolution_clock::now();
        std::string password_str = m_password.toStdString();
        std::vector<uint8_t> password_bytes(password_str.begin(), password_str.end());
        SHA256 sha256;
        std::vector<uint8_t> key = sha256.hash(password_bytes);
        auto hash_end = high_resolution_clock::now();
        metrics.hash_ms = duration_cast<milliseconds>(hash_end - hash_start).count();

        // Step 3: Parse encrypted format
        emit progressUpdate(40, "Parsing encrypted format...");
        DecryptionResult result;
        auto format_start = high_resolution_clock::now();
        try {
            result = parseEncryptedFormat(buffer, key);
        } catch (const std::exception& e) {
            emit error("Invalid file format or wrong password: " + QString::fromStdString(e.what()));
            return;
        }
        auto format_end = high_resolution_clock::now();
        metrics.format_ms = duration_cast<milliseconds>(format_end - format_start).count();

        // Step 4: AES Decryption
        emit progressUpdate(60, "Decrypting AES...");
        auto decrypt_start = high_resolution_clock::now();
        AES aes(key, static_cast<AES::Mode>(result.mode));
        std::vector<uint8_t> plaintext;
        try {
            plaintext = aes.decrypt(result.ciphertext, result.iv);
        } catch (const std::exception& e) {
            emit error("Decryption failed - wrong password or corrupted file: " + QString::fromStdString(e.what()));
            return;
        }
        auto decrypt_end = high_resolution_clock::now();
        metrics.encrypt_ms = duration_cast<milliseconds>(decrypt_end - decrypt_start).count();
        metrics.encrypt_mbps = (result.ciphertext.size() / (1024.0 * 1024.0)) /
                               (duration_cast<duration<double>>(decrypt_end - decrypt_start).count() ?: 1e-6);

        // Step 5: Write temporary 7z file
        emit progressUpdate(75, "Writing compressed file...");
        fs::path zipFile = inputPath;
        zipFile.replace_extension(".7z");
        auto write_start = high_resolution_clock::now();
        if (!writeFileAsBytes(zipFile, plaintext)) {
            emit error("Failed to write temporary (.7z) file");
            return;
        }
        auto write_end = high_resolution_clock::now();
        metrics.write_ms = duration_cast<milliseconds>(write_end - write_start).count();
        metrics.write_mbps = (plaintext.size() / (1024.0 * 1024.0)) /
                             (duration_cast<duration<double>>(write_end - write_start).count() ?: 1e-6);

        // Step 6: Decompress
        emit progressUpdate(85, "Decompressing...");
        auto decompress_start = high_resolution_clock::now();
        if (!Compressor::decompress(plaintext, zipFile, outputPath)) {
            emit error("Decompression failed");
            return;
        }
        auto decompress_end = high_resolution_clock::now();
        metrics.decompress_ms = duration_cast<milliseconds>(decompress_end - decompress_start).count();

        // Cleanup
        emit progressUpdate(95, "Cleaning up...");
        fs::remove_all(inputPath, ec);
        if (ec) qDebug() << "Warning: Failed to remove input file:" << ec.message().c_str();
        fs::remove_all(zipFile, ec);
        if (ec) qDebug() << "Warning: Failed to remove zip file:" << ec.message().c_str();

        metrics.total_ms = duration_cast<milliseconds>(high_resolution_clock::now() - total_start).count();
        qDebug() << "Decryption finished with total_ms:" << metrics.total_ms;
        emit progressUpdate(100, "Decryption completed successfully!");
        emit finished(metrics);
    } catch (const std::exception& e) {
        emit error("Decryption failed: " + QString::fromStdString(e.what()));
    } catch (...) {
        emit error("Unknown error during decryption");
    }
}

#include "mainwindow.moc"
