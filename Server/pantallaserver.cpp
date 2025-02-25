#include "ui_pantallaserver.h"
#include "pantallaserver.h"

PantallaServer::PantallaServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PantallaServer)
{
    ui->setupUi(this);
    seupServer();
}

PantallaServer::~PantallaServer()
{
    delete ui;
}

void PantallaServer::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("New Client added: %1").arg(id));
    auto chatWidget= new ClientChatWidget(client, ui->tbClientsChat);
    ui->tbClientsChat->addTab(chatWidget, QString("Client (%1)").arg(id));

    connect(chatWidget, &ClientChatWidget::clientNameChanged, this, &PantallaServer::setClientName);
    connect(chatWidget, &ClientChatWidget::statusChanged, this, &PantallaServer::setClientStatus);
    connect(chatWidget, &ClientChatWidget::isTyping, [this](QString name){
        this->statusBar()->showMessage(name, 750);
    });

        connect(chatWidget, &ClientChatWidget::textForOtherClients, _server, &ServerManager::onTextForOtherClients);
}

void PantallaServer::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    ui->lstClients->addItem(QString("Client disconnected: %1").arg(id));
}

void PantallaServer::setClientName(QString prevName, QString name)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tbClientsChat->indexOf(widget);
    ui->tbClientsChat->setTabText(index, name);

    _server->notifyOtherClients(prevName, name);
}

void PantallaServer::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget *>(sender());
    auto index = ui->tbClientsChat->indexOf(widget);
    QString iconName = ":/icons/";
    switch (status) {
    case ChatProtocol::Available:
        iconName.append("available.png");
        break;
    case ChatProtocol::Away:
        iconName.append("away.png");
        break;
    case ChatProtocol::Busy:
        iconName.append("busy.png");
        break;
    default:
        iconName = "";
        break;

    }

    auto icon = QIcon(iconName);
    ui->tbClientsChat->setTabIcon(index, icon);
}

void PantallaServer::seupServer()
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &PantallaServer::newClientConnected);
    connect(_server, &ServerManager::clientDisconnected, this, &PantallaServer::clientDisconnected);

}


void PantallaServer::on_tbClientsChat_tabCloseRequested(int index)
{
    auto chatWidget = qobject_cast<ClientChatWidget *>(ui->tbClientsChat->widget(index));
    chatWidget->disconnect();
    ui->tbClientsChat->removeTab(index);
}

