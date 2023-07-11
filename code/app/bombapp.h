#ifndef BOMBAPP_H
#define BOMBAPP_H

#include "../view/mainwindow.h"
#include "../viewmodel/viewmodelcommand.h"

class BombApp
{
public:
    BombApp() {};
    ~BombApp() throw() {};

    bool initialize();
    void show();
private:
    MainWindow *window;
    Map *map;
    std::vector<Character *> players;
    std::vector<playerCommand *> commands;
};

#endif // BOMBAPP_H
