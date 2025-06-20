/********************************************************************************
** Form generated from reading UI file 'successdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUCCESSDIALOG_H
#define UI_SUCCESSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SuccessDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QLabel *labelMessage;
    QPushButton *pushButtonClose;

    void setupUi(QDialog *SuccessDialog)
    {
        if (SuccessDialog->objectName().isEmpty())
            SuccessDialog->setObjectName("SuccessDialog");
        SuccessDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(SuccessDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(SuccessDialog);
        labelTitle->setObjectName("labelTitle");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        labelMessage = new QLabel(SuccessDialog);
        labelMessage->setObjectName("labelMessage");
        labelMessage->setAlignment(Qt::AlignmentFlag::AlignLeft);
        labelMessage->setWordWrap(true);
        labelMessage->setTextInteractionFlags(Qt::TextSelectableByMouse);

        verticalLayout->addWidget(labelMessage);

        pushButtonClose = new QPushButton(SuccessDialog);
        pushButtonClose->setObjectName("pushButtonClose");

        verticalLayout->addWidget(pushButtonClose);


        retranslateUi(SuccessDialog);
        QObject::connect(pushButtonClose, &QPushButton::clicked, SuccessDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(SuccessDialog);
    } // setupUi

    void retranslateUi(QDialog *SuccessDialog)
    {
        SuccessDialog->setWindowTitle(QCoreApplication::translate("SuccessDialog", "Th\303\240nh c\303\264ng", nullptr));
        labelTitle->setText(QCoreApplication::translate("SuccessDialog", "Th\303\240nh c\303\264ng!", nullptr));
        labelMessage->setText(QString());
        pushButtonClose->setText(QCoreApplication::translate("SuccessDialog", "\304\220\303\263ng", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SuccessDialog: public Ui_SuccessDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUCCESSDIALOG_H
