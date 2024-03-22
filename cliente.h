#ifndef CLIENTE_H
#define CLIENTE_H

#include <QMainWindow>
#include "ClientManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Cliente; }
QT_END_NAMESPACE

class Cliente : public QMainWindow
{
    Q_OBJECT

public:
    Cliente(QWidget *parent = nullptr,QString name="",QString name2="");
    ~Cliente();

private slots:

    void on_btnSend_clicked();

    void dataReceived(QString message);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Cliente *ui;
    ClientManager *_client;
    void setupClient();
    QString name;
    QString name2;
};

#endif
