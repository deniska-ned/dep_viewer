#include "treemodel.h"
#include "treeitem.h"

#include <QtWidgets>
#include <QRegularExpression>

#define DEP_COL_COUNT   3
#define EMP_COL_COUNT   3

#define ROOT_DEPTH      0
#define DEPA_DEPTH      1
#define EMPL_DEPTH      2


TreeModel::TreeModel(std::shared_ptr<std::vector<department>> dep_ptr)
{
    rootItem = new TreeItem({ "Наим. подр. / ФИО",
                              "Кол-во сотр. / Должность",
                              "Ср. зарплата / Зарплата"
                            });

    replaceAllData(dep_ptr);
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

    if (item->data(index.column()) == value)
    {
        return false;
    }

    if (EMPL_DEPTH == depth && 0 == index.column())
    {
        QRegularExpression re(R"(^(?<surname>\w+) (?<name>\w+) (?<middlename>\w+$))",
                              QRegularExpression::UseUnicodePropertiesOption);

        if (re.match(value.toString()).hasMatch())
        {
            result = item->setData(index.column(), value);
            shouldBackup = true;
        }
        else
        {
            qInfo("Surname name middlename should be writted as 3 separated words");
            // return the previous data
            result = item->setData(index.column(), item->data(index.column()));
            shouldBackup= false;
        }

        if (result)
        {
            emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        }
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
        emit cellUpdatedByUser();

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

void TreeModel::replaceAllData(
        std::shared_ptr<std::vector<department>> dep_ptr)
{
    removeRows(0, rowCount(QModelIndex()), QModelIndex());

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
            QVariant salary((uint) emp.salary());

            emp_item_ptr->setData(0, snm);
            emp_item_ptr->setData(1, function);
            emp_item_ptr->setData(2, salary);
        }
    }
}

std::shared_ptr<std::vector<department>> TreeModel::getAllData()
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

            QRegularExpression re(R"(^(?<surname>\w+) (?<name>\w+) (?<middlename>\w+$))",
                                  QRegularExpression::UseUnicodePropertiesOption);

            std::string emp_surname, emp_name, emp_middlename;

            auto match = re.match(emp_item_ptr->data(0).toString());

            if (match.hasMatch())
            {
                emp_surname = match.captured("surname").toStdString();
                emp_name = match.captured("name").toStdString();
                emp_middlename = match.captured("middlename").toStdString();
            }
            else
            {
                emp_surname = std::string("-");
                emp_name = std::string("-");
                emp_middlename = std::string("-");
            }

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

bool TreeModel::insertDepartment(QModelIndex curr_index)
{
    bool res = false;
    int depth = getDepth(curr_index);

    if (ROOT_DEPTH == depth || DEPA_DEPTH == depth || EMPL_DEPTH == depth)
    {
        TreeItem *item = nullptr;

        if (ROOT_DEPTH == depth)
        {
            res = insertRows(0, 1, curr_index);

            item = getItem(index(0, 0, QModelIndex()));
        }
        else if (DEPA_DEPTH == depth)
        {
            res = insertRows(curr_index.row() + 1, 1, curr_index.parent());

            item = getItem(index(curr_index.row() + 1, 0,
                                 curr_index.parent()));
        }
        else if (EMPL_DEPTH == depth)
        {
            res = insertRows(curr_index.parent().row() + 1, 1,
                             curr_index.parent().parent());

            item = getItem(index(curr_index.parent().row() + 1, 0,
                                 curr_index.parent().parent()));
        }
        if (nullptr != item)
            item->setData(0, QVariant(QString("Название подразделения")));
    }

    return res;
}

bool TreeModel::insertEmployee(QModelIndex curr_index)
{
    bool res = false;
    int depth = getDepth(curr_index);

    if (DEPA_DEPTH == depth || EMPL_DEPTH == depth)
    {
        TreeItem *item = nullptr;

        if (DEPA_DEPTH == depth)
        {
            res = insertRows(0, 1, curr_index);
            item = getItem(index(0, 0, curr_index));
        }
        else if (EMPL_DEPTH == depth)
        {
            res = insertRows(curr_index.row() + 1, 1, curr_index.parent());
            item = getItem( curr_index.sibling(curr_index.row() + 1, 0));
        }

        if (nullptr != item)
        {
            item->setData(0, QVariant(QString("Фамилия Имя Отчество")));
            item->setData(1, QVariant(QString("Должность")));
            item->setData(2, QVariant((uint) 0));
        }
    }

    return res;
}
