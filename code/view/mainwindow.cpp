#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Map *map,Character *player1,Character *player2,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , map(map)
{
    ui->setupUi(this);
    players.push_back(player1);
    players.push_back(player2);
    keyRespondTimer = new QTimer(this);
    connect(keyRespondTimer, &QTimer::timeout, this, &MainWindow::slotTimeOut);
    refreshTimer = new QTimer(this);
    refreshTimer->setInterval(50);
    refreshTimer->start();
    //connect(refreshTimer, &QTimer::timeout, this, &MainWindow::slotRefresh);
}

MainWindow::~MainWindow()
{
    delete ui;

    refreshTimer->stop();
    delete keyRespondTimer;
    delete refreshTimer;
    delete map;
    for (auto it : players)
        delete it;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap blockPicture("../bombtest/resources/images/2BLOCKBG.png");
    QPixmap bombPicture("../bombtest/resources/images/bomb.png");
    QPixmap boxPicture("../bombtest/resources/images/2BLOCKYELLOW.png");
    QPixmap stonePicture("../bombtest/resources/images/2BLOCKBLACK.png");
    QPixmap explosionPicture("../bombtest/resources/images/explode0.png");
    QPixmap playersPicture;
    Block *aBlock;
    int rowNumber = map->getRowSize();
    int columnNumber = map->getColumnSize();
    int x,y;
    int rowIndex,columnIndex;

    for (columnIndex = 0; columnIndex < columnNumber; ++columnIndex) {
        x = BLOCK_SIDE_LENGTH * (1 + columnIndex);
        for (rowIndex = 0; rowIndex < rowNumber; ++rowIndex) {
            y = BLOCK_SIDE_LENGTH * (rowIndex + 1);
            aBlock = map->getBlock(columnIndex,rowIndex);
            painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, blockPicture);
            switch (aBlock->getType()) {
            case BLOCK_CAN_BE_DESTROYED_1:
            case BLOCK_CAN_BE_DESTROYED_2:
                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, boxPicture);
                break;
            case BLOCK_CANNOT_BE_DESTROYED_1:
            case BLOCK_CANNOT_BE_DESTROYED_2:
                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, stonePicture);
                break;
            case BOMB_EXPLOSION:
                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, explosionPicture);
                break;
            case BOMB_READY:
                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, bombPicture);
                break;
            default:
                break;
            }
        }
    }
    QString playerName;
    for (quint64 i = 0; i < players.size(); ++i) {
        switch (players[i]->getDirection()){
        case UP:
            playerName = "up" + QString::number(i);
            break;
        case DOWN:
            playerName = "down" + QString::number(i);
            break;
        case LEFT:
            playerName = "left" + QString::number(i);
            break;
        case RIGHT:
            playerName = "right" + QString::number(i);
            break;
        }
        playersPicture.load("../bombtest/resources/images/" + playerName + ".png");
        double characterX = players[i]->getCoordinate().first;
        double characterY = players[i]->getCoordinate().second;
        painter.drawPixmap((characterX + 1) * BLOCK_SIDE_LENGTH, (characterY + 1) * BLOCK_SIDE_LENGTH,
                           BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, playersPicture);
    }
}

void MainWindow::initialize()
{
    setFixedSize(1280,720);
    setWindowTitle("泡泡堂");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
        keys.append(event->key());
    if(!keyRespondTimer->isActive()) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(4);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A :
    case Qt::Key_S :
    case Qt::Key_W :
    case Qt::Key_D :
        sendCommand(0,5);
        break;
    case Qt::Key_Up :
    case Qt::Key_Down :
    case Qt::Key_Left :
    case Qt::Key_Right :
        sendCommand(1,5);
        break;
    }
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
        keys.removeAll(event->key());
    if(keys.isEmpty()&&keyRespondTimer->isActive()) //容器空了，关闭定时器
        keyRespondTimer->stop();

}

void MainWindow::slotTimeOut()
{
    foreach (int key, keys) {
        switch (key) {
        case Qt::Key_A :
            sendCommand(0,0);
            break;
        case Qt::Key_S :
            sendCommand(0,3);
            break;
        case Qt::Key_W :
            sendCommand(0,2);
            break;
        case Qt::Key_D :
            sendCommand(0,1);
            break;
        case Qt::Key_Up:
            sendCommand(1,2);
            break;
        case Qt::Key_Down:
            sendCommand(1,3);
            break;
        case Qt::Key_Left:
            sendCommand(1,0);
            break;
        case Qt::Key_Right:
            sendCommand(1,1);
            break;
        default:
            break;
        }
    }
    this->update();
}

void MainWindow::slotRefresh()
{
    this->update();
}
