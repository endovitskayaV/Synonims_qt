#include "utils.h"

 void Utils::log(const string &text){
        QFile file(QDir::currentPath()+"/synQtLog.txt");
        file.open(QIODevice::Append);
        QTextStream textStream(&file);
        textStream << QString::fromStdString(currentDateTime()+" "+text+"\n");
    }

    const string Utils::currentDateTime() {
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }

    void Utils::saveToFile(const QString &path, const QString &text) {
        QFileInfo fileInfo(path);
        if (!(fileInfo.exists() && fileInfo.isFile())) {
           QFile file(fileInfo.absoluteFilePath());
               if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
                    QTextStream textStream(&file);
                    textStream << text;
                }
            }
    }

    string Utils::readFile(const string &path) {
        ifstream file(path.c_str());
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void Utils::findAll(QMap<int, QString>& words,  QString &str, QMap<int, QString>* out) {
        for (int key : words.keys()) {
            if (words.value(key)==str){
                out->insert(key, str);
            }
        }
    }


