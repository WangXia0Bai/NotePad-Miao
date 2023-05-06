#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>

namespace Ui {
class TextEdit;
}

class TextEdit : public QWidget
{
    Q_OBJECT

public:
    explicit TextEdit(QWidget *parent = nullptr);
    ~TextEdit();
private slots:
    // 将textedit的水平滚动条与widget的水平滚动条绑定
    void textEditHScrollBarChanged();
    // 将widget的水平滚动条与textedit的水平滚动条绑定
    void scrollBarChanged();
    // 将textedit的垂直滚动条与browser的垂直滚动条绑定
    void textEditVScrollBarChanged();
    // 将browser的垂直滚动条与textedit的垂直滚动条绑定
    void textBrowserVScrollBarChanged();
    // 检测行数并更新
    void onTextChanged();
private:
    Ui::TextEdit *ui;
    // 水平滚动条初始化
    void hScrollBarInit();
    // 垂直滚动条初始化
    void vScrollBarInit();
    // 字体初始化
    void fontInit();
    // 行数初始化
    void lineNumInit();
};

#endif // TEXTEDIT_H
