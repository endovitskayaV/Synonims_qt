#include "synonimsubwindow.h"
#include "ui_synonimsubwindow.h"

SynonimSubWindow::SynonimSubWindow(QWidget *parent, QList<QMdiSubWindow*> windowsList) :
    QDialog(parent),
    ui(new Ui::SynonimSubWindow)
{
    ui->setupUi(this);
    for (QList<QMdiSubWindow*>::Iterator it = windowsList.begin(); it != windowsList.end(); it++) {
        ui->wordsComboBox->addItem((*it)->windowTitle());
        ui->synonimsComboBox->addItem((*it)->windowTitle());
    }
}
int SynonimSubWindow::getChosenWordsIndex() {
    std::cout << "w"<<ui->wordsComboBox->currentIndex()<< std::endl;
    return ui->wordsComboBox->currentIndex();
}

int SynonimSubWindow::getChosenSynonimsIndex() {
    std::cout << "syn"<<ui->synonimsComboBox->currentIndex()<< std::endl;
    return ui->synonimsComboBox->currentIndex();
}

SynonimSubWindow::~SynonimSubWindow()
{
    delete ui;
}
