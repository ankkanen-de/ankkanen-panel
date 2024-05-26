#include "desktopentry.hpp"

#include <QDir>
#include <QFile>
#include <QStandardPaths>

DesktopEntry::DesktopEntry(QString entryPath)
{
	m_entryPath = entryPath;
	parse();
}

DesktopEntry::~DesktopEntry()
{
}

QString DesktopEntry::entryPath()
{
	return m_entryPath;
}

QString DesktopEntry::appId()
{
	return m_entryPath.split("/").last().split(".").first();
}

QString DesktopEntry::type()
{
	return m_type;
}

QString DesktopEntry::name()
{
	return m_name;
}

QString DesktopEntry::genericName()
{
	return m_genericName;
}

bool DesktopEntry::noDisplay()
{
	return m_noDisplay;
}

QString DesktopEntry::comment()
{
	return m_comment;
}

QString DesktopEntry::icon()
{
	return m_icon;
}

bool DesktopEntry::hidden()
{
	return m_hidden;
}

QList<QString> DesktopEntry::onlyShowIn()
{
	return m_onlyShowIn;
}

QList<QString> DesktopEntry::notShowIn()
{
	return m_notShowIn;
}

QString DesktopEntry::tryExec()
{
	return m_tryExec;
}

QString DesktopEntry::exec()
{
	return m_exec;
}

QString DesktopEntry::path()
{
	return m_path;
}

bool DesktopEntry::terminal()
{
	return m_terminal;
}

QList<QString> DesktopEntry::mimeTypes()
{
	return m_mimeTypes;
}

QList<QString> DesktopEntry::categories()
{
	return m_categories;
}

QList<QString> DesktopEntry::keywords()
{
	return m_keywords;
}

QString DesktopEntry::URL()
{
	return m_URL;
}

bool DesktopEntry::tryExecExists()
{
	if (QFile(m_tryExec).exists())
		return true;

	QList<QString> paths = QString(qgetenv("PATH")).split(':');
	foreach(QString path, paths) {
		if (QFile(path).exists(m_tryExec))
			return true;
	}

	return false;
}

DesktopEntry DesktopEntry::forAppId(QString appId)
{
	QList<QString> paths = QStandardPaths::standardLocations(
		QStandardPaths::ApplicationsLocation);

	foreach(QString path, paths) {
		QDir dir(path);
		if (dir.exists(appId + ".desktop"))
			return DesktopEntry(
				dir.absoluteFilePath(appId + ".desktop"));
	}

	return DesktopEntry("");
}

void DesktopEntry::parse()
{
	QFile file(m_entryPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);
	QString section;
	while (!in.atEnd()) {
		QString line = in.readLine();

		if (line.startsWith("[") && line.endsWith("]")) {
			section = line.mid(1, line.length() - 2);
		} else if (section == "Desktop Entry") {
			if (line.startsWith("Type="))
				m_type = line.mid(5);
			else if (line.startsWith("Name="))
				m_name = line.mid(5);
			else if (line.startsWith("GenericName="))
				m_genericName = line.mid(12);
			else if (line.startsWith("NoDisplay="))
				m_noDisplay = (line.mid(10) == "true");
			else if (line.startsWith("Comment="))
				m_comment = line.mid(8);
			else if (line.startsWith("Icon="))
				m_icon = line.mid(5);
			else if (line.startsWith("Hidden="))
				m_hidden = (line.mid(7) == "true");
			else if (line.startsWith("OnlyShowIn="))
				m_onlyShowIn = line.mid(11).split(";");
			else if (line.startsWith("NotShowIn="))
				m_notShowIn = line.mid(10).split(";");
			else if (line.startsWith("TryExec="))
				m_tryExec = line.mid(8);
			else if (line.startsWith("Exec="))
				m_exec = line.mid(5);
			else if (line.startsWith("Path="))
				m_path = line.mid(5);
			else if (line.startsWith("Terminal="))
				m_terminal = (line.mid(9) == "true");
			else if (line.startsWith("MimeType="))
				m_mimeTypes = line.mid(8).split(";");
			else if (line.startsWith("Categories="))
				m_categories = line.mid(11).split(";");
			else if (line.startsWith("Keywords="))
				m_keywords = line.mid(9).split(";");
			else if (line.startsWith("URL="))
				m_URL = line.mid(4);
		}
	}

	file.close();
}
