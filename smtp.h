#ifndef SMTP_H
#define SMTP_H

#include <QObject>
#include <QSslSocket>
#include <QString>

class Smtp : public QObject
{
    Q_OBJECT

public:
    explicit Smtp(const QString &user, const QString &pass,
                  const QString &host, int port = 465, QObject *parent = nullptr);
    void sendMail(const QString &from, const QString &to,
                  const QString &subject, const QString &body);

signals:
    void success();
    void failure(const QString &error);

private slots:
    void readyRead();
    void connected();
    void sslErrors(const QList<QSslError> &errors);
    void errorOccurred(QAbstractSocket::SocketError socketError);

private:
    QString user;
    QString pass;
    QString host;
    int port;

    QString from;
    QString to;
    QString subject;
    QString body;

    QSslSocket *socket;
    int state;
};

#endif // SMTP_H
