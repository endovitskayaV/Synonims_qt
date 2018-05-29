#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);

    Utils::log("App opened");
    showNewFileSubWindow("", "New");
}

MainWindow::~MainWindow(){
    Utils::log("App closed\n");
    delete ui;
}

void MainWindow::save() {
    FileSubWindow *activeSubWindow = dynamic_cast<FileSubWindow*>(ui->mdiArea->activeSubWindow());
    if (activeSubWindow!=0){
        QFileInfo fileInfo(activeSubWindow->windowTitle());
        if (!(fileInfo.exists() && fileInfo.isFile())) {
            saveAs();
        } else {
            QString text = activeSubWindow->getText();
            QFile file(fileInfo.absoluteFilePath());
            if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
                QTextStream textStream(&file);
                textStream << text;
            }
        }
    }else{
        Utils::log("Attempt to save non-existing file");
        showMessageDialog("Nothing to save");
    }
}

void MainWindow::saveAs(){
    FileSubWindow *activeWindow = dynamic_cast<FileSubWindow*>(ui->mdiArea->activeSubWindow());
    if (activeWindow == 0) {
        showMessageDialog("No file selected");
        Utils::log("Tried tos save non existing file");
        return;
    }
    QString text = activeWindow->getText();
    QString path = QFileDialog::getSaveFileName(this, "Save as", "/", "");
    if (path.trimmed().size() == 0) {
        Utils::log("Canceled saving file");
        return;
    }
    QFileInfo fileInfo(path);
    if (!(fileInfo.exists() && fileInfo.isFile())) {
        QFile file(fileInfo.absoluteFilePath());
        if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
            QTextStream textStream(&file);
            textStream << text;
        }
    }

    Utils::log("Saved new file"+path.toStdString());
    activeWindow->setWindowTitle(path);
}

void MainWindow::showNewFileSubWindow(const QString &text, const QString &title) {
    FileSubWindow *fileWindow = new FileSubWindow(ui->mdiArea, text);
    fileWindow->setWindowTitle(title);
    fileWindow->setAttribute(Qt::WA_DeleteOnClose);
    fileWindow->show();
    Utils::log("Created new sub window "+title.toStdString());
}

void MainWindow::showMessageDialog(const QString &text) {
    QErrorMessage *dialog = new QErrorMessage(this);
    dialog->setWindowTitle("Attention");
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->showMessage(text);
}

void MainWindow::newFile(){
    int index=0;
    QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
        foreach (QMdiSubWindow* subWindow, subWindows) {
            if ((dynamic_cast<FileSubWindow*>(subWindow))->windowTitle().contains("New")){
                index++;
            }
           }
     string title="New";
     if (index!=0){title=title.append(static_cast<ostringstream*>( &(ostringstream() << index))->str());}
    showNewFileSubWindow("",QString::fromStdString(title));
}

void MainWindow::open(){
    QString path = QFileDialog::getOpenFileName(this, "Open file", "/", "Text files (*.txt)");
    if (path.trimmed().size() != 0) {

        QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
            foreach (QMdiSubWindow* subWindow, subWindows) {
                if ((dynamic_cast<FileSubWindow*>(subWindow))->windowTitle()==path){
                    showMessageDialog(QString::fromStdString("File "+path.toStdString()+" already opened"));
                    Utils::log("Tried to open "+path.toStdString()+" again");
                    return;
                }
            }

        Utils::log("Opened file "+path.toStdString());
        string fileContent = Utils::readFile(path.toStdString());
        showNewFileSubWindow(QString::fromStdString(fileContent), path);
    }else{
       Utils::log("Canceled opening file");
    }
}

void MainWindow::synonim() {
    QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
    if (subWindows.size()>1){
        Utils::log("Opened synonim window");
        SynonimSubWindow *synon = new SynonimSubWindow(this, subWindows);
        if (synon->exec()) {
            int indexWords=synon->getChosenWordsIndex();
            int indexSynonims=synon->getChosenSynonimsIndex();
            if(indexWords==indexSynonims){
                showMessageDialog("Cannot choose same file");
                Utils::log("Attempt to choose same file");
            }else{
         makeSynonims(
                (dynamic_cast<FileSubWindow*>(subWindows.at(indexWords)))->getText(),
                (dynamic_cast<FileSubWindow*>(subWindows.at(indexSynonims)))->getText());
            }
        } else {
            Utils::log("Canceled making synonims");
        }
        delete synon;
    }else {
        showMessageDialog("Open 2 or more files to choose");
        Utils::log("Attempt to open synonims window");
    }

}

void MainWindow::constraints(){
    showMessageDialog("Synonims file: syn1, syn2, syn3, ...");
    Utils::log("'Constraints' opened");
}

void MainWindow::about(){
    showMessageDialog("Synonims Maker v1.0");
    Utils::log("'About' opened");
}

void MainWindow::makeSynonims(QString words, QString synonims){

    QMap<int, QString> *wordsMap=new QMap<int, QString>();
    Utils::createWordsMap(wordsMap,words);

    QStringList synonimsList=synonims.split("\n");

    for (int i=0; i<synonimsList.size(); i++) {

        QStringList concreteSynonims=synonimsList[i].split(",");
        QMap<int, QString> *foundWords = new QMap<int, QString>();
        for (int j=0; j<concreteSynonims.size(); j++) {
            QString syn=concreteSynonims.at(j);
            syn=syn.simplified();
            concreteSynonims.replace(j,syn);
            Utils::findAll(wordsMap,syn, foundWords);
        }
        Utils::replaceWithSynonims(words, foundWords, concreteSynonims);
    }

   Utils::log("Synonims made");
   showNewFileSubWindow(words, "result");

}


