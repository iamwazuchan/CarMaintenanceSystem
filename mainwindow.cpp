#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "animatedbackground.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include "smtp.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , animatedBg(nullptr)
{
    ui->setupUi(this);

    // ---------- Setup animated background ----------
    animatedBg = new AnimatedBackground(ui->centralwidget);
    animatedBg->lower(); // send behind all widgets
    animatedBg->resize(ui->centralwidget->size());
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(12);
    shadow->setOffset(0, 3);
    shadow->setColor(QColor(0, 0, 0, 50));

    ui->centralwidget->setStyleSheet(
        "background-color: rgba(255, 255, 255, 100); border-radius: 15px;"
        );
    ui->txtCarModel->setPlaceholderText("Ex. Toyota Vios");
    ui->txtCarModel->setFont(QFont("Segoe UI", 11));
    ui->txtCarModel->setStyleSheet(
        "QLineEdit {"
        "   background: #fdfdfd;"              // soft background
        "   border: 2px solid #dcdcdc;"        // subtle border
        "   border-radius: 12px;"              // rounded corners
        "   padding: 8px 12px;"                // space inside the input
        "   color: #333333;"                   // text color"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4CAF50;"        // highlight border on focus
        "   background: #ffffff;"              // optional focus background
        "}"
        "QLineEdit::placeholder {"
        "   color: #aaaaaa;"                   // placeholder color
        "}"
        );

    ui->txtContact->setPlaceholderText("Ex. ABC 123");
    ui->txtContact->setFont(QFont("Segoe UI", 11));
    ui->txtContact->setStyleSheet(
        "QLineEdit {"
        "   background: #fdfdfd;"              // soft background
        "   border: 2px solid #dcdcdc;"        // subtle border
        "   border-radius: 12px;"              // rounded corners
        "   padding: 8px 12px;"                // space inside the input
        "   color: #333333;"                   // text color"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4CAF50;"        // highlight border on focus
        "   background: #ffffff;"              // optional focus background
        "}"
        "QLineEdit::placeholder {"
        "   color: #aaaaaa;"                   // placeholder color
        "}"
        );
    ui->txtCustomerName->setPlaceholderText("Ex. Juan D. Cruz");
    ui->txtCustomerName->setFont(QFont("Segoe UI", 11));
    ui->txtCustomerName->setStyleSheet(
        "QLineEdit {"
        "   background: #fdfdfd;"              // soft background
        "   border: 2px solid #dcdcdc;"        // subtle border
        "   border-radius: 12px;"              // rounded corners
        "   padding: 8px 12px;"                // space inside the input
        "   color: #333333;"                   // text color"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4CAF50;"        // highlight border on focus
        "   background: #ffffff;"              // optional focus background
        "}"
        "QLineEdit::placeholder {"
        "   color: #aaaaaa;"                   // placeholder color
        "}"
        );
    ui->txtEmail->setPlaceholderText("example123@gmail.com");
    ui->txtEmail->setFont(QFont("Segoe UI", 11));
    ui->txtEmail->setStyleSheet(
        "QLineEdit {"
        "   background: #fdfdfd;"              // soft background
        "   border: 2px solid #dcdcdc;"        // subtle border
        "   border-radius: 12px;"              // rounded corners
        "   padding: 8px 12px;"                // space inside the input
        "   color: #333333;"                   // text color"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4CAF50;"        // highlight border on focus
        "   background: #ffffff;"              // optional focus background
        "}"
        "QLineEdit::placeholder {"
        "   color: #aaaaaa;"                   // placeholder color
        "}"
        );
    ui->txtOtherMaintenance->setPlaceholderText("");
    ui->txtOtherMaintenance->setFont(QFont("Segoe UI", 11));
    ui->txtOtherMaintenance->setStyleSheet(
        "QLineEdit {"
        "   background: #fdfdfd;"              // soft background
        "   border: 2px solid #dcdcdc;"        // subtle border
        "   border-radius: 12px;"              // rounded corners
        "   padding: 8px 12px;"                // space inside the input
        "   color: #333333;"                   // text color"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4CAF50;"        // highlight border on focus
        "   background: #ffffff;"              // optional focus background
        "}"
        "QLineEdit::placeholder {"
        "   color: #aaaaaa;"                   // placeholder color
        "}"
        );
    ui->txtPlate->setPlaceholderText("Ex. 09123456789");
    ui->txtPlate->setFont(QFont("Segoe UI", 11));
    ui->txtPlate->setStyleSheet(
        "QLineEdit {"
        "   background: #fdfdfd;"              // soft background
        "   border: 2px solid #dcdcdc;"        // subtle border
        "   border-radius: 12px;"              // rounded corners
        "   padding: 8px 12px;"                // space inside the input
        "   color: #333333;"                   // text color"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid #4CAF50;"        // highlight border on focus
        "   background: #ffffff;"              // optional focus background
        "}"
        "QLineEdit::placeholder {"
        "   color: #aaaaaa;"                   // placeholder color
        "}"
        );

    ui->cmbService->setGraphicsEffect(shadow);
    ui->cmbService->setStyleSheet(
        "QListWidget {"
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #ffffff, stop:1 #e0f7fa);"
        "   border: 2px solid #81d4fa;"
        "   border-radius: 15px;"
        "   padding: 5px;"
        "}"
        "QListWidget::item {"
        "   padding: 10px;"
        "   margin: 3px 0;"
        "   border-radius: 8px;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #0288d1;"
        "   color: #ffffff;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #b3e5fc;"
        "}"
        );


    // Apply it to the table widget
    ui->tableAppointments->setGraphicsEffect(shadow);
    ui->tableAppointments->setStyleSheet(
        "QTableWidget {"
        "   background-color: #fdfdfd;"             /* Soft background */
        "   border: 2px solid #81d4fa;"            /* Border around table */
        "   border-radius: 15px;"                  /* Rounded corners */
        "   gridline-color: #dcdcdc;"              /* Grid lines color */
        "   selection-background-color: #0288d1;"  /* Selected row background */
        "   selection-color: #ffffff;"             /* Selected text color */
        "   padding: 5px;"
        "}"
        "QHeaderView::section {"
        "   background-color: #e0f7fa;"           /* Header background */
        "   color: #222222;"                       /* Header text color */
        "   padding: 5px;"
        "   border: 1px solid #81d4fa;"
        "   border-radius: 10px;"                  /* Rounded header corners */
        "}"
        "QTableWidget::item {"
        "   padding: 8px;"
        "   border: none;"                         /* Remove cell borders for smooth look */
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #0288d1;"            /* Highlight selected items */
        "   color: #ffffff;"
        "}"
        );







    // Make background adjust automatically on resize
    ui->centralwidget->installEventFilter(this);

    /*QWidget* glassOverlay = new QWidget(ui->centralwidget);
    glassOverlay->setStyleSheet("background-color: rgba(255, 255, 255, 100); border-radius: 15px;");
    glassOverlay->setGeometry(ui->centralwidget->rect()); // fill central widget
    glassOverlay->lower(); // send behind other UI elements, above background

    QGraphicsBlurEffect* blur = new QGraphicsBlurEffect(glassOverlay);
    blur->setBlurRadius(15);
    glassOverlay->setGraphicsEffect(blur);*/



    // ---------- Setup service list ----------
    ui->cmbService->setSelectionMode(QAbstractItemView::MultiSelection);

    QStringList services = {
        "Check Engine", "Change Oil", "Brake Inspection", "Tire Rotation",
        "Battery Maintenance", "Wiper Blade Replacement", "Fuel System Care",
        "Spark Plug Replacement", "Air Filter Replacement",
        "Alignment and Suspension Check", "Fuel Filter Replacement",
        "Suspension and Steering Repairs", "Body and Paint Work",
        "HVAC System Service","Others"
    };
    ui->cmbService->addItems(services);

    // Show/hide the "Other Maintenance" input box when 'Others' is selected
    connect(ui->cmbService, &QListWidget::itemSelectionChanged, this, [=]() {
        bool othersSelected = false;
        for (QListWidgetItem* item : ui->cmbService->selectedItems()) {
            if (item->text() == "Others") {
                othersSelected = true;
                break;
            }
        }
        ui->txtOtherMaintenance->setVisible(othersSelected);
    });

    // ---------- Setup appointments table ----------
    ui->tableAppointments->setColumnCount(9);
    QStringList headers = {
        "ID", "Customer Name", "Car Model", "Contact",
        "Email", "Plate #", "Service", "Date", "Time"
    };
    ui->tableAppointments->setHorizontalHeaderLabels(headers);
    ui->tableAppointments->hideColumn(0); // hide ID column

    // ---------- Database setup ----------
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("car_maintenance.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
        return;
    } else {
        qDebug() << "✅ Database connected successfully!";
    }

    // ---------- Create table ----------
    QSqlQuery query;
    QString createTable =
        "CREATE TABLE IF NOT EXISTS appointments ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "customer_name TEXT NOT NULL, "
        "car_model TEXT NOT NULL, "
        "contact TEXT, "
        "email TEXT, "
        "plate TEXT, "
        "service TEXT NOT NULL, "
        "date TEXT NOT NULL, "
        "time TEXT NOT NULL)";
    if (!query.exec(createTable)) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    // ---------- Create history table ----------
    QString createHistoryTable =
        "CREATE TABLE IF NOT EXISTS history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "action TEXT NOT NULL, "
        "appointment_id INTEGER, "
        "details TEXT NOT NULL, "
        "timestamp TEXT NOT NULL)";
    if (!query.exec(createHistoryTable)) {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }


    // ---------- Connect buttons ----------
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::addAppointment);
    connect(ui->btnUpdate, &QPushButton::clicked, this, &MainWindow::updateAppointment);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::deleteAppointment);

    loadAppointmentsFromDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------- Event Filter for resizing background ----------
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->centralwidget && event->type() == QEvent::Resize) {
        if (animatedBg) {
            animatedBg->resize(ui->centralwidget->size());
            if (obj == ui->centralwidget && event->type() == QEvent::Resize) {
                if (animatedBg)
                    animatedBg->resize(ui->centralwidget->size());
                if (glassOverlay)
                    glassOverlay->resize(ui->centralwidget->size());
            }

        }
    }
    return QMainWindow::eventFilter(obj, event);
}

