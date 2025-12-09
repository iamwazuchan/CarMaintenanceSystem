#include "smtp.h"
#include <QDebug>
#include <QByteArray>

Smtp::Smtp(const QString &user, const QString &pass,
           const QString &host, int port, QObject *parent)
    : QObject(parent), user(user), pass(pass), host(host), port(port), state(0)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::readyRead, this, &Smtp::readyRead);
    connect(socket, &QSslSocket::connected, this, &Smtp::connected);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(sslErrors(QList<QSslError>)));
    connect(socket, &QSslSocket::errorOccurred, this, &Smtp::errorOccurred);
}

void Smtp::sendMail(const QString &from, const QString &to,
                    const QString &subject, const QString &body)
{
    this->from = from;
    this->to = to;
    this->subject = subject;
    this->body = body;

    socket->connectToHostEncrypted(host, port);
}

void Smtp::connected()
{
    qDebug() << "SMTP: Connected to server";
}

void Smtp::sslErrors(const QList<QSslError> &errors)
{
    for (const auto &err : errors) {
        qDebug() << "SSL Error:" << err.errorString();
    }
    socket->ignoreSslErrors();
}

void Smtp::readyRead()
{
    QByteArray response = socket->readAll();
    QString resp(response);

    if (state == 0 && resp.startsWith("220")) {
        socket->write("EHLO localhost\r\n");
        state = 1;
    }
    else if (state == 1 && resp.contains("250")) {
        socket->write("AUTH LOGIN\r\n");
        state = 2;
    }
    else if (state == 2 && resp.contains("334")) {
        socket->write(user.toUtf8().toBase64() + "\r\n");
        state = 3;
    }
    else if (state == 3 && resp.contains("334")) {
        socket->write(pass.toUtf8().toBase64() + "\r\n");
        state = 4;
    }
    else if (state == 4 && resp.contains("235")) {
        socket->write("MAIL FROM:<" + from.toUtf8() + ">\r\n");
        state = 5;
    }
    else if (state == 5 && resp.contains("250")) {
        socket->write("RCPT TO:<" + to.toUtf8() + ">\r\n");
        state = 6;
    }
    else if (state == 6 && resp.contains("250")) {
        socket->write("DATA\r\n");
        state = 7;
    }
    else if (state == 7 && resp.contains("354")) {
        QString msg;
        msg += "To: <" + to + ">\r\n";
        msg += "From: <" + from + ">\r\n";
        msg += "Subject: " + subject + "\r\n";
        msg += "\r\n";
        msg += body + "\r\n.\r\n";

        socket->write(msg.toUtf8());
        state = 8;
    }
    else if (state == 8 && resp.contains("250")) {
        socket->write("QUIT\r\n");
        socket->disconnectFromHost();
        state = 0;
        qDebug() << "SMTP: Email sent successfully!";
        emit success();
    }
}

void Smtp::errorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug() << "SMTP Error:" << socket->errorString();
    emit failure(socket->errorString());
}

