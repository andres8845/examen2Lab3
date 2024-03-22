#include "ClientServerManager.h"

#include <QDir>

ClientServerManager::ClientServerManager(QHostAddress ip, ushort port, QObject *parent)
    : QObject{parent},
      _ip(ip),
      _port(port)
{
    _socket = new QTcpSocket(this);
    setupClient();
}

ClientServerManager::ClientServerManager(QTcpSocket *client, QObject *parent)
    : QObject{parent},
    _socket(client)
{
    setupClient();
}

void ClientServerManager::connectToServer()
{
    _socket->connectToHost(_ip, _port);
}

void ClientServerManager::disconnectFromHost()
{
    _socket->disconnectFromHost();
}

void ClientServerManager::sendMessage(QString message)
{
    _socket->write(_protocol.textMessage(message, name()));
}

void ClientServerManager::sendName(QString name)
{
    _socket->write(_protocol.setNameMessage(name));
}

void ClientServerManager::sendStatus(ChatProtocolserver::Status status)
{
    _socket->write(_protocol.setStatusMessage(status));
}

QString ClientServerManager::name() const
{
    auto id = _socket->property("id").toInt();
    auto name = _protocol.name().length() > 0 ? _protocol.name() : QString("Client (%1)").arg(id);

    return name;
}
void ClientServerManager::readyRead()
{
    auto data = _socket->readAll();
    _protocol.loadData(data);
    switch (_protocol.type()) {
    case ChatProtocolserver::Text:
        emit textMessageReceived(_protocol.message(), _protocol.receiver());
        break;
    case ChatProtocolserver::SetName:{
        auto prevName = _socket->property("clientName").toString();
        _socket->setProperty("clientName", name());
        emit nameChanged(prevName, name());
        break;
    }
    case ChatProtocolserver::SetStatus:
        emit statusChanged(_protocol.status());
        break;
    default:
        break;
    }
}

void ClientServerManager::setupClient()
{
    connect(_socket, &QTcpSocket::connected, this, &ClientServerManager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientServerManager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &ClientServerManager::readyRead);
}


