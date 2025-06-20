#include "successdialog.h"
#include "ui_successdialog.h"
#include <QDebug>

SuccessDialog::SuccessDialog(QWidget *parent) :
    QDialog(parent),
    successUi(new Ui::SuccessDialog)
{
    successUi->setupUi(this);
    setWindowTitle("Thành công");
    qDebug() << "SuccessDialog initialized, labelMessage exists:" << (successUi->labelMessage != nullptr);
}

SuccessDialog::~SuccessDialog()
{
    delete successUi;
}

void SuccessDialog::setMessage(const QString& message)
{
    qDebug() << "Setting message:" << message;
    if (successUi && successUi->labelMessage) {
        successUi->labelMessage->setText(message);
        qDebug() << "Message set successfully to labelMessage";
    } else {
        qDebug() << "Error: labelMessage is null or successUi is invalid";
    }
}

void SuccessDialog::on_pushButtonClose_clicked()
{
    close();
}
