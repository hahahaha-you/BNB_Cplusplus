#ifndef WIDGET_H
#define WIDGET_H

#define BLOCK_SIDE_LENGTH 40

#include <QString>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include "../common/map.h"
#include "../command1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initialize();
    void setMap(Map *m) {map = m;this->update();}
protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void drawMap();
private:
    Ui::Widget *ui;
    Map *map;
    std::vector<character *> players;
};


#endif // WIDGET_H
