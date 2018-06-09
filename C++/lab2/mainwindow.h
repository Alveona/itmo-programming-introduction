#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "rbbutton.h"
#include "logicbutton.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
     int H;
     int W;
     int bombCount;
     int bombsLeft;
     int emptycells;
     int cellstowin;
     int size;
     //const QSize btnSize;
    //int field[H * W];
    void generateField(int H, int W);
    LogicButton **logicbtns;
    RbButton **btns;
    QWidget *menuWidget;
    QHBoxLayout *menuLayout;
    QGridLayout *btnLayout;
    QPushButton *restartButton;
    QVBoxLayout *windowLayout;
    QWidget *windowWidget;
    QLabel *lblBombLeft;
    QLabel *lblTime;
    QTimer *timer;
    QString str;
    int minutes = 0;
    int seconds = 0;
    void startNewGame(int H, int W, int bombCount);
    int rndH;
    int rndW;
    int rnd;
    QMenu *gameMenu;
    QMenu *settingsMenu;
    QAction *newbieGame;
    QAction *professionalGame;
    QAction *expertGame;
    QAction *changeSettings;
    QAction *exitGame;
    QMenuBar *menuBar;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    LogicButton **getLogicbtns() const;
    RbButton **getBtns() const;
    QWidget *buttonWidget;
signals:

public slots:
    void doRightLogic(int i);
    void doLeftLogic(int i);
    void doStartGame();
    void doWinGame();
    void doFlagClick(int i);
    void doTimeUpdate();
    void doNewbieGame();
    void doProfessionalGame();
    void doExpertGame();
    void doQuit();
    //void doSettings();
};

#endif // MAINWINDOW_H
