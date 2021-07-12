#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <memory>

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "treeitem.h"
#include "department.hpp"


class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(
            std::shared_ptr<std::vector<department>> dep_ptr = nullptr);
    ~TreeModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent) override;
    bool insertDepartment(QModelIndex curr_index);
    bool insertEmployee(QModelIndex curr_index);

    void replaceAllData(std::shared_ptr<std::vector<department>> dep_ptr);
    std::shared_ptr<std::vector<department>> getAllData();

signals:
    void cellUpdatedByUser();

private:
    TreeItem *rootItem = nullptr;

    TreeItem *getItem(const QModelIndex &index) const;
    int getDepth(QModelIndex index) const;
};

#endif // TREEMODEL_H
