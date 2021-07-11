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
}

mainwindow::~mainwindow()
{ }

std::shared_ptr<std::vector<department>> mainwindow::get_table_data()
{
    qDebug("called");

    return _model_ptr->getTreeDataAsVector();
}

void mainwindow::set_table_data(
        std::shared_ptr<std::vector<department>> departments)
{
    qDebug("called");

    auto new_model_ptr = std::make_shared<TreeModel>(departments);
    _ui->treeView->setModel(new_model_ptr.get());
    _model_ptr = new_model_ptr;
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

void mainwindow::on_actionInsertEmployer_triggered()
{
    qDebug("clicked");
    show_message("Not implemented");
}

void mainwindow::on_actionInsertDepartment_triggered()
{
    qDebug("clicked");
    show_message("Not implemented");
}

void mainwindow::onvaluechanged()
{
    qDebug("cell data changed");
    execute_command(_update_command_ptr);
}
