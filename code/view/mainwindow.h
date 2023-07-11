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
#include "../common/map.h"
#include "../common/character.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void sendCommand(int playerNumber,int opr){
        if (playerNumber == 0)
            emit player1CommandSignal(opr);
        else
            emit player2CommandSignal(opr);
    }
signals:
    void player1CommandSignal(int opr);
    void player2CommandSignal(int opr);
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
    QTimer* refreshTimer;
    void slotTimeOut();
    void slotRefresh();
signals:
    void keySignal(int i);
};
#endif // MAINWINDOW_H
