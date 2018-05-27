#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <filesubwindow.h>
#include <QFileDialog>
#include <string>
#include <bits/stdc++.h>
#include <QString>
#include <QList>
#include <QErrorMessage>
#include <synonimsubwindow.h>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    string readFile(const string &path);
    void showNewFileSubWindow(const QString &text, const QString &title);
    void showErrorDialog(const QString &text);
    void saveToFile(const QString &path, const QString &text);
    void makeSynonims(QString words, QString synonims);
    const QString& setSubWindowTitle(const QString &desiredTitle);

private slots:
    void save();
    void open();
    void synonim();
};


#endif // MAINWINDOW_H
