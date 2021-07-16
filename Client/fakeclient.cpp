#include "fakeclient.h"

#include <QPushButton>

FakeClient::FakeClient()
{
    this->setWindowTitle("Client");
    this->resize(this->WINDOW_HEIGHT, this->WINDOW_WIDTH);

    QPushButton* send = new QPushButton(this);
    send->setText(this->SEND_BUTTON_NAME);

    this->_layout = new QGridLayout(this);

    this->_label = new QLabel(this);
    this->_label->setText(this->REQUEST_DOESNT_MADE);

    connect(send,
            &QPushButton::clicked,
            this,
            &FakeClient::Send);

    this->_layout->addWidget(this->_label);
    this->_layout->addWidget(send);
}



void FakeClient::Send()
{
    QNetworkRequest request(QUrl(this->SERVER_ADDRES_AND_PORT));
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect( manager,
             &QNetworkAccessManager::finished,
             this,
             &FakeClient::GetAnswer);

    manager->get(request);
}

void FakeClient::GetAnswer(QNetworkReply* reply)
{
   this->_label->setText(reply->readAll());
   reply->deleteLater();
}