// ---------- Helper for SQL errors ----------
static void reportQueryError(const QSqlQuery &q) {
    qDebug() << "Failed SQL:" << q.lastQuery();
    qDebug() << "Error:" << q.lastError().text();
}
void MainWindow::saveHistory(const QString &action, int appointmentId, const QString &details)
{
    QSqlQuery q;
    q.prepare("INSERT INTO history (action, appointment_id, details, timestamp) "
              "VALUES (?, ?, ?, ?)");   // NOW 4 placeholders

    q.addBindValue(action);
    q.addBindValue(appointmentId);
    q.addBindValue(details);
    q.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    if (!q.exec()) {
        qDebug() << "History insert error:" << q.lastError().text();
    }
}


// ======================================================================
//                           ADD APPOINTMENT
// ======================================================================
void MainWindow::addAppointment()
{
    const int MAX_APPOINTMENTS_PER_DAY = 5;  // LIMIT PER DAY

    QString customer = ui->txtCustomerName->text();
    QString carModel = ui->txtCarModel->text();
    QString contact = ui->txtContact->text();
    QString email = ui->txtEmail->text();
    QString plate = ui->txtPlate->text();

    // Get selected services
    QStringList selectedServices;
    for (QListWidgetItem* item : ui->cmbService->selectedItems()) {
        if (item->text() == "Others") {
            QString custom = ui->txtOtherMaintenance->text();
            if (!custom.isEmpty())
                selectedServices << custom;
        } else {
            selectedServices << item->text();
        }
    }

    QString service = selectedServices.join(", ");
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString time = ui->timeAppointment->time().toString("hh:mm");

    if (customer.isEmpty() || carModel.isEmpty() || selectedServices.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in required fields.");
        return;
    }

    // Check if date is fully booked
    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) FROM appointments WHERE date = ?");
    countQuery.addBindValue(date);
    if (!countQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to check booking slots.");
        return;
    }

    int count = 0;
    if (countQuery.next())
        count = countQuery.value(0).toInt();

    if (count >= MAX_APPOINTMENTS_PER_DAY) {
        QMessageBox::warning(this, "Fully Booked",
                             "This date is already fully booked.\nPlease select another day.");
        return;
    }

    // Insert appointment into database
    QSqlQuery query;
    query.prepare(
        "INSERT INTO appointments "
        "(customer_name, car_model, contact, email, plate, service, date, time) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
        );
    query.addBindValue(customer);
    query.addBindValue(carModel);
    query.addBindValue(contact);
    query.addBindValue(email);
    query.addBindValue(plate);
    query.addBindValue(service);
    query.addBindValue(date);
    query.addBindValue(time);

    if (!query.exec()) {
        reportQueryError(query);
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    int id = query.lastInsertId().toInt();
    saveHistory("ADD", id,
                "Customer: " + customer +
                    " | Car: " + carModel +
                    " | Service: " + service +
                    " | Date: " + date +
                    " | Time: " + time);

    // Update table widget
    int row = ui->tableAppointments->rowCount();
    ui->tableAppointments->insertRow(row);
    ui->tableAppointments->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
    ui->tableAppointments->setItem(row, 1, new QTableWidgetItem(customer));
    ui->tableAppointments->setItem(row, 2, new QTableWidgetItem(carModel));
    ui->tableAppointments->setItem(row, 3, new QTableWidgetItem(contact));
    ui->tableAppointments->setItem(row, 4, new QTableWidgetItem(email));
    ui->tableAppointments->setItem(row, 5, new QTableWidgetItem(plate));
    ui->tableAppointments->setItem(row, 6, new QTableWidgetItem(service));
    ui->tableAppointments->setItem(row, 7, new QTableWidgetItem(date));
    ui->tableAppointments->setItem(row, 8, new QTableWidgetItem(time));

    QMessageBox::information(this, "Success", "Appointment added successfully!");

    // ------------------- Send confirmation email -------------------
    if (!email.isEmpty()) {
        QString subject = "Booking Confirmation";
        QString body =
            "Hello " + customer + ",\n\n"
                                  "Your appointment has been successfully booked.\n\n"
                                  "Service: " + service + "\n"
                        "Date: " + date + "\n"
                     "Time: " + time + "\n\n"
                     "Thank you for choosing our Car Maintenance Service!\n";

        // Create SMTP object with SSL port 465
        Smtp *smtp = new Smtp(
            "wazuchan1@gmail.com",       // Your Gmail
            "llhbnpksvonpoyhy",          // Gmail App Password (no spaces)
            "smtp.gmail.com",             // SMTP server
            465,                          // SSL port
            this
            );

        // Connect signals for success/failure
        connect(smtp, &Smtp::success, [email]() {
            QMessageBox::information(nullptr, "Email", "Confirmation email sent to " + email);
        });

        connect(smtp, &Smtp::failure, [email](const QString &err) {
            QMessageBox::critical(nullptr, "Email Error",
                                  "Failed to send email to " + email + "\nError: " + err);
        });

        smtp->sendMail("wazuchan1@gmail.com", email, subject, body);
        qDebug() << "Attempting to send email to:" << email;
    }

    // ------------------- Reset input fields -------------------
    ui->txtCustomerName->clear();
    ui->txtCarModel->clear();
    ui->txtContact->clear();
    ui->txtEmail->clear();
    ui->txtPlate->clear();
    ui->cmbService->clearSelection();
    ui->txtOtherMaintenance->clear();
    ui->txtOtherMaintenance->hide();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeAppointment->setTime(QTime::currentTime());
}


