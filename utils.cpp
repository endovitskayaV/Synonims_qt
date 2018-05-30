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

    void Utils::findAll(QMap<int, QString>* words,  QString &str, QMap<int, QString>* out) {
        for (int key : words->keys()) {
            if (words->value(key)==str){
                out->insert(key, str);
            }
        }
    }

    void Utils::replaceWithSynonims(QString &words, QMap<int, QString> *foundWords, const QStringList &synonims) {
        int offset=0;
        for (int key : foundWords->keys()) {
            int chosenSynonimIndex = 0;
            do {
                chosenSynonimIndex=rand() % ((synonims.size()));
            } while (synonims[chosenSynonimIndex] == foundWords->value(key));
            words.replace(key+offset, foundWords->value(key).size(), synonims[chosenSynonimIndex]);
             offset+=foundWords->value(key).size()-((QString)synonims[chosenSynonimIndex]).size();
        }
    }

    void Utils::createWordsMap(QMap<int, QString>* wordsMap, QString &words){
        QStringList symb={",", ".", " ", "!", "'", "...", "?", "/", "(", ")"};

        int index;
        QString w;
        int i=0;
        while(i<words.size()){
            while (i<words.size() && symb.contains(words.at(i))){
                i++;
             }

            if (i<words.size()){
                index=i;
                w.clear();
                while (i<words.size() && !symb.contains(words.at(i))){
                    w.append(words.at(i));
                    i++;
                 }
              wordsMap->insert(index, w);
            }
        }

    }
