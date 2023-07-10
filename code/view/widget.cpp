#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    drawMap();
}

void Widget::initialize()
{
    setFixedSize(1280,720);
    setWindowTitle("泡泡堂");
}

void Widget::drawMap()
{
    QPainter painter(this);
    QPixmap blockPicture("../../pictures/2BLOCKBG.png");
    QPixmap bombPicture("../../pictures/bomb.png");
    QPixmap boxPicture("../../pictures/2BLOCKBLACK.png");
    QPixmap stonePicture("../../pictures/2BLOCKYELLOW.png");
    QPixmap explosionPicture("../../pictures/explode0.png");
    std::vector<QPixmap> playersPictures;
    block *aBlock;
    int rowNumber = map->getRowSize();
    int columnNumber = map->getColumnSize();
    int x,y;
    int rowIndex,columnIndex;

    for (columnIndex = 0; columnIndex < columnNumber; ++columnIndex) {
        x = BLOCK_SIDE_LENGTH * (1 + columnIndex);
        for (rowIndex = 0; rowIndex < rowNumber; ++rowIndex) {
            y = BLOCK_SIDE_LENGTH * (rowIndex + 1);
            aBlock = map->getBlock(columnIndex,rowIndex);
            switch (aBlock->getType()) {
            case ROAD:
                painter.drawPixmap(x, y, BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, blockPicture);
                break;
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
            default:
                break;
            }
        }
    }

    for (quint64 i = 0; i < players.size(); ++i) {
        QString playerName = "player" + QString::number(i);
        playersPictures.push_back(QPixmap("../../pictures/" + playerName + ".png"));
        double characterX = players[i]->getCoordinate().first;
        double characterY = players[i]->getCoordinate().second;
        painter.drawPixmap((characterX + 1) * BLOCK_SIDE_LENGTH, (characterY + 1) * BLOCK_SIDE_LENGTH,
            BLOCK_SIDE_LENGTH + 1, BLOCK_SIDE_LENGTH + 1, playersPictures[i]);
    }
        
    
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A : 
        players[0]->updateOperation(TURN_LEFT);
        break;
    case Qt::Key_S :
        players[0]->updateOperation(TURN_DOWN);
        break;
    case Qt::Key_W :
        players[0]->updateOperation(TURN_UP);
        break;
    case Qt::Key_D :
        players[0]->updateOperation(TURN_RIGHT);
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A :
    case Qt::Key_S :
    case Qt::Key_W :
    case Qt::Key_D :
        players[0]->updateOperation(INVALID_OPERATION);
        break;
    }
}