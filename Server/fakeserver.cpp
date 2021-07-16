#include "fakeserver.h"

#include <QPushButton>

FakeServer::FakeServer(QWidget* parent): _serverIsAble(false)
{
    this->setWindowTitle("Server");
    this->resize(this->WINDOW_HEIGHT, this->WINDOW_WIDTH);

    this->_layout = new QGridLayout(this);

    this->_label = new QLabel(this);
    this->_label->setText(this->SERVER_DISABLE);

    QPushButton* start = new QPushButton(this);
    start->setText(this->START_BUTTON_NAME);

    QPushButton* stop = new QPushButton(this);
    stop->setText(this->STOP_BUTTON_NAME);

    QPushButton* request = new QPushButton(this);
    request->setText(this->REQUEST_BUTTON_NAME);

    connect(start, &QPushButton::clicked, this, &FakeServer::Start);
    connect(stop, &QPushButton::clicked, this, &FakeServer::Stop);
    connect(request, &QPushButton::clicked, this, &FakeServer::Request);

    this->_tcpServer = new QTcpServer(this);

    this->_layout->addWidget(this->_label);
    this->_layout->addWidget(start);
    this->_layout->addWidget(stop);
    this->_layout->addWidget(request);
}

void FakeServer::StartListen()
{
    if(!this->_tcpServer->listen(QHostAddress::Any, this->SERVER_PORT))
    {
        this->_label->setText(this->SOME_ERROR);
        return;
    }


    /*
    if(!this->_webSocket->listen(QHostAddress::Any))
    {
        this->_label->setText(this->SOME_ERROR);
        this->_tcpServer->close();
        return;
    }
    */

    connect(this->_tcpServer,
            &QTcpServer::newConnection,
            this,
            &FakeServer::SendAnswer);

    qDebug() << this->_tcpServer->serverAddress() << this->_tcpServer->serverPort();

    this->_serverIsAble = true;
    this->_label->setText(this->WAIT_REQUEST);
}

void FakeServer::StopListen()
{

    if(this->_tcpServer->isListening())
    {
        this->_tcpServer->close();
    }

    /*
    if(this->_webSocket->isListening())
    {
        this->_webSocket->close();
    }
    */

    disconnect(this->_tcpServer,
               &QTcpServer::newConnection,
               this,
               &FakeServer::SendAnswer);

    this->_serverIsAble = false;
    this->_label->setText(this->SERVER_DISABLE);
}

void FakeServer::Start()
{
    if(!this->_serverIsAble){
        this->StartListen();
    }
}

void FakeServer::Stop()
{
    if(this->_serverIsAble)
    {
        this->StopListen();
    }
}

void FakeServer::SendAnswer()
{
    QTcpSocket* tcpSocket = this->_tcpServer->nextPendingConnection();




    connect(tcpSocket, &QTcpSocket::readyRead, this, &FakeServer::Request);
    this->_label->setText("Hello, World!!!");
}

void FakeServer::Request()
{
    QByteArray result = QStringLiteral("<html>"
"<head>"
"<meta charset=\"UTF-8\">"
"</head>"
"<body>"
"<h1>Hello, World!!!</h1>"
"<p>%1</p>"
"</body>"
"</html>")
            .arg(QDateTime::currentDateTime()
                 .toString()).toUtf8();
    QTcpSocket* tcpSocket = (QTcpSocket*)sender();
    QTextStream os(tcpSocket);
    os.setAutoDetectUnicode(true);
    os << "HTTP/1.1 200 OK\r\n";
    os << "Content-Type: text/html;\r\n";
    os << QStringLiteral("Content-Length: %1\r\n")
          .arg(result.length());
    os << "\r\n";
    os << result;
    tcpSocket->close();
}
