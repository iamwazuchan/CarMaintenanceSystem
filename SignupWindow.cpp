#include "SignupWindow.h"
#include "ui_SignupWindow.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SignupWindow::SignupWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignupWindow)
{
    ui->setupUi(this);

    // Connect Sign Up button
    connect(ui->btnSignUp, &QPushButton::clicked, this, &SignupWindow::handleSignup);
    connect(ui->btnlogin, &QPushButton::clicked, this, &SignupWindow::on_btnlogin_clicked);
}


SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::on_btnlogin_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}


// -------------------------------------------------
// Main Signup Logic
// -------------------------------------------------
void SignupWindow::handleSignup()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text();
    QString confirmPassword = ui->lineEditConfirmPassword->text();

    // Validate inputs
    if(username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Warning", "All fields are required!");
        return;
    }

    if(password != confirmPassword) {
        QMessageBox::warning(this, "Warning", "Passwords do not match!");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) {
        QMessageBox::critical(this, "Error", "Database is not open!");
        return;
    }

    // Insert new user
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);

    if(!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to register user:\n" + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Account created successfully!");

    // Clear fields
    ui->lineEditUsername->clear();
    ui->lineEditPassword->clear();
    ui->lineEditConfirmPassword->clear();

    // Open LoginWindow
    LoginWindow *login = new LoginWindow();
    login->show();

    this->close();
}
