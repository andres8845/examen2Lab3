#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "ClientServerManager.h"

#include <QDir>
#include <QTcpSocket>
#include <QWidget>

namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *cleint, QWidget *parent = nullptr);
    void disconnect();
    ~ClientChatWidget();
private slots:

    void clientDisconnected();

    void on_btnSend_clicked();

    void textMessageReceived(QString message, QString receiver);

    void onClientNameChanged(QString prevName, QString name);
signals:
    void clientNameChanged(QString prevName, QString name);
    void statusChanged(ChatProtocolserver::Status status);
    void textForOtherClients(QString message, QString receiver, QString sender);
private:
    Ui::ClientChatWidget *ui;
    ClientServerManager *_client;
    QDir dir;
};

#endif // CLIENTCHATWIDGET_H
