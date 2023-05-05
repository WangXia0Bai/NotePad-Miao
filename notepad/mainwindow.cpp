#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QFileDialog"
#include "QMessageBox"
#include "QFontDialog"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_new_file_triggered()
{
    qDebug() << "on_new_file_triggered";
    // 清空
    current_file_.clear();
    ui->textEdit->setText("");

}

void MainWindow::on_open_file_triggered()
{
    // 获取文件名
    QString file_name = QFileDialog::getOpenFileName(this, "打开文件");
    // 获取文件对象
    QFile file(file_name);
    // 判断文件可读可写
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        // 如果文件只可读
        QMessageBox::warning(this, "警告", "无法打开此文件: " + file.errorString());
        return;
    }
    current_file_ = file_name;
    // 修改窗口标题
    setWindowTitle(file_name);
    // 读入文件文本
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_save_file_triggered()
{
    QString file_name;
    // 判断当前编辑器中的文本是否是空的
    if(current_file_.isEmpty())
    {
        file_name = QFileDialog::getSaveFileName(this, "保存文件");
        current_file_ = file_name;
    }
    else
    {
        file_name = current_file_;
    }

    // 获取文件对象
    QFile file(file_name);
    // 如果文件只是可写的
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "警告", "无法保存此文件: " + file.errorString());
        return;
    }
    // 修改窗口标题
    setWindowTitle(file_name);
    // 写入文件(保存)
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.close();
}

void MainWindow::on_save_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "另存为");
    // 获取文件对象
    QFile file(file_name);
    // 如果文件只是可写的
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "警告", "无法保存此文件: " + file.errorString());
        return;
    }

    // 设置为当前窗口
    current_file_ = file_name;
    setWindowTitle(file_name);
    // 保存
    QTextStream out(&file);
    QString text = ui->textEdit->toHtml();
    out << text;
    file.close();
}

void MainWindow::on_paste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_cut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_copy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_undo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_redo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_exit_triggered()
{
    QCoreApplication::exit();
}

void MainWindow::on_font_triggered()
{
    bool is_font_selected;
    QFont font = QFontDialog::getFont(&is_font_selected, this);
    // 字体是否已经选择了
    if(is_font_selected)
    {
        ui->textEdit->setFont(font);
    }
}

void MainWindow::on_about_triggered()
{
    QMessageBox::about(this,"关于","这是一个基于QT的文本编辑器notepad喵!！欢迎学习和使用~");
}

void MainWindow::on_printer_triggered()
{
    QMessageBox::warning(this, "警告", "暂时不支持此功能");
    // TODO;
}

void MainWindow::on_bolder_triggered(bool bolder)
{
    // 判断是否已经是斜体
    ui->textEdit->setFontWeight(bolder?QFont::Bold:QFont::Normal);
}

void MainWindow::on_italic_triggered(bool italics)
{
    ui->textEdit->setFontItalic(italics);
}

void MainWindow::on_underline_triggered(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

