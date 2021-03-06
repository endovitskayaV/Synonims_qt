#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <string>
#include <QString>
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

using namespace std;

class Utils
{
public:
    static const string currentDateTime();
    static void log(const string &text);
    static void removeEmpty(QStringList &list);
    static string readFile(const string &path);
    static void saveToFile(const QString &path, const QString &text);
    static void findAll(QMap<int, QString>* words,  QString &str, QMap<int, QString>* out);
    static void replaceWithSynonims(QString &words, QMap<int, QString> *foundWords, const QStringList &synonims);
    static void createWordsMap(QMap<int, QString>* wordsMap, QString &words);
};

#endif // UTILS_H
