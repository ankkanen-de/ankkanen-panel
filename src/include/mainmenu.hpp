#pragma once

#include <QDialog>

namespace Ui
{
class MainMenu;
}

class MainMenu : public QDialog {
	Q_OBJECT

    public:
	explicit MainMenu(QWidget *parent = nullptr);
	~MainMenu();

    private slots:
	void launchTerminal();

    private:
	Ui::MainMenu *ui;
};
