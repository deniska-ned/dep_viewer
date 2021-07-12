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
    _update_command_ptr = std::make_shared<update_command>(this);
    _save_command_ptr = std::make_shared<save_command>(this);
    _showdata_command_ptr = std::make_shared<showdata_command>(this);
    _undo_command_ptr = std::make_shared<undo_command>(this);
    _redo_command_ptr = std::make_shared<redo_command>(this);

    _model_ptr = std::make_shared<TreeModel>();

    _ui->treeView->setModel(_model_ptr.get());

    connect(_model_ptr.get(), &TreeModel::treeUpdated,
            this, &mainwindow::onvaluechanged);
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

    _model_ptr->setVectorDataAsTree(departments);
}

std::string mainwindow::get_load_filename()
{
    qDebug("called");

    QString qstr_filename = QFileDialog::getOpenFileName();

    std::string filename(qstr_filename.toUtf8().data());
    return filename;
}

std::string mainwindow::get_save_filename()
{
    qDebug("called");

    return _src_filename;
}

void mainwindow::set_save_filename(std::string const& filename)
{
    _src_filename = filename;
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
    execute_command(_save_command_ptr);
}

void mainwindow::on_actionUndo_triggered()
{
    qDebug("clicked");
    execute_command(_undo_command_ptr);
}

void mainwindow::on_actionRedo_triggered()
{
    qDebug("clicked");
    execute_command(_redo_command_ptr);
}

void mainwindow::on_actionInsertEmployer_triggered()
{
    qDebug("clicked");
    const QModelIndex index = _ui->treeView->selectionModel()->currentIndex();

    _model_ptr->insertEmployee(index);
}

void mainwindow::on_actionInsertDepartment_triggered()
{
    qDebug("clicked");
    const QModelIndex index = _ui->treeView->selectionModel()->currentIndex();

    _model_ptr->insertDepartment(index);
}

void mainwindow::onvaluechanged()
{
    qDebug("called");
    execute_command(_update_command_ptr);
}

void mainwindow::on_actionRemoveRow_triggered()
{
    qDebug("called");

    const QModelIndex index = _ui->treeView->selectionModel()->currentIndex();
    _model_ptr->removeRow(index.row(), index.parent());
}
