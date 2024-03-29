#include "clientSocket.h"
#include "graphresults.h"
#include "helpers/helpers.h"
#include "check/check.h"
#include "menu.h"
#include "purchase.h"
#include "globalClient.h"
#include "popup.h"
#include <iostream>
#include <QMessageBox>
using namespace std;

clientSocket::clientSocket(QObject *parent):QThread(parent){};

void clientSocket::connectSocket(){
    clientSock = new QTcpSocket(this);
    clientSock->connectToHost("192.168.86.196",8080);

    if(clientSock->waitForConnected(3000)){
        connect(this->clientSock,SIGNAL(connected()), this,SLOT(connected()));
        connect(this->clientSock,SIGNAL(disconnected()), this,SLOT(disconnected()));
        connect(this->clientSock,SIGNAL(readyRead()), this,SLOT(readyRead()));
    }
}
void clientSocket :: connected(){
    cout<<"Connection done"<<endl;
}
void clientSocket::disconnected(){
    cout<<"Socket disconnected"<<endl;
}

void clientSocket::readyRead(){
    QByteArray data = clientSock->readAll();
    string dataToString = data.toStdString();
    vector<string> dataFromServer = helper::split(dataToString,";");


    cout<<"<------DATA------>"<<endl;
    cout<<dataToString<<endl;
    cout<<">----------------<"<<endl;

    if(dataFromServer[0]=="00"){

        QMessageBox block;
        block.setText("Server is blocked, please try again later");
        block.exec();

    } else if(dataFromServer[0]=="02"){
        if(dataFromServer[1]=="1"){
            isLogged = true;
            Menu *menu = new Menu;
            menu->show();
        }else if(dataFromServer[1]=="0"){
            Check *check = new Check;
            check->show();
        }
    } else if(dataFromServer[0]=="03"  && fromPurchase){
        fromPurchase = false;
        purchase *p = new purchase;
        p->show();

    } else if(dataFromServer[0]=="03"){
        GraphResults *g = new GraphResults(QString::fromStdString(dataFromServer[1]));
        g->show();
    } else if(dataFromServer[0]=="04"){
        GraphResults *g = new GraphResults(QString::fromStdString(dataFromServer[1]));
        g->show();
    } else if(dataFromServer[0]=="05"){
        GraphResults *g = new GraphResults(QString::fromStdString(dataFromServer[1]));
        g->show();
    } else if(dataFromServer[0]=="20"){
        QMessageBox answ;
        string temp = dataFromServer[1];
        QString qtemp = QString::fromUtf8(temp.c_str());
        answ.setText(qtemp);
        answ.exec();

    } else if(dataFromServer[0]=="21"){
        QMessageBox answ;
        if(dataFromServer[1]=="1"){
            answ.setText("Is Basic");
        } else if(dataFromServer[1]=="0"){
            answ.setText("Is Normal");
        }
        answ.exec();

    } else if(dataFromServer[0]=="22"){

        QMessageBox answ;
        string temp = dataFromServer[1];
        QString qtemp = QString::fromUtf8(temp.c_str());
        answ.setText(qtemp);
        answ.exec();

    }
    else if(dataFromServer[0]=="50"){
        GraphResults *g = new GraphResults(QString::fromStdString(dataFromServer[1]));
        g->show();
    } else if(dataFromServer[0]=="35"){

        if(dataFromServer[1]=="1"){
            QMessageBox block;
            block.setText("Total: "+QString::fromStdString(dataFromServer[2]));
            block.exec();

            PopUp *popUp = new PopUp;
            popUp->show();
        } else {
            QMessageBox block;
            block.setText("Could not complete purchase");
            block.exec();

            PopUp *popUp = new PopUp;
            popUp->show();
        }

    }


}
void clientSocket::send(QByteArray data){
    this->clientSock->write(data);
}
