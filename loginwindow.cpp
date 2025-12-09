#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginwindow)
{
    ui->setupUi(this);

    // Connect login button
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginWindow::handleLogin);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::handleLogin()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter username and password.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database is not open!");
        return;
    }

    // Verify credentials
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Login query failed:\n" + query.lastError().text());
        return;
    }

    if (query.next()) {
        // Login successful
        QMessageBox::information(this, "Success", "Login successful!");

        MainWindow *mainWin = new MainWindow();
        mainWin->show();

        this->close();  // Close login window
    }
    else {
        QMessageBox::warning(this, "Error", "Invalid username or password!");
    }
}
