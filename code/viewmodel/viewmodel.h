#pragma once
#include<QObject>
#include"command/playercommand.h"
#include"command/propcommand.h"

class CommandViewModel : public QObject{
	 Q_OBJECT
public slots:
    void commandSlots(int playerNum, int opr);
public:
    CommandViewModel()=default;
    void initial();
    inline Map* getMap(){ return map;}
    inline std::vector<PlayerCommand *> getPlayerControl(){ return playerControl;}
    std::vector<PropCommand *> getPlayerWeapons() {return playerWeapons;}
private:
	Map* map;
    std::vector<PlayerCommand *> playerControl;
    std::vector<PropCommand *> playerWeapons;
}; 
