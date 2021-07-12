#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <memory>

#include <QMainWindow>

#include "i_tableowner.h"
#include "load_command.h"
#include "redo_command.h"
#include "save_command.h"
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
    void set_table_data(std::shared_ptr<std::vector<department>> departments) override;

    std::string get_load_filename() override;
    std::string get_save_filename() override;

    void show_message(std::string const& mes) override;

private:
    std::shared_ptr<Ui::mainwindow> _ui;

    std::shared_ptr<load_command> _load_command_ptr;
    std::shared_ptr<redo_command> _redo_command_ptr;
    std::shared_ptr<save_command> _save_command_ptr;
    std::shared_ptr<showdata_command> _showdata_command_ptr;
    std::shared_ptr<undo_command> _undo_command_ptr;
    std::shared_ptr<update_command> _update_command_ptr;

    std::string _src_filename;

    std::shared_ptr<TreeModel> _model_ptr;

    static void execute_command(std::shared_ptr<base_command> cmd);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionInsertEmployer_triggered();
    void on_actionInsertDepartment_triggered();
    void on_actionRemoveRow_triggered();

    void onvaluechanged();
};
#endif // MAINWINDOW_H
