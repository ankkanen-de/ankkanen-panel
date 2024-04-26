#pragma once

#include <QWidget>
#include <qt6-foreign-toplevel-management.h>

#include "taskbutton.hpp"

class MainMenu;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QWidget {
	Q_OBJECT

    public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void prepare();

	int targetHeight = 32;

    public slots:
	void onWindowHeightChanged(int h);
	void toggleMainMenu();

    private slots:
	void onToplevelAdded(ForeignToplevelHandleV1 *toplevel);
	void onToplevelRemoved(ForeignToplevelHandleV1 *toplevel);

    private:
	Ui::MainWindow *ui;
	MainMenu *m_mainMenu;
	ForeignToplevelManagerV1 *m_foreignToplevelManager;
	QMap<ForeignToplevelHandleV1 *, TaskButton *> m_toplevelButtonMap;
};
