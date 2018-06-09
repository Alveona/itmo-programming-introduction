#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    generateUI();
    byteArray = new QByteArray;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 42850);
    connect(socket, SIGNAL(readyRead()), SLOT(receiveMsg()));
}
void MainWindow::changeNickname_slot()
{
    nickname = changingNickname->text();
    currentNickname->setText(nickname);
    changingNickname->setText(QString(""));
}
void MainWindow::receiveMessage(Message *message)
{
    if(message->getMessage() == QString("")) // additional check if smth went wrong
    {
        updateMembersList(message->getName());
        return;
    }
    chatBox->setCurrentFont(QFont("Arial", 12));
    chatBox->append(message->getName());
    cursor = chatBox->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);

    textBlockFormat.setBackground(QColor("#d0e1fb"));
    textBlockFormat.setLeftMargin(4);
    textBlockFormat.setRightMargin(40);
    textBlockFormat.setBottomMargin(0);
    textBlockFormat.setTopMargin(0);

    cursor.mergeBlockFormat(textBlockFormat);
    chatBox->setTextCursor(cursor);
    chatBox->setCurrentFont(QFont("Arial", 18));
    chatBox->append(message->getMessage());
    cursor = chatBox->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignLeft);
    textBlockFormat.setBottomMargin(10);
    cursor.mergeBlockFormat(textBlockFormat);
    chatBox->setTextCursor(cursor);
    chatBox->verticalScrollBar()->setValue(chatBox->verticalScrollBar()->maximum());
}
void MainWindow::openShade()
{
    transparentWidget->setVisible(!transparentWidget->isVisible());
    shadeWidget->setVisible(!shadeWidget->isVisible());
    messageTextBox->clearFocus(); // fixing the bug when border on lineedit was highlighted
}
void MainWindow::receiveMessage_slot()
{
    receivedMessage->setMessage(receivedText);
    receivedMessage->setName(receivedSender);
    receiveMessage(receivedMessage);
}
void MainWindow::sendMessage()
{
    sentMessage->setMessage(messageTextBox->text());
    sentMessage->setName(nickname);
    sentMessage->constructHeader_text(nickname, messageTextBox->text());
    byteArray->clear();
    byteArray->append((char*)sentMessage->getHeader(), sizeof(*(sentMessage->getHeader())));
    byteArray->append(sentMessage->getStrings()[0]);
    byteArray->append('\0');
    byteArray->append(sentMessage->getStrings()[1]);
    byteArray->append('\0');
    socket->writeDatagram(*byteArray, QHostAddress::Broadcast, 42850);

    chatBox->setCurrentFont(QFont("Arial", 12));
    chatBox->append(sentMessage->getName());
    cursor = chatBox->textCursor();
    textBlockFormat = cursor.blockFormat();

    textBlockFormat.setAlignment(Qt::AlignRight);
    textBlockFormat.setBackground(QColor("#d0e1fb"));
    textBlockFormat.setLeftMargin(40);
    textBlockFormat.setRightMargin(4);
    textBlockFormat.setBottomMargin(0);
    textBlockFormat.setTopMargin(0);
    cursor.mergeBlockFormat(textBlockFormat);

    chatBox->setTextCursor(cursor);
    chatBox->setCurrentFont(QFont("Arial", 18));
    chatBox->append(sentMessage->getMessage());
    cursor = chatBox->textCursor();
    textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignRight);
    textBlockFormat.setBottomMargin(10);
    cursor.mergeBlockFormat(textBlockFormat);
    chatBox->setTextCursor(cursor);
    messageTextBox->setText(QString(""));
    chatBox->verticalScrollBar()->setValue(chatBox->verticalScrollBar()->maximum());
}
void MainWindow::updateMembersList(QString nickname)
{
    if(!members.contains(nickname))
    {
        members.push_back(nickname);
    }
    /*membersList->clear();
    for(int i = 0; i < members.size(); i++)
    {
        membersList->append(members.at(i));
        //members.removeAt(i);
    }*/
}
void MainWindow::refreshingMembers()
{
    membersList->clear();
    for(int i = 0; i < members.size(); i++)
    {
        membersList->append(members.at(i));
        //members.removeAt(i);
    }
    members.clear();

}
void MainWindow::receiveMsg()
{
    networkMessage = new Message();
    //QByteArray BA; // debuging packets
    while(socket->hasPendingDatagrams())
    {
        QNetworkDatagram networkDatagram = socket->receiveDatagram();
        if(!networkDatagram.isValid())
            continue;
        //BA = networkDatagram.data(); // debuging packets
        networkMessage->receiveData(networkDatagram.data());
    }
    if(networkMessage->getMessage() == QString(""))
    {
        updateMembersList(networkMessage->getName());
        return;
    }
    if(networkMessage->getName() != this->nickname)
        receiveMessage(networkMessage);
}
void MainWindow::spamIntroducts()
{
    sentMessage->constructHeader_introduction(nickname);
    byteArray->clear();
    byteArray->append((char*)sentMessage->getHeader(), sizeof(*(sentMessage->getHeader())));
    byteArray->append(sentMessage->getStrings()[0]);
    byteArray->append('\0');
    socket->writeDatagram(*byteArray, QHostAddress::Broadcast, 42850);
}
void MainWindow::generateUI()
{
    networkMessage = new Message();
    setFixedSize(QSize(360, 540));
    statusBarLayout = new QHBoxLayout();
    statusBarWidget = new QWidget();
    statusBarWidget->setStyleSheet(QString("background-color: #4a76a8;"));
    shadeButton = new QPushButton();
    statusBarLayout->addWidget(shadeButton);
    shadeButton->setFixedSize(QSize(25, 25));
    shadeButton->setStyleSheet("background-color: rgba(0, 0, 0, 0%)");
    shadeButton->setIcon(QIcon(":/images/Assets/menuicon.png"));
    shadeButton->setIconSize(QSize(25, 25));
    connect(shadeButton, SIGNAL(clicked(bool)), this, SLOT(openShade()));
    statusBarImage = new QPushButton;
    statusBarImage->setStyleSheet("background-color: rgba(0, 0, 0, 0%)");
    statusBarImage->setIcon(QIcon(":/images/Assets/statusbarimage.png"));
    statusBarImage->setIconSize(QSize(200, 35));
    statusBarImage->setFixedSize(QSize(200, 40));
    statusBarLayout->addWidget(statusBarImage);
    statusBarLayout->setAlignment(statusBarImage, Qt::AlignHCenter);
    statusBarLayout->setSpacing(0);
    statusBarWidget->setLayout(statusBarLayout);
    statusBarWidget->setFixedSize(QSize(360, 50));

    messageSendLayout = new QHBoxLayout();
    messageSendWidget = new QWidget();
    messageTextBox = new QLineEdit();
    sendMsgButton = new QPushButton();
    sendMsgButton->setFixedSize(QSize(25, 25));
    sendMsgButton->setStyleSheet("background-color: rgba(0, 0, 0, 0%)");
    sendMsgButton->setIcon(QIcon(":/images/Assets/sendmsg.png"));
    sendMsgButton->setIconSize(QSize(25, 25));
    //messageTextBox->setAlignment(Qt::AlignLeft);
    messageSendLayout->addWidget(messageTextBox);
    messageSendLayout->addWidget(sendMsgButton);
    messageSendLayout->setSpacing(20);
    messageSendLayout->setAlignment(sendMsgButton, Qt::AlignLeft);
    //messageSendLayout->setMargin(20);
    messageSendWidget->setStyleSheet(QString("background-color: #dbe1ed;"));
    messageSendWidget->setLayout(messageSendLayout);
    messageSendWidget->setFixedSize(QSize(360, 50));
    connect(sendMsgButton, SIGNAL(clicked(bool)), this, SLOT(sendMessage()));
    connect(messageTextBox, SIGNAL(returnPressed()), this, SLOT(sendMessage()));

    nickname = QString("Anonymous");
    receivedText = QString("Message Received."); // just for test
    receivedSender = QString("Sender"); // just for test
    receivedMessage = new Message();
    receivedMessage->setMessage(receivedText); // fix
    sentMessage = new Message();
    timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(receiveMessage_slot())); // TEST MESSAGE INTERFACE
    connect(timer, SIGNAL(timeout()), this, SLOT(spamIntroducts()));

    timer->start(3000);

    dialogLayout = new QVBoxLayout();
    chatBox = new QTextEdit();
    chatBox->setReadOnly(true);
    dialogLayout->addWidget(chatBox);
    chatBox->setStyleSheet("background: rgba(0,0,255, 0%);");
    chatBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chatBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    chatBox->setFont(QFont("Arial", 18));
    for(int i = 0; i < 20; i++) // for initial spacing to start messages from bottom
        chatBox->append(" ");
    dialogWidget = new QWidget();
    dialogWidget->setStyleSheet(QString("background-color: #eef2fb;")); //d5ecfc
    dialogWidget->setLayout(dialogLayout);



    windowLayout = new QVBoxLayout();
    windowLayout->addWidget(statusBarWidget);
    windowLayout->addWidget(dialogWidget);
    windowLayout->addWidget(messageSendWidget);
    windowLayout->setSpacing(0);
    windowLayout->setMargin(0);
    windowWidget = new QWidget();
    windowWidget->setLayout(windowLayout);

    shadeLayout = new QVBoxLayout();
    currentNickname = new QLabel();
    currentNickname->setText(nickname);
    currentNickname->setFont(QFont("Arial", 22));
    currentNickname->setFixedHeight(40);
    currentStatus = new QLabel();
    currentStatus->setText(QString("online"));
    currentStatus->setFont(QFont("Arial", 14));
    changingNickname = new QLineEdit();
    changeNickname = new QPushButton();
    changeNickname->setFixedWidth(200);
    connect(changeNickname, SIGNAL(clicked(bool)), this, SLOT(changeNickname_slot()));
    connect(changingNickname, SIGNAL(returnPressed()), this, SLOT(changeNickname_slot()));
    changeNickname->setText("Change Nickname");
    membersListLabel = new QLabel();
    membersListLabel->setText("Online Users:");
    membersListLabel->setFont(QFont("Arial", 12));
    membersList = new QTextEdit();
    membersList->setStyleSheet("background: rgba(0, 0, 255, 0%);");
    membersList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    membersList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    membersList->setDisabled(true);
    membersList->setFont(QFont("Arial", 14));
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshingMembers()));
    //QVBoxLayout *shadeLayout2 = new QVBoxLayout;
    //shadeLayout2->addWidget(currentNickname);

    shadeLayout->addWidget(currentNickname);
    shadeLayout->addWidget(currentStatus);
    shadeLayout->addWidget(changingNickname);
    shadeLayout->addWidget(changeNickname);
    shadeLayout->addWidget(membersListLabel);
    shadeLayout->addWidget(membersList);
    //shadeLayout->setAlignment(currentNickname, Qt::AlignBottom);
    //shadeLayout->setAlignment(currentNickname, Qt::AlignTop);
    shadeLayout->setAlignment(currentStatus, Qt::AlignTop);
    //currentStatus->setMargin(0);
    //shadeLayout->setSpacing(0);
    //shadeLayout->setAlignment(changeNickname, Qt::AlignTop);
    //shadeLayout->setAlignment(changingNickname, Qt::AlignTop);
    shadeLayout->setAlignment(changeNickname, Qt::AlignTop);
    shadeLayout->setAlignment(changeNickname, Qt::AlignHCenter);
    shadeLayout->setAlignment(membersList, Qt::AlignTop);
    shadeWidget = new QWidget(windowWidget);
    shadeWidget->setLayout(shadeLayout);
    //QWidget *shadeWidget2 = new QWidget(shadeWidget);
    //shadeWidget2->setLayout(shadeLayout2);
    //shadeWidget->setStyleSheet("background-color: #b9bdc4");
    shadeWidget->setStyleSheet("background-color: rgb(255, 255, 255);");
    //shadeWidget->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
    //                           stop:0 blue, stop:1 rgb(200, 230, 200))");
    shadeWidget->setFixedSize(QSize(360 * 3/4, 540));
    shadeWidget->hide();
    transparentLayout = new QVBoxLayout();
    transparentButton = new QPushButton();
    transparentButton->setFixedSize(QSize(360*1/4, 540));
    transparentButton->setStyleSheet("background-color: rgba(0, 0, 0, 0%)");
    connect(transparentButton, SIGNAL(clicked(bool)), this, SLOT(openShade()));
    transparentLayout->addWidget(transparentButton);
    //transparentButton->setGeometry(QRect(360 - 360*1/4, 0, 360 * 1/4, 540));
    transparentWidget = new QWidget(windowWidget);
    transparentWidget->setLayout(transparentLayout);
    transparentWidget->setStyleSheet("background-color: rgba(0, 0, 0, 50%)");
    transparentWidget->setFixedSize(QSize(360*1/4, 540));
    transparentWidget->setGeometry(QRect(360 - 360*1/4, 0, 360 * 1/4, 540));
    transparentWidget->hide();
    setCentralWidget(windowWidget);
    //setCentralWidget(windowWidget);
}
