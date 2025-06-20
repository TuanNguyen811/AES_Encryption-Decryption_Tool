#ifndef SUCCESSDIALOG_H
#define SUCCESSDIALOG_H

#include <QDialog>

namespace Ui {
class SuccessDialog;
}

class SuccessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SuccessDialog(QWidget *parent = nullptr);
    ~SuccessDialog();
    void setMessage(const QString& message);

private slots:
    void on_pushButtonClose_clicked(); // Đảm bảo khớp với successdialog.ui

private:
    Ui::SuccessDialog *successUi;
};

#endif // SUCCESSDIALOG_H
