/********************************************************************************
** Form generated from reading UI file 'loginpageview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGEVIEW_H
#define UI_LOGINPAGEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginPageView
{
public:
    QGroupBox *groupBox;
    QPushButton *loginButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *unameLabel;
    QLineEdit *usernameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *pwdLabel;
    QLineEdit *passwordEdit;

    void setupUi(QDialog *LoginPageView)
    {
        if (LoginPageView->objectName().isEmpty())
            LoginPageView->setObjectName(QStringLiteral("LoginPageView"));
        LoginPageView->resize(530, 443);
        groupBox = new QGroupBox(LoginPageView);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(50, 160, 421, 261));
        loginButton = new QPushButton(groupBox);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(160, 210, 89, 25));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(80, 50, 261, 141));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        unameLabel = new QLabel(widget);
        unameLabel->setObjectName(QStringLiteral("unameLabel"));

        horizontalLayout->addWidget(unameLabel);

        usernameEdit = new QLineEdit(widget);
        usernameEdit->setObjectName(QStringLiteral("usernameEdit"));

        horizontalLayout->addWidget(usernameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pwdLabel = new QLabel(widget);
        pwdLabel->setObjectName(QStringLiteral("pwdLabel"));

        horizontalLayout_2->addWidget(pwdLabel);

        passwordEdit = new QLineEdit(widget);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));

        horizontalLayout_2->addWidget(passwordEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(LoginPageView);

        QMetaObject::connectSlotsByName(LoginPageView);
    } // setupUi

    void retranslateUi(QDialog *LoginPageView)
    {
        LoginPageView->setWindowTitle(QApplication::translate("LoginPageView", "Dialog", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LoginPageView", "Log-In", Q_NULLPTR));
        loginButton->setText(QApplication::translate("LoginPageView", "Login", Q_NULLPTR));
        unameLabel->setText(QApplication::translate("LoginPageView", "Username:", Q_NULLPTR));
        pwdLabel->setText(QApplication::translate("LoginPageView", "Password:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginPageView: public Ui_LoginPageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGEVIEW_H
