#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usuario.h"
#include "qmessagebox.h"
#include "QDateTime"
#include <QFile>
#include <QDataStream>
#include <QStringListModel>

QStringListModel model;
QString name1;
QString name2;
QString userchat = "";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete v;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->uslog->setText("");
    ui->passlog->setText("");
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->nombreCompleto->setText("");
    ui->usuario->setText("");
    ui->contra->setText("");
}


void MainWindow::on_pushButton_5_clicked()
{
    QStringList stringList;
    UsuarioManager obj;
    QString name = ui->uslog->text().simplified();
    QString contraseña = ui->passlog->text().simplified();

    if(!obj.login(name,contraseña)){
        QMessageBox::information(nullptr, "!!!!!!!!!!", "Usuario inexistente!");
    }else{

        ui->stackedWidget->setCurrentIndex(3);
        name2=name;
        ui->label_10->setText(name);

            QFile file("usuariosfile.us");

            QDataStream in(&file);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(nullptr, "!!!!!!!!!!", "No se encontro el archivo");
            }

            Usuario usuarioRegistrado;
            file.seek(0);

            while (!in.atEnd()) {
                in>>usuarioRegistrado.nombre >> usuarioRegistrado.usuario >> usuarioRegistrado.contraseña >> usuarioRegistrado.fecha;
                qDebug() << usuarioRegistrado.nombre;
                if(usuarioRegistrado.usuario!=name){
                    stringList << usuarioRegistrado.usuario;
                }
            }
            model.setStringList(stringList);
            qDebug() << stringList.size();
        }

        ui->listView->setModel(&model);
}


void MainWindow::on_pushButton_6_clicked()
{
    UsuarioManager obj;
    Usuario us;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    us.nombre = ui->nombreCompleto->text().simplified();
    us.usuario = ui->usuario->text().simplified();
    us.contraseña = ui->contra->text().simplified();
    us.fecha = formattedDateTime;

    if(us.nombre=="" || us.usuario=="" || us.contraseña=="")
    {
        QMessageBox::information(nullptr, "Mensaje", "Favor rellenar todas las casillas!");
    }else
    {
        if(!obj.crearUsuario(us)){
            QMessageBox::information(nullptr, "!!!!!!!!!!11", "Usuario existente!");
        }else{
            QMessageBox::information(nullptr, "Registro", "Se ha registrado correctamente!");
            ui->stackedWidget->setCurrentIndex(0);
        }
    }


}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    seupServer();

    QAbstractItemModel *model = ui->listView->model();

    QModelIndexList selectedIndexList = ui->listView->selectionModel()->selectedIndexes();

    if (!selectedIndexList.isEmpty()) {

        QModelIndex selectedIndex = selectedIndexList.first();

        QVariant data = model->data(selectedIndex, Qt::DisplayRole);

        userchat = QString(data.toString());

        qDebug() << "Usuario seleccionado:" << data.toString();



    } else {
        qDebug() << "No se ha seleccionado ningún usuario.";
    }

    name1 = userchat;
    if (userchat !=""){
        userchat = "";

        auto named = name2;

        auto names = name1;

        ui->label_24->setText("Chat de "+names);
        ui->label_25->setText("Chat de "+named);
        v = new Cliente(this,names, named);

        w = new Cliente(this,named,names);

        w->move(768,180);
        v->show();
        v->move(370,180);
        w->show();

        ui->stackedWidget->setCurrentIndex(4);
    }

}


void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setVisible(false);
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id").toInt();
    auto chatWidget= new ClientChatWidget(client, nullptr);
    connect(chatWidget, &ClientChatWidget::clientNameChanged, this, &MainWindow::setClientName);
    connect(chatWidget, &ClientChatWidget::textForOtherClients, _server, &ServerManager::onTextForOtherClients);
}

void MainWindow::setClientName(QString prevName, QString name)
{
    _server->notifyOtherClients(prevName, name);
}

void MainWindow::setClientStatus(ChatProtocol::Status status)
{
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
}

void MainWindow::seupServer()
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected);

}

void MainWindow::on_pushButton_7_clicked()
{
    _server->serverclose();
    ui->stackedWidget->setCurrentIndex(3);
    delete v;
    delete w;
}

