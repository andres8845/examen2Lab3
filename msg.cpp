#include "msg.h"
#include "ui_ChatItemWidget.h"

#include <QTime>

ChatItemWidget::ChatItemWidget(QWidget *parent, QString nombre) :
    QWidget(parent),ui(new Ui::ChatItemWidget)
{
    ui->setupUi(this);
    this->nombre = nombre;
}

ChatItemWidget::~ChatItemWidget()
{
    delete ui;
}

void ChatItemWidget::setMessage(QString message, bool isMyMessage)
{
    if(isMyMessage){
        ui->label->setAlignment(Qt::AlignRight);
        ui->lbname->setAlignment(Qt::AlignRight);
        ui->lblTime->setAlignment(Qt::AlignRight);
    }else{
    }
    ui->lbname->setText(nombre);
    ui->label->setText(message);
    ui->lblTime->setText(QTime::currentTime().toString("HH:mm"));
}
