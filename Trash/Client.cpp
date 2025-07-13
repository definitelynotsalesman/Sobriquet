#include "Client.hpp"
//QHostAddress to get HostAddress


Client::Client(QWidget *parent)
{
    socket = new QTcpSocket(this);

    connect(this, SIGNAL(newMessage(QString)), this, SLOT(displayMessage(QString))); //sends 
    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(discardSocket()));

    /*connect(socket, &QTcpSocket::readyRead, this, &YourClass::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &YourClass::discardSocket);
    */

}

Client::~Client()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

void Client::readSocket(){
    QByteArray byteArray = socket->readAll();
    QDataStream incomingMessage(&byteArray, QIODevice::ReadOnly);
    incomingMessage.setVersion(QDataStream::Qt_6_7);

    while(!incomingMessage.atEnd()){
        QString message;
        incomingMessage >> message;
        message.prepend(QString("%1 :: ").arg(socket->socketDescriptor()));
        emit newMessage(message);
    }
}

void Client::disconnectSocket(){
    socket->deleteLater(); //thread safe method scheduling socket for deletion
    socket = nullptr; 
}




