#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "cmdhistory_manager_creator.h"
#include "errors.hpp"
#include "treemodel.h"


mainwindow::mainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::mainwindow)
{
    ui_->setupUi(this);

    load_command_ptr_ = std::make_shared<load_command>(this);
    update_command_ptr_ = std::make_shared<update_command>(this);
    save_command_ptr_ = std::make_shared<save_command>(this);
    showdata_command_ptr_ = std::make_shared<showdata_command>(this);
    undo_command_ptr_ = std::make_shared<undo_command>(this);
    redo_command_ptr_ = std::make_shared<redo_command>(this);

    model_ptr_ = std::make_shared<TreeModel>();

    ui_->treeView->setModel(model_ptr_.get());

    connect(model_ptr_.get(), &TreeModel::cellUpdatedByUser,
            this, &mainwindow::react_to_user_cell_changes);

    execute_command(update_command_ptr_);
}

mainwindow::~mainwindow()
{ }

std::shared_ptr<std::vector<department>> mainwindow::get_table_data()
{
    qDebug("called");

    return model_ptr_->getAllData();
}

void mainwindow::set_table_data(
        std::shared_ptr<std::vector<department>> departments)
{
    qDebug("called");

    model_ptr_->replaceAllData(departments);
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

    return src_filename_;
}

void mainwindow::set_save_filename(std::string const& filename)
{
    src_filename_ = filename;
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

void mainwindow::react_to_user_cell_changes()
{
    qDebug("called");
    execute_command(update_command_ptr_);
}

void mainwindow::on_actionOpen_triggered()
{
    qDebug("clicked");

    execute_command(load_command_ptr_);
}

void mainwindow::on_actionSave_triggered()
{
    qDebug("clicked");
    execute_command(save_command_ptr_);
}

void mainwindow::on_actionUndo_triggered()
{
    qDebug("clicked");
    execute_command(undo_command_ptr_);
}

void mainwindow::on_actionRedo_triggered()
{
    qDebug("clicked");
    execute_command(redo_command_ptr_);
}

void mainwindow::on_actionInsertEmployer_triggered()
{
    qDebug("clicked");
    const QModelIndex index = ui_->treeView->selectionModel()->currentIndex();

    model_ptr_->insertEmployee(index);

    execute_command(update_command_ptr_);
}

void mainwindow::on_actionInsertDepartment_triggered()
{
    qDebug("clicked");
    const QModelIndex index = ui_->treeView->selectionModel()->currentIndex();

    model_ptr_->insertDepartment(index);

    execute_command(update_command_ptr_);
}

void mainwindow::on_actionRemoveRow_triggered()
{
    qDebug("called");

    const QModelIndex index = ui_->treeView->selectionModel()->currentIndex();
    model_ptr_->removeRow(index.row(), index.parent());

    execute_command(update_command_ptr_);
}
