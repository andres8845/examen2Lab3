#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class clientpantalla; }
QT_END_NAMESPACE

class clientpantalla : public QMainWindow
{
    Q_OBJECT

public:
    clientpantalla(QWidget *parent = nullptr);
    ~clientpantalla();

private slots:
    void on_actionConnect_triggered();

    void on_btnSend_clicked();

    void dataReceived(QString message);

    void on_lnClientName_editingFinished();

    void on_cmbStatus_currentIndexChanged(int index);

    void onTyping();

    void on_btnSendFile_clicked();

    void onRejectReceivingFile();

    void onInitReceivingFile(QString clientName, QString fileName, qint64 fileSize);


    void onConnectionACK(QString myName, QStringList clientsName);
    void onNewClientConnectedToServer(QString clienName);
    void onClientNameChanged(QString prevName, QString clientName);
    void onClientDisconnected(QString clientName);


private:
    Ui::clientpantalla *ui;
    ClientManager *_client;
    void setupClient();
};
#endif // MAINWINDOW_H
