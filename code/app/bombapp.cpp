#include "bombapp.h"

bool BombApp::initialize()
{
    map = new Map();
    map->initial();
    Character *player1,*player2;
    player1 = new Character(std::make_pair<double>(0,0),0.07);
    player2 = new Character(std::make_pair<double>(11,11),0.07);

    players.push_back(player1);
    players.push_back(player2);
    for (int i = 0; i < players.size(); ++i)
        commands.push_back(new playerCommand(players[i],map));
    window = new MainWindow(map,commands[0]->getPlayer(),commands[1]->getPlayer());
    window->initialize();
    bool flag = QObject::connect(window,SIGNAL(player1CommandSignal(int)),commands[0],SLOT(commandSlots(int)));
    flag = QObject::connect(window,SIGNAL(player2CommandSignal(int)),commands[1],SLOT(commandSlots(int)));
}

void BombApp::show()
{
    window->show();
}
