#pragma once
#include<QObject>
#include"command/playercommand.h"
#include"command/laser.h"

class CommandViewModel : public QObject{
	 Q_OBJECT
public slots:
    void commandSlots(int playerNum, int opr);
public:
    CommandViewModel()=default;
    void initial();
    inline Map* getMap(){ return map;}
    inline std::vector<playerCommand *> getPlayerControl(){ return playerControl;}
    std::vector<Laser *> getPlayerWeapons() {return playerWeapons;}
private:
	Map* map;
    std::vector<playerCommand *> playerControl;
    std::vector<Laser *> playerWeapons;
}; 
