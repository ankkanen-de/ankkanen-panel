#include "mainmenu.hpp"
#include "./ui/ui_mainmenu.h"

#include <QProcess>

MainMenu::MainMenu(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::MainMenu)
{
	ui->setupUi(this);
	connect(ui->testButton, &QPushButton::clicked, this,
		&MainMenu::launchTerminal);
}

MainMenu::~MainMenu()
{
	delete ui;
}

void MainMenu::launchTerminal()
{
	setVisible(false);
	QProcess::startDetached("konsole");
}
