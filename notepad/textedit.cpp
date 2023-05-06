#include "textedit.h"
#include "ui_textedit.h"

TextEdit::TextEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEdit)
{
    ui->setupUi(this);

    // 初始化
    hScrollBarInit();
    vScrollBarInit();
    fontInit();
    lineNumInit();
}

TextEdit::~TextEdit()
{
    delete ui;
}

void TextEdit::hScrollBarInit()
{
    connect(ui->textEdit->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(textEditHScrollBarChanged()));
    connect(ui->horizontalScrollBar,SIGNAL(valueChanged(int)),this,SLOT(scrollBarChanged()));
}

void TextEdit::vScrollBarInit()
{
    connect(ui->textEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textEditVScrollBarChanged()));
    connect(ui->textBrowser->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(textBrowserVScrollBarChanged()));
}

void TextEdit::fontInit()
{
    QFont font("Consolas",14);
    ui->textEdit->setFont(font);
    ui->textBrowser->setFont(font);
}

void TextEdit::lineNumInit()
{
	// 设置行数初始值始终为1
    ui->textBrowser->setText("1");
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
}

void TextEdit::textEditHScrollBarChanged()
{
    // 设置对齐
    ui->horizontalScrollBar->setValue(ui->textEdit->horizontalScrollBar()->value());
    ui->horizontalScrollBar->setMaximum(ui->textEdit->horizontalScrollBar()->maximum());
    ui->horizontalScrollBar->setMinimum(ui->textEdit->horizontalScrollBar()->minimum());
    ui->horizontalScrollBar->setPageStep(ui->textEdit->horizontalScrollBar()->pageStep());
}

void TextEdit::scrollBarChanged()
{
    ui->textEdit->horizontalScrollBar()->setValue(ui->horizontalScrollBar->value());
}

void TextEdit::textEditVScrollBarChanged()
{
    ui->textBrowser->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->value());
}

void TextEdit::textBrowserVScrollBarChanged()
{
    ui->textEdit->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->value());
}

void TextEdit::onTextChanged()
{
    // 获取 TextEdit 的行数
    int line_count_of_textedit = ui->textEdit->document()->lineCount();

    // 获取 TextBrowser 的文本内容，并按换行符分割成行数组
    QString text = ui->textBrowser->toPlainText();
    QStringList lines = text.split('\n');

    // 获取 TextBrowser 的行数
    int line_count_of_textbrowser = lines.size();

    // 如果 TextBrowser 的行数小于 TextEdit 的行数，则在末尾添加缺失行数的行号
    if (line_count_of_textbrowser < line_count_of_textedit) {
        for (int i = line_count_of_textbrowser; i < line_count_of_textedit; i++) {
            lines.append(QString::number(i + 1));
        }
    }
    // 如果 TextBrowser 的行数大于 TextEdit 的行数，则移除多余的行号
    else if (line_count_of_textbrowser > line_count_of_textedit) {
        for (int i = line_count_of_textedit; i < line_count_of_textbrowser; i++) {
            lines.removeLast();
        }
    }

    // 使用换行符将行数组拼接成文本字符串，并设置到 TextBrowser 中
    text = lines.join("\n");
    ui->textBrowser->setMaximumWidth(25+QString::number(line_count_of_textedit).length()*7);
    ui->textBrowser->setText(text);
}


