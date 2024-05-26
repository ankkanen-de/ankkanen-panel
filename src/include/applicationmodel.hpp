#pragma once

#include "desktopentry.hpp"

#include <QAbstractItemModel>

class CategoryItem;
class ApplicationModel;

enum Category {
	AudioVideo,
	Development,
	Education,
	Game,
	Graphics,
	Network,
	Office,
	Science,
	Settings,
	System,
	Utility,
	Unknown
};

class ApplicationItem : public QObject {
	Q_OBJECT

    public:
	ApplicationItem(DesktopEntry *entry, CategoryItem *parent = nullptr);
	~ApplicationItem();

	DesktopEntry *entry() const;
	CategoryItem *parent() const;
	int row() const;

    private:
	DesktopEntry *m_entry;
	CategoryItem *m_parent;
};

class CategoryItem : public QObject {
	Q_OBJECT

    public:
	CategoryItem(Category category, ApplicationModel *model = nullptr);
	~CategoryItem();

	Category category() const;
	void appendChild(ApplicationItem *child);
	void sortChildren();
	ApplicationItem *child(int row) const;
	int childCount() const;
	QList<ApplicationItem *> children() const;
	int row() const;

    private:
	Category m_category;
	QList<ApplicationItem *> m_children;
	ApplicationModel *m_model;
};

class ApplicationModel : public QAbstractItemModel {
	Q_OBJECT

    public:
	Q_DISABLE_COPY_MOVE(ApplicationModel)

	explicit ApplicationModel(QObject *parent = nullptr);
	~ApplicationModel() override;

	QVariant data(const QModelIndex &index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation,
			    int role = Qt::DisplayRole) const override;
	QModelIndex parent(const QModelIndex &index) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;
	QModelIndex index(int row, int column,
			  const QModelIndex &parent = {}) const override;
	int rowCount(const QModelIndex &parent = {}) const override;
	int columnCount(const QModelIndex &parent = {}) const override;

	QList<CategoryItem *> *categories();

	CategoryItem *categoryItem(const QModelIndex &index) const;
	ApplicationItem *applicationItem(const QModelIndex &index) const;

	void launchApplication(const QModelIndex &index);

	static const QStringList categoryNames;
	static const QStringList categoryIds;
	static const QStringList categoryIcons;

    private:
	QList<CategoryItem *> m_categories;
};
