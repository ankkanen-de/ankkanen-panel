#include "mainwindow.hpp"
#include "mainmenu.hpp"
#include "./ui/ui_mainwindow.h"

#include <QScreen>
#include <QWindow>
#include <LayerShellQt/window.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MainWindow)
	, m_foreignToplevelManager(new ForeignToplevelManagerV1)
{
	ui->setupUi(this);
	connect(ui->startButton, &QPushButton::clicked, this,
		&MainWindow::toggleMainMenu);

	connect(m_foreignToplevelManager,
		&ForeignToplevelManagerV1::toplevelAdded, this,
		&MainWindow::onToplevelAdded);
	connect(m_foreignToplevelManager,
		&ForeignToplevelManagerV1::toplevelRemoved, this,
		&MainWindow::onToplevelRemoved);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::prepare()
{
	m_mainMenu = new MainMenu();
	m_mainMenu->show();

	QWindow *qw = m_mainMenu->windowHandle();
	LayerShellQt::Window *layerShell = LayerShellQt::Window::get(qw);
	layerShell->setLayer(LayerShellQt::Window::LayerOverlay);
	layerShell->setAnchors((LayerShellQt::Window::Anchors)
				       LayerShellQt::Window::AnchorBottom |
			       LayerShellQt::Window::AnchorLeft);
	layerShell->setKeyboardInteractivity(
		LayerShellQt::Window::KeyboardInteractivityOnDemand);
	layerShell->setExclusiveZone(0);
	layerShell->setScope("ankkanen-panel");

	m_mainMenu->hide();
}

void MainWindow::onWindowHeightChanged(int h)
{
	QWindow *w = windowHandle();
	if (w)
		w->resize(screen()->availableSize().width(), targetHeight);
}

void MainWindow::toggleMainMenu()
{
	m_mainMenu->setVisible(!m_mainMenu->isVisible());
}

void MainWindow::onToplevelAdded(ForeignToplevelHandleV1 *toplevel)
{
	TaskButton *taskButton = new TaskButton(toplevel, this);
	ui->taskLayout->addWidget(taskButton);
	m_toplevelButtonMap.insert(toplevel, taskButton);
}

void MainWindow::onToplevelRemoved(ForeignToplevelHandleV1 *toplevel)
{
	TaskButton *taskButton = m_toplevelButtonMap[toplevel];
	if (!taskButton)
		return;
	delete taskButton;
	m_toplevelButtonMap.remove(toplevel);
}
