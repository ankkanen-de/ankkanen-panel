#pragma once

#include <QObject>

class DesktopEntry : public QObject {
	Q_OBJECT

	Q_PROPERTY(QString entryPath READ entryPath)
	Q_PROPERTY(QString appId READ appId)
	Q_PROPERTY(QString type READ type)
	Q_PROPERTY(QString name READ name)
	Q_PROPERTY(QString genericName READ genericName)
	Q_PROPERTY(bool noDisplay READ noDisplay)
	Q_PROPERTY(QString comment READ comment)
	Q_PROPERTY(QString icon READ icon)
	Q_PROPERTY(bool hidden READ hidden)
	Q_PROPERTY(QList<QString> onlyShowIn READ onlyShowIn)
	Q_PROPERTY(QList<QString> notShowIn READ notShowIn)
	Q_PROPERTY(QString tryExec READ tryExec)
	Q_PROPERTY(QString exec READ exec)
	Q_PROPERTY(QString path READ path)
	Q_PROPERTY(bool terminal READ terminal)
	Q_PROPERTY(QList<QString> mimeTypes READ mimeTypes)
	Q_PROPERTY(QList<QString> categories READ categories)
	Q_PROPERTY(QList<QString> keywords READ keywords)
	Q_PROPERTY(QString URL READ URL)

    public:
	DesktopEntry(QString entryPath);
	~DesktopEntry();

	QString entryPath();
	QString appId();

	QString type();
	QString name();
	QString genericName();
	bool noDisplay();
	QString comment();
	QString icon();
	bool hidden();
	QList<QString> onlyShowIn();
	QList<QString> notShowIn();
	QString tryExec();
	QString exec();
	QString path();
	bool terminal();
	QList<QString> mimeTypes();
	QList<QString> categories();
	QList<QString> keywords();
	QString URL();

	bool tryExecExists();

	static DesktopEntry forAppId(QString appId);

    private:
	QString m_entryPath;
	QString m_type;
	QString m_name;
	QString m_genericName;
	bool m_noDisplay = false;
	QString m_comment;
	QString m_icon;
	bool m_hidden = false;
	QList<QString> m_onlyShowIn;
	QList<QString> m_notShowIn;
	QString m_tryExec;
	QString m_exec;
	QString m_path;
	bool m_terminal = false;
	QList<QString> m_mimeTypes;
	QList<QString> m_categories;
	QList<QString> m_keywords;
	QString m_URL;

	void parse();
};
