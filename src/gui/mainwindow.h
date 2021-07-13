#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <memory>

#include <QMainWindow>

#include "i_tableowner.h"

#include "new_file_command.h"
#include "load_command.h"
#include "redo_command.h"
#include "save_command.h"
#include "save_as_command.h"
#include "showdata_command.h"
#include "undo_command.h"
#include "update_command.h"
#include "treemodel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow, public i_tableowner
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() override;

    std::shared_ptr<std::vector<department>> get_table_data() override;
    void set_table_data(
            std::shared_ptr<std::vector<department>> departments) override;

    std::string get_opened_filename() override;
    void set_opened_filename(std::string const& new_filename) override;
    std::string get_new_open_filename() override;
    std::string get_new_save_filename() override;

    void show_message(std::string const& mes) override;

private:
    std::shared_ptr<Ui::mainwindow> ui_;

    std::shared_ptr<new_file_command> new_file_command_ptr_;
    std::shared_ptr<load_command> load_command_ptr_;
    std::shared_ptr<redo_command> redo_command_ptr_;
    std::shared_ptr<save_command> save_command_ptr_;
    std::shared_ptr<save_as_command> save_as_command_ptr_;
    std::shared_ptr<showdata_command> showdata_command_ptr_;
    std::shared_ptr<undo_command> undo_command_ptr_;
    std::shared_ptr<update_command> update_command_ptr_;

    std::string opened_filename_;

    std::shared_ptr<TreeModel> model_ptr_;

    static void execute_command(std::shared_ptr<base_command> cmd);
    void react_to_user_cell_changes();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionInsertEmployer_triggered();
    void on_actionInsertDepartment_triggered();
    void on_actionRemoveRow_triggered();
};
#endif // MAINWINDOW_H
