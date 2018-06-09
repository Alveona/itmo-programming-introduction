#include "mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#define field(i,j) field[(i)*W+j]
//int field[H*W];
LogicButton **MainWindow::getLogicbtns() const
{
    return logicbtns;
}

RbButton **MainWindow::getBtns() const
{
    return btns;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    startNewGame(20, 20, 15);
    this->layout()->setSizeConstraint( QLayout::SetFixedSize );

    menuBar = new QMenuBar;
    gameMenu = new QMenu("&Game");
    gameMenu->addAction("&Newbie", this, SLOT(doNewbieGame()), Qt::CTRL + Qt::Key_N);
    gameMenu->addAction("&Professional", this, SLOT(doProfessionalGame()), Qt::CTRL + Qt::Key_P);
    gameMenu->addAction("&Expert", this, SLOT(doExpertGame()), Qt::CTRL + Qt::Key_E);
    //gameMenu->addSeparator();
    gameMenu->addAction("&Quit", this, SLOT(doQuit()), Qt::CTRL + Qt::Key_Q);
    menuBar->addMenu(gameMenu);
    menuBar->show();
}
void MainWindow::doRightLogic(int index)
{
   printf("\n%d: ", index);
   logicbtns[index]->doRightLogic();
   //**(logicbtns+index).doRightLogic();
}
void MainWindow::doLeftLogic(int index)
{
    printf("\n%d: ", index);
    //int nextx, nexty;
    //char flag = false;
    if(logicbtns[index]->getState() == BOMB)
    {
        printf("\n============BOMB============\n");
        logicbtns[index]->doLeftLogic();
        QMessageBox msgBox;
        msgBox.setText("I'm afraid you lost :(");
        msgBox.setDefaultButton(QMessageBox::Ok);
        timer->stop();
        msgBox.exec();
        buttonWidget->setDisabled(true);
        buttonWidget->blockSignals(true);

        return;
    }
    if(logicbtns[index]->getState() == OPENED || logicbtns[index]->getState() == FLAG)
        return;
    logicbtns[index]->doLeftLogic();
    //int _i = 0;
    //int _j = 0;
    int x = logicbtns[index]->getW();
    int y = logicbtns[index]->getH();
    if(logicbtns[index]->getBombCount() == 0)
    {
        for (int curry = (y > 0 ? y - 1 : y); curry <= (y < H - 1 ? y + 1 : y); curry++)
        {
            for (int currx = (x > 0 ? x - 1 : x); currx <= (y < W - 2 ? x + 1 : x); currx++)
            {
                doLeftLogic(curry*W+currx);
            }
        }
    }
}
void MainWindow::doTimeUpdate()
{
    seconds++;
    if(seconds == 60)
    {
        minutes++;
        seconds = 0;
    }
    //QString("Time: %2d:%2d").arg(minutes, seconds);
    //lblTime->setText(QString("Time: %2d:%2d").arg(minutes, seconds));
    lblTime->setText(str.sprintf("Time: %02d:%02d", minutes, seconds));
    //lblTime->setText(QString("Time: %2d:%2d").arg(minutes, seconds));
}
void MainWindow::doNewbieGame()
{
    minutes = 0;
    seconds = 0;
    timer->stop();
    startNewGame(12, 12, 15);
}
void MainWindow::doProfessionalGame()
{
    minutes = 0;
    seconds = 0;
    timer->stop();
    startNewGame(16, 16, 40);
}
void MainWindow::doExpertGame()
{
    minutes = 0;
    seconds = 0;
    timer->stop();
    startNewGame(25, 25, 70);
}
void MainWindow::doQuit()
{
    QApplication::quit();
}
void MainWindow::doFlagClick(int i)
{
    bombsLeft = (i == 1)? bombsLeft - 1 : bombsLeft + 1;
    if(bombsLeft >= 0)
        lblBombLeft->setText(QString("Bombs: ") + QString::number(bombsLeft));
}
void MainWindow::doStartGame()
{
    minutes = 0;
    seconds = 0;
    timer->stop();
    startNewGame(H, W, bombCount);
}
void MainWindow::doWinGame()
{
    emptycells++;
    if(emptycells == cellstowin)
    {
        QMessageBox msgBox;
        msgBox.setText("Awesome Victory!");
        msgBox.setDefaultButton(QMessageBox::Ok);
        timer->stop();
        msgBox.exec();
        buttonWidget->setDisabled(true);
        buttonWidget->blockSignals(true);
        return;
    }
}
void MainWindow::startNewGame(int H = 15, int W = 15, int bombCount = 30)
{
    this->H = H;
    this->W = W;
    this->bombCount = bombCount;
    bombsLeft = bombCount;
    emptycells = 0;
    cellstowin = H * W - bombCount;
    size = H*W;
    int field[H * W];
    const QSize btnSize = QSize(25, 25);
    logicbtns = new LogicButton*[H*W];
    std::srand(unsigned(std::time(0)));

    btns = new RbButton*[H*W];
    buttonWidget = new QWidget();
    for(int i = 0; i < size; i++) {
        btns[i] = new RbButton(buttonWidget, i);
        btns[i]->setIcon(QIcon(":/images/Assets/cell.png"));
        btns[i]->setIconSize(btnSize);
        btns[i]->setFixedSize(btnSize);
        field[i] = 0;
    }
    for(int i = 0; i < bombCount; i++)
    {
        //int rnd = std::rand()%((H)*(W));
        rndH = 1 + std::rand()%(H - 1);
        rndW = 1 + std::rand()%(W - 1);
        rnd = rndW*W + rndH;
        //printf("BOMB: x: %d, y: %d\n", rndW, rndH);
        field[rnd] = 1;

        //logicbtns[rnd] = new LogicButton(1, btns[rnd]);
        //connect(btns[i])
    }
    int currentBombCount = 0;
    for(int i = 0; i < size; i++)
    {
        //btns[i]->setText(QString::number(field[i]));
        logicbtns[i] = new LogicButton(field[i], btns[i], i);
        //logicbtns[i]->setH(H);
        //logicbtns[i]->setW(W);
        connect(btns[i], SIGNAL(rightclicked(int)), this, SLOT(doRightLogic(int)));
        connect(btns[i], SIGNAL(leftclicked(int)), this, SLOT(doLeftLogic(int)));
        connect(btns[i], SIGNAL(bombopened_signal()), this, SLOT(doWinGame()));
        connect(btns[i], SIGNAL(flagclicked_signal(int)), this, SLOT(doFlagClick(int)));

    }
    for(int i = 0; i < H; i++)
    {
        //currentBombCount = 0;
        for(int j = 0; j < W; j++)
        {
            currentBombCount = 0;
            if(field[(i-1)*W + j] == 1 && i != 0)
                currentBombCount++;
            if(field[(i+1)*W + j] == 1 && i != H - 1)
                currentBombCount++;
            if(field[i*W + (j-1)] == 1 && j != 0)
                currentBombCount++;
            if(field[i*W + (j+1)] == 1 && j != W - 1)
                currentBombCount++;
            if(field[(i-1)*W + (j-1)] == 1 && i != 0 && j != 0)
                currentBombCount++;
            if(field[(i+1)*W + (j+1)] == 1 && i != H - 1 && j != W - 1)
                currentBombCount++;
            if(field[(i-1)*W + (j+1)] == 1 && j != W - 1 && i != 0)
                currentBombCount++;
            if(field[(i+1)*W + (j-1)] == 1 && i != H - 1 && j != 0)
                currentBombCount++;
            logicbtns[i*W+j]->setBombCount(currentBombCount);
            logicbtns[i*W+j]->setH(i);
            logicbtns[i*W+j]->setW(j);
            //if(currentBombCount != 0)
            //btns[i*W+j]->setText(QString::number(currentBombCount));
        }
    }

    btnLayout = new QGridLayout(buttonWidget);
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            btnLayout->addWidget(btns[j + i * W], 0 + i, j);
        }
    }
    btnLayout->setSpacing(10);
    menuWidget = new QWidget();
    restartButton = new QPushButton();
    lblBombLeft = new QLabel();
    lblTime = new QLabel();
    timer = new QTimer(this);
    connect(restartButton, SIGNAL(clicked(bool)), this, SLOT(doStartGame()));
    restartButton->setFixedSize(QSize(35, 35));
    restartButton->setIcon(QIcon(":/images/Assets/game_button.png"));
    restartButton->setIconSize(QSize(35, 35));
    lblBombLeft->setText(QString("Bombs: ") + QString::number(bombsLeft));
    lblTime->setText(QString("Time: ") + QString("00:00"));
    lblBombLeft->setFont(QFont("Courier", 18));
    lblTime->setFont(QFont("Courier", 18));
    menuLayout = new QHBoxLayout();
    menuLayout->addWidget(lblTime);
    menuLayout->addWidget(restartButton);
    menuLayout->addWidget(lblBombLeft);
    //menuLayout->setAlignment(Qt::AlignCenter);
    menuLayout->setAlignment(restartButton, Qt::AlignCenter);
    menuLayout->setAlignment(lblBombLeft, Qt::AlignRight);
    menuLayout->setAlignment(lblTime, Qt::AlignLeft);
    menuWidget->setLayout(menuLayout);
    windowLayout = new QVBoxLayout();
    windowWidget = new QWidget();
    buttonWidget->setLayout(btnLayout);
    windowLayout->addWidget(menuWidget);
    windowLayout->addWidget(buttonWidget);
    //windowLayout->addWidget(menuWidget);
    windowWidget->setLayout(windowLayout);
    connect(timer, SIGNAL(timeout()), this, SLOT(doTimeUpdate()));
    timer->start(1000);
    setCentralWidget(windowWidget);
    //setCentralWidget(buttonWidget);
}

