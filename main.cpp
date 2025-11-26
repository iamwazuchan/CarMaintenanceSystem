#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

#include "SignupWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // -------------------
    // Open SQLite database
    // -------------------
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("car_maintenance.db");   // your main DB file

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Failed to open database:\n" + db.lastError().text());
        return -1;
    }

    qDebug() << "Database opened successfully.";

    // -----------------------------------------
    // Create USERS table if it doesn't exist yet
    // -----------------------------------------
    QSqlQuery createUsers;

    if (!createUsers.exec(
            "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE NOT NULL, "
            "password TEXT NOT NULL)"
            )) {
        QMessageBox::critical(nullptr, "Error",
                              "Failed to create users table:\n" + createUsers.lastError().text());
        return -1;
    }

    qDebug() << "Users table verified.";

    // -------------------
    // Show SignupWindow
    // -------------------
    SignupWindow signup;
    signup.show();

    return a.exec();
}
