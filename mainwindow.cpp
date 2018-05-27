#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::cout<< "System: app opened" <<std::endl;
    FileSubWindow *fileWindow = new FileSubWindow(ui->mdiArea);
    fileWindow->setWindowTitle("New");
    fileWindow->setAttribute(Qt::WA_DeleteOnClose);
    fileWindow->show();
    std::cout<< "System: basic empty sun window created" << std::endl;
}

MainWindow::~MainWindow()
{
    std::cout<< "System: app closed" << std::endl;
    delete ui;
}

void MainWindow::save() {
    FileSubWindow *activeSubWindow = dynamic_cast<FileSubWindow*>(ui->mdiArea->activeSubWindow());
    if (activeSubWindow!=0){
        //set file name and type!!
        const QString pathToSave = QFileDialog::getSaveFileName(this, "Save file", "/", "");
        if (pathToSave.trimmed().size() != 0) {
            QString text = activeSubWindow->getText();
            saveToFile(pathToSave, text);
            activeSubWindow->setWindowTitle(setSubWindowTitle(QFileInfo(pathToSave).fileName()));
            std::cout <<"Saved new file"<<pathToSave.toStdString()<<std::endl;
        }else{
            std::cout << "Canceled saving file"<< std::endl;
        }

    }else{
        std::cout << "Attempt to save non-existing file"<< std::endl;
     showErrorDialog("nothing to save");
    }
}


void MainWindow::showNewFileSubWindow(const QString &text, const QString &title) {
    FileSubWindow *fileWindow = new FileSubWindow(ui->mdiArea, text);
    fileWindow->setWindowTitle(setSubWindowTitle(title));
    fileWindow->setAttribute(Qt::WA_DeleteOnClose);
    fileWindow->show();
    std::cout <<"Created new sub window "<<title.toStdString()<< std::endl;
}

void MainWindow::showErrorDialog(const QString &text) {
    QErrorMessage *errorDialog = new QErrorMessage(this);
    errorDialog->setAttribute(Qt::WA_DeleteOnClose);
    errorDialog->showMessage(text);
}

void MainWindow::open(){
    QString path = QFileDialog::getOpenFileName(this, "Open file", "/", "Text files (*.txt)");
    if (path.trimmed().size() != 0) {
        std::cout << "Opened file "+path.toStdString() << std::endl;
        string fileContent = readFile(path.toStdString());
        showNewFileSubWindow(QString::fromStdString(fileContent), QFileInfo(path).fileName());
    }else{
       std::cout << "Canceled opening file"<< std::endl;
    }
}

void MainWindow::saveToFile(const QString &path, const QString &text) {
    QFileInfo fileInfo(path);
    if (!(fileInfo.exists() && fileInfo.isFile())) {
       QFile file(fileInfo.absoluteFilePath());
           if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
                QTextStream textStream(&file);
                textStream << text;
            }
        }
}

string MainWindow::readFile(const string &path) {
    ifstream file(path.c_str());
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void MainWindow::synonim() {
    QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
    if (subWindows.size()>1){
        std::cout << "Opened synonim window"<< std::endl;
        SynonimSubWindow *synon = new SynonimSubWindow(this, subWindows);
        if (synon->exec()) {
            std::cout << "Started making synonims"<< std::endl;
         makeSynonims(
                     (dynamic_cast<FileSubWindow*>(subWindows.at(synon->getChosenWordsIndex())))->getText(),
                (dynamic_cast<FileSubWindow*>(subWindows.at(synon->getChosenSynonimsIndex())))->getText());
        } else {
            std::cout << "Canceled making synonims"<< std::endl;
        }
        delete synon;
    }else {
        showErrorDialog("open 2 or more files to choose");
        std::cout << "Attempt to open synonims window"<< std::endl;
    }

}

void MainWindow::makeSynonims(QString words, QString synonims){
   QStringList wordsList= words.split(",");
   QStringList synonimsList=synonims.split(";");
   QStringList resList;

   for (int i=0; i<wordsList.size(); i++) {
     QStringList concreteSynonims= synonimsList.at(i).split(",");
     int index=rand() % ((concreteSynonims.size() + 1));
     resList.append(concreteSynonims.at(index));
   }

   showNewFileSubWindow(resList.join(","), "result");
}


const QString& MainWindow::setSubWindowTitle(const QString &desiredTitle){
    int index=0;
     QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
     foreach (QMdiSubWindow* subWindow, subWindows) {
         if ((dynamic_cast<FileSubWindow*>(subWindow))->windowTitle()==desiredTitle){
             index++;
         }
     }
     if (index>0){
        string test = static_cast<ostringstream*>( &(ostringstream() << index) )->str();
        //std::cout << "A "<<desiredTitle.insert(desiredTitle.lastIndexOf(".")+1,QString::fromStdString("["+test+"]")).toStdString()<< std::endl;

        //FIX THIS SHIT!!!!!!!
        return desiredTitle.insert(desiredTitle.lastIndexOf(".")+1,QString::fromStdString("["+test+"]"));

     }
     else{
         return desiredTitle;
     }
}
