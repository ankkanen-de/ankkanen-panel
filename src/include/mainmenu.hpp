#pragma once

#include "applicationmodel.hpp"

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
	void launchApplication(const QModelIndex &index);

    private:
	Ui::MainMenu *ui;
	ApplicationModel *m_model;
};
