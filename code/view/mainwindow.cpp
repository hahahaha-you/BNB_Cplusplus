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
    //checkBombsTimer = new QTimer(this);
    //checkBombsTimer->setInterval(50);
    //checkBombsTimer->start();
    //connect(checkBombsTimer, &QTimer::timeout, this, &MainWindow::slotCheckBombs);
    start = new QPushButton(this);
    connect(start, &QPushButton::clicked, this, &MainWindow::slotChangeState);
}


MainWindow::~MainWindow()
{
    delete ui;

    //checkBombsTimer->stop();
    delete keyRespondTimer;
    //delete checkBombsTimer;
    delete map;
    for (auto it : players)
        delete it;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap background("../bombtest/resources/images/mainCover.jpg");
    painter.drawPixmap(0, 0, 560, 560, background);
    if (state == RUNNING || state == END) {
        QPixmap blockPicture("../bombtest/resources/images/2BLOCKBG.png");
        QPixmap bombPicture("../bombtest/resources/images/bomb.png");
        QPixmap boxPicture("../bombtest/resources/images/2BLOCKYELLOW.png");
        QPixmap stonePicture("../bombtest/resources/images/2BLOCKBLACK.png");
        QPixmap upWavePicture("../bombtest/resources/images/upwave.png");
        QPixmap downWavePicture("../bombtest/resources/images/downwave.png");
        QPixmap leftWavePicture("../bombtest/resources/images/leftwave.png");
        QPixmap rightWavePicture("../bombtest/resources/images/rightwave.png");
        QPixmap centerWavePicture("../bombtest/resources/images/centerwave.png");
        QPixmap speedPicture("../bombtest/resources/images/speed.png");
        QPixmap boomPicture("../bombtest/resources/images/boom.png");
        QPixmap laserGunPicture("../bombtest/resources/images/lasergun.png");
        QPixmap laserUpPicture("../bombtest/resources/images/laserup.png");
        QPixmap laserRightPicture(("../bombtest/resources/images/laserright.png"));
        QPixmap playersPicture;
        Block *aBlock;
        int rowNumber = map->getRowSize();
        int columnNumber = map->getColumnSize();
        int x,y;
        int rowIndex,columnIndex;
        uint lastPropIndex = 0;

        for (rowIndex = 0; rowIndex < rowNumber; ++rowIndex) {
            y = BLOCK_SIDE_LENGTH * (rowIndex + 1);
            for (columnIndex = 0; columnIndex < columnNumber; ++columnIndex) {
                x = BLOCK_SIDE_LENGTH * (1 + columnIndex);
                aBlock = map->getBlock(columnIndex,rowIndex);
                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, blockPicture);
                uint propIndex = lastPropIndex;
                switch (aBlock->getType()) {
                case ROAD :
                    while (true) {
                        Prop *pr = map->getProp(propIndex);
                        if (pr == nullptr) {
                            lastPropIndex = propIndex;
                            break;
                        }
                        if (!pr->propExists()) {
                            lastPropIndex = propIndex;
                            ++propIndex;
                            continue;
                        }
                        int propX = pr->getCoordinate().first;
                        int propY = pr->getCoordinate().second;
                        if (propX == columnIndex && propY == rowIndex) {
                            switch (pr->getType()) {
                            case BIGBOMB :
                                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, boomPicture);
                                break;
                            case SPEEDUP :
                                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, speedPicture);
                                break;
                            case LASER :
                                painter.drawPixmap(x, y + 10, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1 - 20, laserGunPicture);
                                break;
                            }
                            lastPropIndex = propIndex + 1;
                            break;
                        } else if ((propX > columnIndex && propY == rowIndex) || propY > rowIndex) {
                            lastPropIndex = propIndex;
                            break;
                        }
                        ++propIndex;
                    }
                    break;
                case BLOCK_CAN_BE_DESTROYED_1:
                case BLOCK_CAN_BE_DESTROYED_2:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, boxPicture);
                    break;
                case BLOCK_CANNOT_BE_DESTROYED_1:
                case BLOCK_CANNOT_BE_DESTROYED_2:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, stonePicture);
                    break;
                case BOMB_EXPLOSION_LEFT:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, leftWavePicture);
                    break;
                case BOMB_EXPLOSION_RIGHT:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, rightWavePicture);
                    break;
                case BOMB_EXPLOSION_UP:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, upWavePicture);
                    break;
                case BOMB_EXPLOSION_DOWN:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, downWavePicture);
                    break;
                case BOMB_EXPLOSION_CENTRAL:
                    painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, centerWavePicture);
                    break;
                case LASER_EXPLOSION_LEFT :
                case LASER_EXPLOSION_RIGHT :
                case LASER_EXPLOSION_CENTRAL_LEFT :
                case LASER_EXPLOSION_CENTRAL_RIGHT :
                    painter.drawPixmap(x, y + 10, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1 - 20, laserRightPicture);
