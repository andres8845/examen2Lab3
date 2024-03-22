#ifndef CLIENTSERVERMANAGER_H
#define CLIENTSERVERMANAGER_H

#include "ChatProtocolserver.h"

#include <QObject>
#include <QTcpSocket>

class ClientServerManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientServerManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    explicit ClientServerManager(QTcpSocket *client, QObject *parent = nullptr);

    void connectToServer();
    void disconnectFromHost();

    void sendMessage(QString message);
    void sendName(QString name);
    void sendStatus(ChatProtocolserver::Status status);
    QString name() const;

signals:
    void connected();
    void disconnected();
//    void dataReceived(QByteArray data);
    void textMessageReceived(const QString message, QString receiver);
    void isTyping();
    void nameChanged(QString prevName, QString name);
    void statusChanged(ChatProtocolserver::Status status);
    void rejectReceivingFile();
    void initReceivingFile(QString clientName, QString fileName, qint64 fileSize);
    void fileSaved(QString path);
private slots:
    void readyRead();

private: //fields
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocolserver _protocol;
    QString _tmpFileName;

private: //methods
     void setupClient();
     void sendFile();
     void saveFile();
};

#endif // CLIENTSERVERMANAGER_H
