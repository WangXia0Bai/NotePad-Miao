#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 新建文件
    void on_new_file_triggered();
    // 打开文件
    void on_open_file_triggered();
    // 保存
    void on_save_file_triggered();
    // 另存为
    void on_save_as_triggered();
    // 粘贴
    void on_paste_triggered();
    // 剪切
    void on_cut_triggered();
    // 复制
    void on_copy_triggered();
    // 撤回
    void on_undo_triggered();
    // 取消撤回
    void on_redo_triggered();
    // 退出
    void on_exit_triggered();
    // 字体选项
    void on_font_triggered();
    // 关于
    void on_about_triggered();
    // 打印
    void on_printer_triggered();
    // 加粗
    void on_bolder_triggered(bool checked);
    // 斜体
    void on_italic_triggered(bool checked);
    // 下划线
    void on_underline_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    QString current_file_;
};
#endif // MAINWINDOW_H
