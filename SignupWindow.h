#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QMainWindow>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private slots:
    void handleSignup();          // <-- your signup function
    void on_btnlogin_clicked(); // <-- button to open login window

private:
    Ui::SignupWindow *ui;
};

#endif // SIGNUPWINDOW_H
