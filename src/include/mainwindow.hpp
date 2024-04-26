#pragma once

#include <QWidget>

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

    private:
	Ui::MainWindow *ui;
	MainMenu *m_mainMenu;
};
