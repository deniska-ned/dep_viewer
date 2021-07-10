#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "cmdhistory_manager_creator.h"
#include "errors.hpp"
#include "treemodel.h"


mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , _ui(new Ui::mainwindow)
{
    _ui->setupUi(this);

    _load_command_ptr = std::make_shared<load_command>(this);
    _restore_command_ptr = std::make_shared<redo_command>(this);
    _save_command_ptr = std::make_shared<save_command>(this);
    _showdata_command_ptr = std::make_shared<showdata_command>(this);
    _undo_command_ptr = std::make_shared<undo_command>(this);
    _update_command_ptr = std::make_shared<update_command>(this);

    _model_ptr = std::make_shared<TreeModel>();

    _ui->treeView->setModel(_model_ptr.get());



    connect(_model_ptr.get(), &QAbstractItemModel::dataChanged ,
            this, &mainwindow::onvaluechanged);
}

mainwindow::~mainwindow()
{ }

std::vector<department> mainwindow::get_table_data()
{
    qDebug("called");

    std::vector<department> departments;

    auto dep_index = _model_ptr->index(0, 0);

    for ( size_t dep_row_i = 0;
          dep_index.isValid();
          ++dep_row_i, dep_index = dep_index.siblingAtRow(dep_row_i))
    {
        QString q_dep_name = _model_ptr->data(dep_index, Qt::DisplayRole).toString();
        std::string dep_name = q_dep_name.toStdString();

        department dep(dep_name);

        std::vector<employment> employments;

        auto emp_index = _model_ptr->index(0, 0, dep_index);
        for (size_t emp_row_i = 0;
             emp_index.isValid();
             ++emp_row_i, emp_index = emp_index.siblingAtRow(emp_row_i))
        {
            QString q_emp_snm = _model_ptr->data(emp_index.siblingAtColumn(0), Qt::DisplayRole).toString();

            // TODO: recode
            QStringList l = q_emp_snm.split(" ");
            std::string surname = l.count() >= 1 ? l[0].toStdString() : "surname";
            std::string name = l.count() >= 2 ? l[1].toStdString() : "name";
            std::string middlename = l.count() >= 3 ? l[2].toStdString(): "middlename";

            std::string function = _model_ptr->data(emp_index.siblingAtColumn(1), Qt::DisplayRole).toString().toStdString();
            int salary = _model_ptr->data(emp_index.siblingAtColumn(2), Qt::DisplayRole).toInt();

            employment new_empl(surname, name, middlename, function, salary);

            employments.push_back(new_empl);
        }

        dep.replace_employments(employments.begin(), employments.end());

        departments.push_back(dep);
    };

    return departments;
}

void mainwindow::set_table_data(const std::vector<department> &departments)
{
    qDebug("called");

    _model_ptr = std::make_shared<TreeModel>();

    const QModelIndex index = _ui->treeView->selectionModel()->currentIndex();

    _model_ptr->insertRows(0, departments.size(), index);

    for (size_t i = 0; i < departments.size(); ++i)
    {
        auto const& dep = departments[i];

        QModelIndex dep_index = _model_ptr->index(i, 0, index);

        QVariant dep_name(QString::fromStdString(dep.name()));
        QVariant dep_empl_count((const unsigned) dep.employment_count());
        QVariant dep_avg_salary(dep.avg_salary());

        _model_ptr->setData(dep_index.siblingAtColumn(0), dep_name);
        _model_ptr->setData(dep_index.siblingAtColumn(1), dep_empl_count);
        _model_ptr->setData(dep_index.siblingAtColumn(2), dep_avg_salary);

        _model_ptr->insertRows(0, dep.employment_count(), dep_index);

        for (size_t j = 0; j < dep.employment_count(); ++j)
        {
            auto const& empl = dep.get_employment(j);

            QModelIndex empl_index = _model_ptr->index(j, 0, dep_index);

            QVariant empl_snm(QString::fromStdString(
                    empl.surname() + " " + empl.name()
                    + " " + empl.middle_name()
            ));
            QVariant empl_func(QString::fromStdString(empl.function()));
            QVariant empl_salary(empl.salary());

            _model_ptr->setData(empl_index.siblingAtColumn(0), empl_snm);
            _model_ptr->setData(empl_index.siblingAtColumn(1), empl_func);
            _model_ptr->setData(empl_index.siblingAtColumn(2), empl_salary);
        }
    }

    _ui->treeView->setModel(_model_ptr.get());


    connect(_model_ptr.get(), &QAbstractItemModel::dataChanged ,
            this, &mainwindow::onvaluechanged);
}

std::string mainwindow::get_load_filename()
{
    qDebug("called");

    QString filename = QFileDialog::getOpenFileName();

    if (filename.isEmpty())
    {
        show_message("File is not selected");
        throw app_filename_not_selected();
    }
    else
    {
        std::string s_filename(filename.toUtf8().data());
        return s_filename;
    }
}

std::string mainwindow::get_save_filename()
{
    qDebug("called");

    if (_src_filename.empty())
        throw app_table_not_loaded();

    return _src_filename;
}

void mainwindow::show_message(std::string const& mes)
{
    qDebug("called");

    QMessageBox box;
    box.setText(QString::fromStdString(mes));
    box.exec();
}

void mainwindow::execute_command(std::shared_ptr<base_command> cmd)
{
    if (cmd->execute())
    {
        auto history_man_ptr = cmdhistory_manager_creator().get_manager();
        history_man_ptr->add_new(cmd);
    }
}

void mainwindow::on_actionOpen_triggered()
{
    qDebug("clicked");

    execute_command(_load_command_ptr);
}

void mainwindow::on_actionSave_triggered()
{
    qDebug("clicked");

    show_message("Not implemented");
    // execute_command(_save_command_ptr);
}

void mainwindow::on_actionUndo_triggered()
{
    qDebug("clicked");
    execute_command(_undo_command_ptr);
}

void mainwindow::on_actionRedo_triggered()
{
    qDebug("clicked");
    execute_command(_restore_command_ptr);
}

void mainwindow::onvaluechanged()
{
    qDebug("cell data changed");
    execute_command(_update_command_ptr);
}

void mainwindow::_insert_empl()
{
    const QModelIndex index = _ui->treeView->selectionModel()->currentIndex();
    QModelIndex empl_index;

    if (!index.isValid()) // root item
    {
        this->show_message("Choose department first");
        return;
    }
    else if (!_model_ptr->parent(index).isValid()) // index on dep row
    {
        _model_ptr->insertRow(0, index);
        empl_index = _model_ptr->index(0, 0, index);
    }
    else // index on emp row
    {
        _model_ptr->insertRow(index.row() + 1, index.parent());
        empl_index = _model_ptr->index(index.row() + 1, 0, index.parent());
    }

    _model_ptr->setData(_model_ptr->index(0, 0, empl_index.parent()),
                        QVariant(QString("surname name middlename")));
}

void mainwindow::on_actionInsertEmployer_triggered()
{
    qDebug("clicked");
    _insert_empl();
}

void mainwindow::on_actionInsertDepartment_triggered()
{
    qDebug("clicked");
    show_message("Not implemented");
}

/*
void mainwindow::insert_child()
{
    const QModelIndex index = _ui->treeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = _ui->treeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        const QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }

    view->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

void MainWindow::insertRow()
{
    const QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        const QModelIndex child = model->index(index.row() + 1, column, index.parent());
        model->setData(child, QVariant(tr("[No data]")), Qt::EditRole);
    }
}

void MainWindow::removeRow()
{
    const QModelIndex index = view->selectionModel()->currentIndex();
    QAbstractItemModel *model = view->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}
*/
