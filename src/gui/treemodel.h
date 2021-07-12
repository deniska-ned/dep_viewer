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
    TreeModel(std::shared_ptr<std::vector<department>> dep_ptr = nullptr);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool insertDepartment(QModelIndex curr_index);
    bool insertEmployee(QModelIndex curr_index);

    void setVectorDataAsTree(std::shared_ptr<std::vector<department>> dep_ptr);
    std::shared_ptr<std::vector<department>> getTreeDataAsVector();

signals:
    void treeUpdated();

private:
    TreeItem *getItem(const QModelIndex &index) const;
    int getDepth(QModelIndex index) const;

    TreeItem *rootItem = nullptr;
};

#endif // TREEMODEL_H
