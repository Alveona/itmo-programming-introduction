#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include<QtWidgets>
#include"sendbutton.h"
#include"message.h"
#include <QUdpSocket>
#include<QNetworkDatagram>
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVBoxLayout *windowLayout;
    QWidget *windowWidget;
    QHBoxLayout *messageSendLayout;
    QWidget *messageSendWidget;
    QHBoxLayout *statusBarLayout;
    QWidget *statusBarWidget;
    QVBoxLayout *dialogLayout;
    QWidget *dialogWidget;
    QVBoxLayout *shadeLayout;
    QWidget *shadeWidget;
    QVBoxLayout *transparentLayout;
    QWidget *transparentWidget;
    QPushButton *transparentButton;
    QWidget *pageWidget;


    QPushButton *shadeButton;
    QPushButton *statusBarImage;
    QLineEdit *messageTextBox;
    QPushButton *sendMsgButton;
    QTextEdit *chatBox;
    QTextCursor cursor;
    QTextBlockFormat textBlockFormat;
    QString nickname;
    QString receivedText;
    QString receivedSender;
    QLabel *currentNickname;
    QLabel *currentStatus;
    QLineEdit *changingNickname;
    QPushButton *changeNickname;
    QTextEdit *membersList;
    QLabel *membersListLabel;
    QVector<QString> members;

    QUdpSocket *socket;
    QByteArray *byteArray;
    Message *receivedMessage;
    Message *sentMessage;
    Message *networkMessage;
    QTimer *timer;
    void generateUI();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void receiveMessage(Message *message);
    void transformToNetworkMessage(Message *message);
    void updateMembersList(QString nickname);
signals:

public slots:
    void receiveMsg();
    void changeNickname_slot();
    void sendMessage();
    void receiveMessage_slot();
    void openShade();
    void spamIntroducts();
    void refreshingMembers();
};

#endif // MAINWINDOW_H
