#include "cliente.h"
#include "ui_cliente.h"
#include "msg.h"
#include <QFileDialog>

Cliente::Cliente(QWidget *parent,QString name,QString name2)
    : QMainWindow(parent)
    , ui(new Ui::Cliente)
{
    ui->setupUi(this);
    setupClient();
    this->name = name;
    this->name2= name2;
    ui->btnSend->setEnabled(false);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

Cliente::~Cliente()
{
    delete ui;
}


void Cliente::setupClient()
{
    _client = new ClientManager();
    connect(_client , &ClientManager::connected, [this](){
        ui->btnSend->setEnabled(true);
        ui->lnMessage->setEnabled(true);
    });
    connect(_client, &ClientManager::textMessageReceived, this, &Cliente::dataReceived);
}

void Cliente::on_btnSend_clicked()
{
    auto message = ui->lnMessage->text().trimmed();
    qDebug() << name2;
    qDebug() << name;
    _client->sendMessage(message, name2);
    ui->lnMessage->setText("");
    ui->lnMessage->setFocus();
    auto chatWidget = new ChatItemWidget(this,name);
    chatWidget->setMessage(message, true);
    auto listWidgetItem = new QListWidgetItem();
    listWidgetItem->setSizeHint(QSize(0, 100));
    ui->lstMessages->addItem(listWidgetItem);
    ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
}

void Cliente::dataReceived(QString message)
{
    auto chatWidget = new ChatItemWidget(this,name2);
    chatWidget->setMessage(message);
    auto listWidgetItem = new QListWidgetItem();
    listWidgetItem->setSizeHint(QSize(0, 100));
    ui->lstMessages->addItem(listWidgetItem);
    ui->lstMessages->setItemWidget(listWidgetItem, chatWidget);
}

void Cliente::on_pushButton_clicked()
{
    _client->connectToServer();
    _client->sendName(name);
    ui->pushButton->hide();
}

void Cliente::on_pushButton_2_clicked()
{
 _client->sendName(name);
}

