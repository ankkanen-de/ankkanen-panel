#include "mainmenu.hpp"
#include "./ui/ui_mainmenu.h"

#include <QScreen>
#include <QWindow>

MainMenu::MainMenu(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::MainMenu)
{
	ui->setupUi(this);
}

MainMenu::~MainMenu()
{
	delete ui;
}
