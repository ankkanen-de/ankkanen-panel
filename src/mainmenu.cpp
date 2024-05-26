#include "mainmenu.hpp"
#include "./ui/ui_mainmenu.h"

#include <QProcess>

MainMenu::MainMenu(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::MainMenu)
	, m_model(new ApplicationModel(this))
{
	ui->setupUi(this);
	ui->appTree->setModel(m_model);

	connect(ui->appTree, &QTreeView::clicked, this,
		&MainMenu::launchApplication);
}

MainMenu::~MainMenu()
{
	delete ui;
}

void MainMenu::launchApplication(const QModelIndex &index)
{
	setVisible(false);
	m_model->launchApplication(index);
}
