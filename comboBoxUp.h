#ifndef COMBOBOXUP_H
#define COMBOBOXUP_H

#include <QComboBox>

//将QComboBox提升为ComboBoxUp
class ComboBoxUp : public QComboBox
{
public:
    explicit ComboBoxUp();
    ComboBoxUp(QWidget *parent = 0);

    void adjustItemWidth();

};

#endif // COMBOBOXUP_H