//                    painter.drawPixmap(x + 10, y, BLOCK_SIDE_LENGTH + 1 - 20, BLOCK_SIDE_LENGTH + 1, laserRightPicture);
                    break;
                case LASER_EXPLOSION_CENTRAL_UP :
                case LASER_EXPLOSION_CENTRAL_DOWN :
                case LASER_EXPLOSION_UP :
                case LASER_EXPLOSION_DOWN :
                    painter.drawPixmap(x + 10, y, BLOCK_SIDE_LENGTH + 1 - 20, BLOCK_SIDE_LENGTH + 1, laserUpPicture);

                    break;
                default:
                    break;
                }
            }
        }

        int bombIndex = 0;
        for (mapWeapon *bomb = map->getBomb(bombIndex); bomb != nullptr; bomb = map->getBomb(++bombIndex)) {
            int bombX = bomb->getCoordinate().first;
            int bombY = bomb->getCoordinate().second;
            if (map->getBlock(bombX,bombY)->getType() != BOMB_EXPLOSION_CENTRAL)
                painter.drawPixmap((bombX + 1) * BLOCK_SIDE_LENGTH, (bombY + 1) * BLOCK_SIDE_LENGTH,
                           BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, bombPicture);
        }

        QString playerName;
        for (quint64 i = 0; i < players.size(); ++i) {
            switch (players[i]->getDirection()) {
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
            if (players[i]->getLive() != 0) {
                playersPicture.load("../bombtest/resources/images/" + playerName + ".png");
                double characterX = players[i]->getCoordinate().first;
                double characterY = players[i]->getCoordinate().second;
                painter.drawPixmap((characterX + 1) * BLOCK_SIDE_LENGTH, (characterY + 1) * BLOCK_SIDE_LENGTH,
                           BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, playersPicture);
            }
        }
        if (state == END) {
            QPixmap end("../bombtest/resources/images/gameover.png");
            painter.drawPixmap(120,200,320,160,end);
        }
    }
    else if (state == START){
        QPixmap icon("../bombtest/resources/images/start.png");
        start->setParent(this);
        start->setIcon(icon);
        start->setIconSize(QSize(200,70));
        start->show();
        start->setStyleSheet("QPushButton{color:white; background-color:transparent;}");
        start->move(200,460);
        start->setFixedSize(icon.size());
    }

}

void MainWindow::initialize()
{
    setFixedSize(560,560);
    setWindowTitle("泡泡堂");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
        keys.append(event->key());
    bool flag = !keyRespondTimer->isActive();
    if(flag) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(10);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A :
    case Qt::Key_S :
    case Qt::Key_W :
    case Qt::Key_D :
    case Qt::Key_Q :
    case Qt::Key_Space :
        emit sendCommand(0,5);
        break;
    case Qt::Key_Up :
    case Qt::Key_Down :
    case Qt::Key_Left :
    case Qt::Key_Right :
    case Qt::Key_O :
        emit sendCommand(1,5);
        break;
    }
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
        keys.removeAll(event->key());
    //if(keys.isEmpty()&&keyRespondTimer->isActive()) //容器空了，关闭定时器
        //keyRespondTimer->stop();
}

void MainWindow::slotTimeOut()
{
    foreach (int key, keys) {
        switch (key) {
        case Qt::Key_A :
            emit sendCommand(0,0);
            break;
        case Qt::Key_S :
            emit sendCommand(0,3);
            break;
        case Qt::Key_W :
            emit sendCommand(0,2);
            break;
        case Qt::Key_D :
            emit sendCommand(0,1);
            break;
        case Qt::Key_Space :
            emit sendCommand(0,4);
            break;
        case Qt::Key_Up:
            emit sendCommand(1,2);
            break;
        case Qt::Key_Down:
            emit sendCommand(1,3);
            break;
        case Qt::Key_Left:
            emit sendCommand(1,0);
            break;
        case Qt::Key_Right:
            emit sendCommand(1,1);
            break;
        case Qt::Key_O:
            emit sendCommand(1,4);
            break;
        default:
            break;
        }
    }
    if (keys.isEmpty()) {
        emit sendCommand(0,5);
        emit sendCommand(1,5);
    }

    int count = 0, livePlayer = 0;
    for (uint i = 0; i < players.size(); ++i)
        if (players[i]->getLive() != 0) {
            ++count;
            livePlayer = i;
        }
    if (count == 1) {
        slotOpenEndWindow(livePlayer);
    }
    else
        this->update();
}

void MainWindow::slotCheckBombs()
{
    emit signalCheckBombs();
}

void MainWindow::slotChangeState()
{
    state = RUNNING;
    start->close();
    this->setFocus();
    this->update();
}

void MainWindow::slotOpenEndWindow(int playerNumber) {
    QString information = "玩家" + QString::number(playerNumber + 1) + "胜利！";

    state = END;
    this->update();
    QMessageBox::information(this,"游戏结束！",information);
    keyRespondTimer->stop();
}
