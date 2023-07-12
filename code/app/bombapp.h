#ifndef BOMBAPP_H
#define BOMBAPP_H

#include "../view/mainwindow.h"
#include "../viewmodel/commandviewmodel.h"

class BombApp
{
public:
    BombApp() {};
    ~BombApp() throw() {};

    bool initialize();
    void show();
private:
    MainWindow *window;
    CommandViewModel *viewModel;
};

#endif // BOMBAPP_H
