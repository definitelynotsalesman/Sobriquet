#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QTcpSocket>
#include <QObject>

namespace Ui {
class MainWindow;
}

class Client : QMainWindow{

    public:
        explicit Client(QWidget *parent = nullptr);
        ~Client();
    signals:
        void newMessage(QString);
    private slots:
        void readSocket();
        void disconnectSocket();

        void displayMessage(const QString& str);
    private:
        Ui::MainWindow *ui;
        QTcpSocket* socket;
};

#endif