#include "applicationmodel.hpp"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QIcon>
#include <QProcess>

const QStringList ApplicationModel::categoryNames = {
	"Multimedia", "Development",  "Education", "Games",
	"Graphics",   "Internet",     "Office",	   "Science",
	"Settings",   "System Tools", "Utilities", "Other"
};

const QStringList ApplicationModel::categoryIds = {
	"AudioVideo", "Development", "Education", "Game",
	"Graphics",   "Network",     "Office",	  "Science",
	"Settings",   "System",	     "Utility"
};

const QStringList ApplicationModel::categoryIcons = {
	"applications-multimedia", "applications-development",
	"applications-education",  "applications-games",
	"applications-graphics",   "applications-internet",
	"applications-office",	   "applications-science",
	"applications-system",	   "applications-utilities",
	"applications-other"
};

ApplicationItem::ApplicationItem(DesktopEntry *entry, CategoryItem *parent)
	: m_entry(entry)
	, m_parent(parent)
{
}

ApplicationItem::~ApplicationItem()
{
	delete m_entry;
}

DesktopEntry *ApplicationItem::entry() const
{
	return m_entry;
}

CategoryItem *ApplicationItem::parent() const
{
	return m_parent;
}

int ApplicationItem::row() const
{
	if (m_parent)
		return m_parent->children().indexOf(
			const_cast<ApplicationItem *>(this));

	return 0;
}

CategoryItem::CategoryItem(Category category, ApplicationModel *model)
	: m_category(category)
	, m_model(model)
{
}

CategoryItem::~CategoryItem()
{
	qDeleteAll(m_children);
}

Category CategoryItem::category() const
{
	return m_category;
}

void CategoryItem::appendChild(ApplicationItem *child)
{
	m_children << child;
}

void CategoryItem::sortChildren()
{
	std::sort(m_children.begin(), m_children.end(),
		  [](ApplicationItem *a, ApplicationItem *b) {
			  return a->entry()->name() < b->entry()->name();
		  });
}

ApplicationItem *CategoryItem::child(int row) const
{
	return m_children.value(row);
}

int CategoryItem::childCount() const
{
	return m_children.count();
}

QList<ApplicationItem *> CategoryItem::children() const
{
	return m_children;
}

int CategoryItem::row() const
{
	if (m_model)
		return m_model->categories()->indexOf(this);

	return 0;
}

ApplicationModel::ApplicationModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	QList<QString> dirs = QStandardPaths::standardLocations(
		QStandardPaths::ApplicationsLocation);
	QString xdgCurrentDesktop = qgetenv("XDG_CURRENT_DESKTOP");

	foreach(QString dir, dirs) {
		QDir applicationsDir(dir);
		foreach(QString entry, applicationsDir.entryList(QDir::Files)) {
			if (entry.endsWith(".desktop")) {
				DesktopEntry *desktopEntry = new DesktopEntry(
					applicationsDir.absoluteFilePath(
						entry));
				if (desktopEntry->type() == "Application" &&
				    !desktopEntry->noDisplay() &&
				    !desktopEntry->hidden() &&
				    (desktopEntry->onlyShowIn().contains(
					     xdgCurrentDesktop) ||
				     desktopEntry->onlyShowIn().isEmpty()) &&
				    !desktopEntry->notShowIn().contains(
					    xdgCurrentDesktop) &&
				    !desktopEntry->tryExecExists()) {
					foreach(QString category,
						desktopEntry->categories()) {
						if (!categoryIds.contains(
							    category))
							continue;

						Category cat = static_cast<
							Category>(
							categoryIds.indexOf(
								category));

						CategoryItem *catItem = nullptr;
						foreach(CategoryItem *item,
							m_categories) {
							if (item->category() ==
							    cat) {
								catItem = item;
								break;
							}
						}

						if (!catItem) {
							catItem =
								new CategoryItem(
									cat,
									this);
							m_categories << catItem;
						}

						catItem->appendChild(
							new ApplicationItem(
								desktopEntry,
								catItem));
					}
				} else
					delete desktopEntry;
			}
		}
	}

	std::sort(m_categories.begin(), m_categories.end(),
		  [](CategoryItem *a, CategoryItem *b) {
			  return categoryNames.at(a->category()) <
				 categoryNames.at(b->category());
		  });

	foreach(CategoryItem *category, m_categories)
		category->sortChildren();
}

ApplicationModel::~ApplicationModel()
{
	qDeleteAll(m_categories);
}

QVariant ApplicationModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	CategoryItem *category = categoryItem(index);
	if (category) {
		switch (role) {
		case Qt::DisplayRole:
			return categoryNames.at(category->category());
		case Qt::DecorationRole:
			return QIcon::fromTheme(
				categoryIcons.at(category->category()));
		default:
			return QVariant();
		}
	}

	ApplicationItem *application = applicationItem(index);
	if (application) {
		switch (role) {
		case Qt::DisplayRole:
			return application->entry()->name();
		case Qt::DecorationRole:
			return QIcon::fromTheme(application->entry()->icon());
		default:
			return QVariant();
		}
	}

	return QVariant();
}

QVariant ApplicationModel::headerData(int section, Qt::Orientation orientation,
				      int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return "Applications";

	return QVariant();
}

QModelIndex ApplicationModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	ApplicationItem *application = applicationItem(index);
	if (application) {
		CategoryItem *category = application->parent();
		if (category)
			return createIndex(category->row(), 0, category);
	}

	return QModelIndex();
}

Qt::ItemFlags ApplicationModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex ApplicationModel::index(int row, int column,
				    const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	if (!parent.isValid()) {
		CategoryItem *category = m_categories.at(row);
		if (category)
			return createIndex(row, column, category);
	} else {
		CategoryItem *category = categoryItem(parent);
		if (category) {
			ApplicationItem *application = category->child(row);
			if (application)
				return createIndex(row, column, application);
		}
	}

	return QModelIndex();
}

int ApplicationModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		return m_categories.count();

	CategoryItem *category = categoryItem(parent);
	if (category) {
		return category->childCount();
	}
	return 0;
}

int ApplicationModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return 1;
}

QList<CategoryItem *> *ApplicationModel::categories()
{
	return &m_categories;
}

CategoryItem *ApplicationModel::categoryItem(const QModelIndex &index) const
{
	if (!index.isValid())
		return nullptr;

	return qobject_cast<CategoryItem *>((QObject *)index.internalPointer());
}

ApplicationItem *
ApplicationModel::applicationItem(const QModelIndex &index) const
{
	if (!index.isValid())
		return nullptr;

	return qobject_cast<ApplicationItem *>(
		(QObject *)index.internalPointer());
}

void ApplicationModel::launchApplication(const QModelIndex &index)
{
	ApplicationItem *application = applicationItem(index);
	if (application) {
		QString exec = application->entry()->exec();
		exec.replace("%f", "");
		exec.replace("%F", "");
		exec.replace("%u", "");
		exec.replace("%U", "");
		exec.replace("%%", "%");
		QStringList args;
		args << "-c";
		args << exec;

		QProcess::startDetached("sh", args,
					application->entry()->path());
	}
}
