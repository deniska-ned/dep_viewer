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
    _restore_command_ptr = std::make_shared<restore_command>(this);
    _save_command_ptr = std::make_shared<save_command>(this);
    _showdata_command_ptr = std::make_shared<showdata_command>(this);
    _undo_command_ptr = std::make_shared<undo_command>(this);
    _update_command_ptr = std::make_shared<update_command>(this);

    _model_ptr = std::make_shared<TreeModel>();

    _ui->treeView->setModel(_model_ptr.get());
}

mainwindow::~mainwindow()
{ }

std::vector<department> mainwindow::get_table_data()
{
    qDebug("called");
    // TODO: implement method

    std::vector<department> tmp;
    return tmp;
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
        cmdhistory_manager_creator().get_manager()->add_new(cmd);
}

void mainwindow::on_actionOpen_triggered()
{
    qDebug("clicked");

    execute_command(_load_command_ptr);
}

void mainwindow::on_actionSave_triggered()
{
    qDebug("clicked");

    execute_command(_save_command_ptr);
}
