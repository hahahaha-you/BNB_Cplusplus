#include "bombapp.h"

bool BombApp::initialize()
{
    viewModel = new CommandViewModel();
    viewModel->initial();
    window = new MainWindow(viewModel->getMap(),viewModel->getPlayerControl()[0]->getPlayer(),viewModel->getPlayerControl()[1]->getPlayer());
    window->initialize();
    QObject::connect(window,SIGNAL(sendCommand(int,int)),viewModel,SLOT(commandSlots(int,int)));
}

void BombApp::show()
{
    window->show();
}
