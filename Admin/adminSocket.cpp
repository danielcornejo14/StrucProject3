#include "adminSocket.h"
#include <iostream>
using namespace std;

adminSocket::adminSocket(QObject *parent):QThread(parent){};

void adminSocket::connectSocket(){
    adminSock = new QTcpSocket(this);
    adminSock->connectToHost("localhost",8080);

    if(adminSock->waitForConnected(3000)){
        connect(this->adminSock,SIGNAL(connected()), this,SLOT(connected()));
        connect(this->adminSock,SIGNAL(disconnected()), this,SLOT(disconnected()));
        connect(this->adminSock,SIGNAL(readyRead()), this,SLOT(readyRead()));
    }
}
void adminSocket :: connected(){
    cout<<"Connection done"<<endl;
}
void adminSocket::disconnected(){
    cout<<"Socket disconnected"<<endl;
}

void adminSocket::readyRead(){
    QByteArray data = adminSock->readAll();
    string dataToString = data.toStdString();
    cout<<dataToString<<endl;



}
void adminSocket::send(QByteArray data){
    this->adminSock->write(data);
}