#ifndef FILESUBWINDOW_H
#define FILESUBWINDOW_H

#include <QObject>
#include <QWidget>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QString>

class FileSubWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    FileSubWindow(QWidget *parent, const QString &text = 0);
    ~FileSubWindow();
    QString getText();

private:
    QTextEdit *textEdit;
};

#endif // FILESUBWINDOW_H
