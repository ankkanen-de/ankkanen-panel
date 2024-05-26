#pragma once

#include <QPushButton>
#include <qt6-foreign-toplevel-management.h>

class TaskButton : public QPushButton {
	Q_OBJECT

    public:
	TaskButton(ForeignToplevelHandleV1 *handle, QWidget *parent = nullptr);

    private slots:
	void onTitleChanged(QString title);
	void onStateChanged(QSet<ForeignToplevelHandleV1::State> state);
	void onAppIdChanged(QString appId);
	void onClicked();

    private:
	ForeignToplevelHandleV1 *m_handle;
};
