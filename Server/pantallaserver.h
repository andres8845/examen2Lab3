#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ServerManager.h"
#include "ClientChatWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PantallaServer; }
QT_END_NAMESPACE

class PantallaServer : public QMainWindow
{
    Q_OBJECT

public:
    PantallaServer(QWidget *parent = nullptr);
    ~PantallaServer();
private slots:
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket *client);
    void setClientName(QString prevName, QString name);
    void setClientStatus(ChatProtocol::Status status);
    void on_tbClientsChat_tabCloseRequested(int index);

private: //fields
    Ui::PantallaServer *ui;
    ServerManager *_server;
private: //methods
    void seupServer();
};
#endif // MAINWINDOW_H
