#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>

class AnimatedBackground;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveHistory(const QString &action, int appointmentId, const QString &details);


private slots:
    void addAppointment();
    void updateAppointment();
    void deleteAppointment();
    void loadAppointmentsFromDatabase();   // ✅ only this remains


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;  // make db a member variable
    AnimatedBackground *animatedBg;
    QWidget *glassOverlay = nullptr;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H



