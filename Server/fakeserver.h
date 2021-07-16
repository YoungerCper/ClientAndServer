#ifndef FAKESERVER_H
#define FAKESERVER_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTcpServer>
#include <QWebSocketServer>
#include <QNetworkSession>
#include <QTcpSocket>


class FakeServer : public QWidget
{
public:



    FakeServer(QWidget* parent = nullptr);

    void StartListen();
    void StopListen();

public slots:

    void Start();
    void Stop();
    void Request();

    void SendAnswer();

private:

    const QString SERVER_DISABLE = "Сервер выключен";
    const QString WAIT_REQUEST = "В ожиднии запроса";
    const QString SOME_ERROR = "Произошла какая-то ошибка";

    const QString STOP_BUTTON_NAME = "Стоп";
    const QString START_BUTTON_NAME = "Старт";
    const QString REQUEST_BUTTON_NAME = "Ответить";

    const int WINDOW_HEIGHT = 400;
    const int WINDOW_WIDTH = 400;
    const int SERVER_PORT = 21716;

    bool _serverIsAble;

    QTcpServer* _tcpServer;
    QNetworkSession* _netSession;

    QGridLayout* _layout;
    QLabel* _label;

};

#endif // FAKESERVER_H
