#pragma once
#include<QObject>
#include"command/playerCommand.h"

class CommandViewModel : public QObject{
	 Q_OBJECT
public slots:
    void commandSlots(int playerNum, int opr);
public:
	CommandViewModel()=default;
    void initial();
    inline Map* getMap(){ return map;}
    inline std::vector<playerCommand *> getPlayerControl(){ return playerControl;}
private:
	Map* map;
    std::vector<playerCommand *> playerControl;
}; 
