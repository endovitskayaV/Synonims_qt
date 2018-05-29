#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <filesubwindow.h>
#include <QFileDialog>
#include <bits/stdc++.h>
#include <QList>
#include <QErrorMessage>
#include <synonimsubwindow.h>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "utils.h"



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
    void showNewFileSubWindow(const QString &text, const QString &title);
    void showMessageDialog(const QString &text);
    const QString& setSubWindowTitle(const QString &desiredTitle);
    void makeSynonims(QString words, QString synonims);

private slots:
    void save();
    void saveAs();
    void open();
    void newFile();
    void synonim();
    void about();
    void constraints();
};


#endif // MAINWINDOW_H
