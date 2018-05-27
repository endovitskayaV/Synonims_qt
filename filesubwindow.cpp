#include "filesubwindow.h"

FileSubWindow::FileSubWindow(QWidget *parent, const QString &text): QMdiSubWindow(parent)
{
    textEdit = new QTextEdit();
    textEdit->setPlainText(text);
    setWidget(textEdit);
}

FileSubWindow::~FileSubWindow() {
     textEdit->~QTextEdit();
}

QString FileSubWindow::getText() {
    return textEdit->toPlainText();
}
