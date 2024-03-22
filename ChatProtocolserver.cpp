#include "ChatProtocolserver.h"

#include <QFileInfo>
#include <QIODevice>

ChatProtocolserver::ChatProtocolserver()
{

}

QByteArray ChatProtocolserver::textMessage(QString message, QString receiver)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << Text << receiver << message;
    return ba;
}



QByteArray ChatProtocolserver::setNameMessage(QString name)
{
    return getData(SetName, name);
}

QByteArray ChatProtocolserver::setStatusMessage(Status status)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << SetStatus << status;
    return ba;
}



QByteArray ChatProtocolserver::setFileMessage(QString fileName)
{
    QByteArray ba;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QFileInfo info(fileName);
        QDataStream out(&ba, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_0);
        out << SendFile << info.fileName() << info.size() << file.readAll() ;
        file.close();
    }
    return ba;
}

QByteArray ChatProtocolserver::setClientNameMessage(QString prevName, QString name)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << ClientName << prevName << name;
    return ba;
}

QByteArray ChatProtocolserver::setConnectionACKMessage(QString clientName, QStringList otherClients)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << ConnectionACK << clientName << otherClients;
    return ba;
}

QByteArray ChatProtocolserver::setNewClientMessage(QString clientName)
{
    return getData(NewClient, clientName);
}

QByteArray ChatProtocolserver::setClinetDisconnectedMessage(QString clientName)
{
    return getData(ClientDisconnected, clientName);
}

void ChatProtocolserver::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);
    in >> _type;
    switch (_type) {
    case Text:
        in >> _receiver >> _message;
        break;
    case SetName:
        in >> _name;
        break;
    case SetStatus:
        in >> _status;
        break;
    case InitSendingFile:
        in >> _fileName >> _fileSize;
        break;
    case SendFile:
        in >> _fileName >> _fileSize >> _fileData;
        break;
    default:
        break;
    }
}

QByteArray ChatProtocolserver::getData(MessageType type, QString data)
{
    QByteArray ba;
    QDataStream out(&ba, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << type << data;
    return ba;
}

const QString &ChatProtocolserver::receiver() const
{
    return _receiver;
}

const QByteArray &ChatProtocolserver::fileData() const
{
    return _fileData;
}

qint64 ChatProtocolserver::fileSize() const
{
    return _fileSize;
}

const QString &ChatProtocolserver::fileName() const
{
    return _fileName;
}

ChatProtocolserver::MessageType ChatProtocolserver::type() const
{
    return _type;
}

ChatProtocolserver::Status ChatProtocolserver::status() const
{
    return _status;
}

const QString &ChatProtocolserver::name() const
{
    return _name;
}

const QString &ChatProtocolserver::message() const
{
    return _message;
}
