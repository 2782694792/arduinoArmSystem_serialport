#include "comboBoxUp.h"

#include <QAbstractItemView>

ComboBoxUp::ComboBoxUp()
{
}

ComboBoxUp::ComboBoxUp(QWidget *parent)
{
    QComboBox varname(parent);
}

void ComboBoxUp::adjustItemWidth()
{
    //    优化串口设备显示信息
    //    遍历串口设备所有字符串的长度，找出最大值并设置最大长度显示
    int max_len=0;
    for(int i=0;i < this->count();i++)
    {
        if(max_len < this->itemText(i).length())
            max_len = this->itemText(i).length();
    }
    //        获取字体的磅值
    int font_pval = this->font().pointSize();
    //        （字符数*每个字符的宽度(磅)*比例）个像素          1磅 ＝ 1.33333像素（9号字体时）1.66667像素（大字体时）
    //  英文字符：0.75   中文字符：
    int w = max_len * font_pval * 1.12;
    this->view()->setFixedWidth(w);
}
