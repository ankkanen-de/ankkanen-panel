#include "taskbutton.hpp"

TaskButton::TaskButton(ForeignToplevelHandleV1 *handle, QWidget *parent)
	: QPushButton(parent)
	, m_handle(handle)
{
	setCheckable(true);
	onTitleChanged(m_handle->title());
	onStateChanged(m_handle->state());

	connect(this, &TaskButton::clicked, this, &TaskButton::onClicked);
	connect(m_handle, &ForeignToplevelHandleV1::titleChanged, this,
		&TaskButton::onTitleChanged);
	connect(m_handle, &ForeignToplevelHandleV1::stateChanged, this,
		&TaskButton::onStateChanged);
}

void TaskButton::onTitleChanged(QString title)
{
	setText(title);
}

void TaskButton::onStateChanged(QSet<ForeignToplevelHandleV1::State> state)
{
	setChecked(state.contains(ForeignToplevelHandleV1::Activated));
}

void TaskButton::onClicked()
{
	QSet<ForeignToplevelHandleV1::State> state = m_handle->state();
	if (state.contains(ForeignToplevelHandleV1::Activated))
		state << ForeignToplevelHandleV1::Minimized;
	else
		state << ForeignToplevelHandleV1::Activated;
	m_handle->setState(state);
}
