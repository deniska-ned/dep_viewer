#include "treemodel.h"
#include "treeitem.h"

#include <QtWidgets>

#define DEP_COL_COUNT   3
#define EMP_COL_COUNT   3

#define ROOT_DEPTH      0
#define DEPA_DEPTH      1
#define EMPL_DEPTH      2


TreeModel::TreeModel(std::shared_ptr<std::vector<department>> dep_ptr)
{
    setVectorDataAsTree(dep_ptr);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    int res = 0;

    switch (getDepth(parent))
    {
        case ROOT_DEPTH:
        case DEPA_DEPTH:
        case EMPL_DEPTH:
            res = 3;
            break;
        default:
            res = 0;
    }

    return res;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    int depth = getDepth(index);

    if (DEPA_DEPTH == depth && 1 == index.column()) {
        TreeItem *dep = getItem(index);
        int emp_count = dep->childCount();
        return QVariant(emp_count);
    }
    else if (DEPA_DEPTH == depth && 2 == index.column())
    {
        TreeItem *dep = getItem(index);
        double avg_salary = dep->countAvgSalary();
        return QVariant(avg_salary);
    }
    else
    {
        TreeItem *item = getItem(index);
        return item->data(index.column());
    }
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (DEPA_DEPTH == getDepth(index)
            && (1 == index.column() || 2 == index.column()))
        return QAbstractItemModel::flags(index);
    else
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows,
                                                    rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem ? childItem->parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    int res = 0;

    const TreeItem *parentItem = getItem(parent);

    res = parentItem ? parentItem->childCount() : 0;

    return res;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    int depth = getDepth(index);
    bool result = false;
    bool shouldBackup = false;

    TreeItem *item = getItem(index);

    if (EMPL_DEPTH == depth && 0 == index.column()
        && 3 != value.toString().split(" ").count())
    // TODO: make check more strict
    {
        qInfo("Surname name middlename should be writted as 3 separated words");
        // return the previous data
        result = item->setData(index.column(), item->data(index.column()));
        shouldBackup = false;
    }
    else if (EMPL_DEPTH == depth && 2 == index.column())
    {
        result = item->setData(index.column(), value);
        shouldBackup = result;

        if (result)
        {
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
            emit dataChanged(index.parent().siblingAtRow(2),
                             index.parent().siblingAtRow(2),
                             {Qt::DisplayRole});
        }
    }
    else
    {
        result = item->setData(index.column(), value);
        shouldBackup = result;

        if (result)
        {
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        }
    }

    if (shouldBackup)
        emit treeUpdated();

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    const bool result = rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

void TreeModel::setVectorDataAsTree(
        std::shared_ptr<std::vector<department>> dep_ptr)
{
    delete rootItem;
    rootItem = new TreeItem({ "Наим. подр. / ФИО",
                              "Кол-во сотр. / Должность",
                              "Ср. зарплата / Зарплата"
                            });

    if (nullptr == dep_ptr)
        return;

    for (int dep_i = 0; dep_i < dep_ptr->size(); ++dep_i)
    {
        department const& dep = dep_ptr->at(dep_i);

        rootItem->insertChildren(dep_i, 1, DEP_COL_COUNT);
        TreeItem *dep_item_ptr = rootItem->child(dep_i);

        QVariant dep_name(QString::fromStdString(dep.name()));
        QVariant dep_emp_count((uint) dep.employment_count());
        QVariant dep_avg_salary(dep.avg_salary());

        dep_item_ptr->setData(0, dep_name);
        dep_item_ptr->setData(1, dep_emp_count);
        dep_item_ptr->setData(2, dep_avg_salary);

        for (int emp_i = 0; emp_i < dep.employment_count(); ++emp_i)
        {
            employment const& emp = dep.get_employment(emp_i);

            dep_item_ptr->insertChildren(emp_i, 1, EMP_COL_COUNT);
            TreeItem *emp_item_ptr = dep_item_ptr->child(emp_i);

            QVariant snm(QString::fromStdString(
                    emp.surname() + " "
                    + emp.name() + " "
                    + emp.middle_name()));
            QVariant function(QString::fromStdString(emp.function()));
            QVariant salary(emp.salary());

            emp_item_ptr->setData(0, snm);
            emp_item_ptr->setData(1, function);
            emp_item_ptr->setData(2, salary);
        }
    }

    emit layoutChanged();
}

std::shared_ptr<std::vector<department>> TreeModel::getTreeDataAsVector()
{
    auto departments_ptr = std::make_shared<std::vector<department>>();

    for (int dep_i = 0; dep_i < rootItem->childCount(); ++dep_i)
    {
        TreeItem *dep_item_ptr = rootItem->child(dep_i);

        std::string dep_name = dep_item_ptr->data(0).toString().toStdString();
        department dep(dep_name);
        std::vector<employment> employments;

        for (int emp_i = 0; emp_i < dep_item_ptr->childCount(); ++emp_i)
        {
            TreeItem *emp_item_ptr = dep_item_ptr->child(emp_i);

            auto emp_snm_l = emp_item_ptr->data(0).toString().split(" ");
            std::string emp_surname = (emp_snm_l.count() > 0 ?
                                       emp_snm_l[0].toStdString() : "");
            std::string emp_name = (emp_snm_l.count() > 1 ?
                                    emp_snm_l[1].toStdString() : "");
            std::string emp_middlename = (emp_snm_l.count() > 2 ?
                                          emp_snm_l[2].toStdString() : "");

            std::string emp_function = emp_item_ptr->data(1).toString().toStdString();
            int emp_salary = emp_item_ptr->data(2).toInt();

            employments.emplace_back(emp_surname, emp_name, emp_middlename,
                                     emp_function, emp_salary);
        }

        dep.replace_employments(employments.begin(), employments.end());

        departments_ptr->push_back(dep);
    }

    return departments_ptr;
}

int TreeModel::getDepth(QModelIndex index) const
{
    int depth = 0;

    while (QModelIndex() != index)
    {
        index = index.parent();
        ++depth;
    }

    return depth;
}
