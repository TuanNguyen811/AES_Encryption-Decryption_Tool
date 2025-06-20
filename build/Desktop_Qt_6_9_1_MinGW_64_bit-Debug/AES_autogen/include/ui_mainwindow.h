/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_save;
    QPushButton *pushButton_cancel;
    QGroupBox *groupBox_3;
    QToolButton *toolButton_2;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *lineEdit_encrypted_path_output;
    QLineEdit *lineEdit_file;
    QPushButton *pushButton_3;
    QPushButton *pushButton_selectFolder;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLineEdit *lineEdit_verify;
    QLabel *label_4;
    QLabel *label_6;
    QLineEdit *lineEdit_password_encrypt;
    QRadioButton *radioButton_128bit;
    QRadioButton *radioButton_192bit;
    QRadioButton *radioButton_256bit;
    QComboBox *comboBox_encryMode;
    QLabel *label_11;
    QPushButton *pushButton_5;
    QWidget *tab_2;
    QLabel *label_7;
    QLineEdit *lineEdit_password_decrypt;
    QPushButton *pushButton_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QButtonGroup *buttonGroup_keySize;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(451, 418);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton_save = new QPushButton(centralwidget);
        pushButton_save->setObjectName("pushButton_save");
        pushButton_save->setGeometry(QRect(331, 340, 101, 25));
        QFont font;
        font.setPointSize(10);
        pushButton_save->setFont(font);
        pushButton_save->setMouseTracking(true);
        pushButton_save->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #007aff;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 6px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #006ae6;\n"
"}\n"
""));
        pushButton_cancel = new QPushButton(centralwidget);
        pushButton_cancel->setObjectName("pushButton_cancel");
        pushButton_cancel->setGeometry(QRect(212, 340, 101, 25));
        pushButton_cancel->setFont(font);
        pushButton_cancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    color: black;\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 6px;\n"
"    padding: 6px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #f2f2f2;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #e6e6e6;\n"
"}\n"
""));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(20, 10, 411, 107));
        groupBox_3->setFont(font);
        toolButton_2 = new QToolButton(groupBox_3);
        toolButton_2->setObjectName("toolButton_2");
        toolButton_2->setGeometry(QRect(180, 30, 23, 23));
        toolButton_2->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border: none;\n"
"    background: transparent;\n"
"}"));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
        toolButton_2->setIcon(icon);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 70, 51, 21));
        label_3->setFont(font);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 34, 21, 21));
        label_2->setFont(font);
        lineEdit_encrypted_path_output = new QLineEdit(groupBox_3);
        lineEdit_encrypted_path_output->setObjectName("lineEdit_encrypted_path_output");
        lineEdit_encrypted_path_output->setGeometry(QRect(70, 66, 304, 30));
        lineEdit_file = new QLineEdit(groupBox_3);
        lineEdit_file->setObjectName("lineEdit_file");
        lineEdit_file->setGeometry(QRect(70, 30, 304, 30));
        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(380, 68, 21, 25));
        pushButton_3->setStyleSheet(QString::fromUtf8(""));
        pushButton_3->setIcon(icon);
        pushButton_selectFolder = new QPushButton(groupBox_3);
        pushButton_selectFolder->setObjectName("pushButton_selectFolder");
        pushButton_selectFolder->setGeometry(QRect(380, 33, 21, 25));
        pushButton_selectFolder->setStyleSheet(QString::fromUtf8(""));
        pushButton_selectFolder->setIcon(icon);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 130, 411, 201));
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(2, 15, 78, 20));
        label->setFont(font);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineEdit_verify = new QLineEdit(tab);
        lineEdit_verify->setObjectName("lineEdit_verify");
        lineEdit_verify->setGeometry(QRect(87, 53, 282, 31));
        lineEdit_verify->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 6px;\n"
"    padding: 6px 8px;\n"
"    background-color: white;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #007aff; /* xanh d\306\260\306\241ng macOS */\n"
"}\n"
""));
        lineEdit_verify->setEchoMode(QLineEdit::EchoMode::Password);
        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(2, 55, 78, 20));
        label_4->setFont(font);
        label_4->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_4->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(2, 90, 78, 20));
        label_6->setFont(font);
        label_6->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_6->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineEdit_password_encrypt = new QLineEdit(tab);
        lineEdit_password_encrypt->setObjectName("lineEdit_password_encrypt");
        lineEdit_password_encrypt->setGeometry(QRect(87, 13, 282, 31));
        lineEdit_password_encrypt->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 6px;\n"
"    padding: 6px 8px;\n"
"    background-color: white;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #007aff; /* xanh d\306\260\306\241ng macOS */\n"
"}\n"
""));
        lineEdit_password_encrypt->setEchoMode(QLineEdit::EchoMode::Password);
        radioButton_128bit = new QRadioButton(tab);
        buttonGroup_keySize = new QButtonGroup(MainWindow);
        buttonGroup_keySize->setObjectName("buttonGroup_keySize");
        buttonGroup_keySize->addButton(radioButton_128bit);
        radioButton_128bit->setObjectName("radioButton_128bit");
        radioButton_128bit->setGeometry(QRect(90, 92, 61, 21));
        radioButton_192bit = new QRadioButton(tab);
        buttonGroup_keySize->addButton(radioButton_192bit);
        radioButton_192bit->setObjectName("radioButton_192bit");
        radioButton_192bit->setGeometry(QRect(160, 92, 61, 21));
        radioButton_256bit = new QRadioButton(tab);
        buttonGroup_keySize->addButton(radioButton_256bit);
        radioButton_256bit->setObjectName("radioButton_256bit");
        radioButton_256bit->setGeometry(QRect(230, 92, 61, 21));
        comboBox_encryMode = new QComboBox(tab);
        comboBox_encryMode->setObjectName("comboBox_encryMode");
        comboBox_encryMode->setGeometry(QRect(87, 126, 282, 24));
        label_11 = new QLabel(tab);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(2, 125, 78, 20));
        label_11->setFont(font);
        label_11->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_11->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        pushButton_5 = new QPushButton(tab);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(373, 17, 31, 25));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_7 = new QLabel(tab_2);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(0, 20, 78, 16));
        label_7->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineEdit_password_decrypt = new QLineEdit(tab_2);
        lineEdit_password_decrypt->setObjectName("lineEdit_password_decrypt");
        lineEdit_password_decrypt->setGeometry(QRect(18, 40, 344, 31));
        lineEdit_password_decrypt->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 6px;\n"
"    padding: 6px 8px;\n"
"    background-color: white;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #007aff; /* xanh d\306\260\306\241ng macOS */\n"
"}\n"
""));
        lineEdit_password_decrypt->setEchoMode(QLineEdit::EchoMode::Password);
        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setGeometry(QRect(370, 43, 31, 25));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 451, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Folder Selection", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Save AS:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "File:", nullptr));
        pushButton_3->setText(QString());
        pushButton_selectFolder->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Verify:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Key Size:", nullptr));
        radioButton_128bit->setText(QCoreApplication::translate("MainWindow", "128 bit", nullptr));
        radioButton_192bit->setText(QCoreApplication::translate("MainWindow", "192 bit", nullptr));
        radioButton_256bit->setText(QCoreApplication::translate("MainWindow", "256 bit", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Encry Mode:", nullptr));
        pushButton_5->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        pushButton_6->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