// ======================================================================
//                           UPDATE APPOINTMENT
// ======================================================================
void MainWindow::updateAppointment()
{
    int row = ui->tableAppointments->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Select a row to update.");
        return;
    }

    int id = ui->tableAppointments->item(row, 0)->text().toInt();

    QString customer = ui->txtCustomerName->text();
    QString carModel = ui->txtCarModel->text();
    QString contact = ui->txtContact->text();
    QString email = ui->txtEmail->text();
    QString plate = ui->txtPlate->text();

    QStringList selectedServices;
    for (QListWidgetItem* item : ui->cmbService->selectedItems())
        selectedServices << item->text();
    QString service = selectedServices.join(", ");

    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString time = ui->timeAppointment->time().toString("hh:mm");

    QSqlQuery query;
    query.prepare(
        "UPDATE appointments SET "
        "customer_name=?, car_model=?, contact=?, email=?, plate=?, service=?, date=?, time=? "
        "WHERE id=?"
        );
    query.addBindValue(customer);
    query.addBindValue(carModel);
    query.addBindValue(contact);
    query.addBindValue(email);
    query.addBindValue(plate);
    query.addBindValue(service);
    query.addBindValue(date);
    query.addBindValue(time);
    query.addBindValue(id);

    if (!query.exec()) {
        reportQueryError(query);
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    // Update table widget
    ui->tableAppointments->setItem(row, 1, new QTableWidgetItem(customer));
    ui->tableAppointments->setItem(row, 2, new QTableWidgetItem(carModel));
    ui->tableAppointments->setItem(row, 3, new QTableWidgetItem(contact));
    ui->tableAppointments->setItem(row, 4, new QTableWidgetItem(email));
    ui->tableAppointments->setItem(row, 5, new QTableWidgetItem(plate));
    ui->tableAppointments->setItem(row, 6, new QTableWidgetItem(service));
    ui->tableAppointments->setItem(row, 7, new QTableWidgetItem(date));
    ui->tableAppointments->setItem(row, 8, new QTableWidgetItem(time));

    QMessageBox::information(this, "Updated", "Appointment updated successfully!");
}


// ======================================================================
//                           DELETE APPOINTMENT
// ======================================================================
void MainWindow::deleteAppointment()
{
    int row = ui->tableAppointments->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Select a row to delete.");
        return;
    }

    int id = ui->tableAppointments->item(row, 0)->text().toInt();



    QSqlQuery query;
    query.prepare("DELETE FROM appointments WHERE id=?");
    query.addBindValue(id);

    if (!query.exec()) {
        reportQueryError(query);
        QMessageBox::critical(this, "Database Error", query.lastError().text());
        return;
    }

    ui->tableAppointments->removeRow(row);
    QMessageBox::information(this, "Deleted", "Appointment deleted successfully!");
}

// ======================================================================
//                      LOAD APPOINTMENTS FROM DB
// ======================================================================
void MainWindow::loadAppointmentsFromDatabase()
{
    ui->tableAppointments->setRowCount(0);

    QSqlQuery query("SELECT id, customer_name, car_model, contact, email, plate, service, date, time FROM appointments");

    int row = 0;
    while (query.next()) {
        ui->tableAppointments->insertRow(row);

        for (int col = 0; col < 9; col++) {
            ui->tableAppointments->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }

        row++;
    }

    qDebug() << "Appointments loaded from database.";
}
