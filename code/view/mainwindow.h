#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#define BLOCK_SIDE_LENGTH 40

#include <QString>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include "../common/map.h"
#include "../common/character.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void sendCommand(int playerNumber,int opr);
    void signalCheckBombs();
public:
    MainWindow(Map *map,Character *player1,Character *player2,QWidget *parent = nullptr);
    ~MainWindow();
    void initialize();
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    Ui::MainWindow *ui;
    Map *map;
    std::vector<Character *> players;
    QList<int> keys;
    QTimer* keyRespondTimer;
    QTimer* checkBombsTimer;
    QPushButton *start;
    int state = 0;
    void slotTimeOut();
    void slotCheckBombs();
    void slotChangeState();
};
#endif // MAINWINDOW_H