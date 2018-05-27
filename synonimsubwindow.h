#ifndef SYNONIMSUBWINDOW_H
#define SYNONIMSUBWINDOW_H

#include <QDialog>
#include <QList>
#include <QMdiSubWindow>
#include <iostream>

namespace Ui {
class SynonimSubWindow;
}

class SynonimSubWindow : public QDialog
{
    Q_OBJECT

public:
    SynonimSubWindow(QWidget *parent = 0, QList<QMdiSubWindow*> windowsSList = QList<QMdiSubWindow*>());
    ~SynonimSubWindow();
    int getChosenWordsIndex();
    int getChosenSynonimsIndex();

private:
    Ui::SynonimSubWindow *ui;
};

#endif // SYNONIMSUBWINDOW_H
