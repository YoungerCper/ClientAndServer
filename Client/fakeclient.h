#ifndef FAKECLIENT_H
#define FAKECLIENT_H

#include <QWidget>
#include <QNetworkRequest>
#include <QLabel>
#include <QGridLayout>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDebug>

class FakeClient : public QWidget
{
public:
    FakeClient();


public slots:

    void Send();
    void GetAnswer(QNetworkReply*);

private:

    const QString SEND_BUTTON_NAME = "Сделать запрос";
    const QString REQUEST_DOESNT_MADE = "Запрос ещё не сделан";
    const QString SERVER_ADDRES_AND_PORT = "http://localhost:21716";

    const int WINDOW_HEIGHT = 400;
    const int WINDOW_WIDTH = 400;

    QGridLayout* _layout;
    QLabel* _label;
};

#endif // FAKECLIENT_H
