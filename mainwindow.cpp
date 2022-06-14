#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <fas.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui -> setupUi(this);
    QFontDatabase database;
    QFont font;
    if (database.families().contains("Monospace"))
            font = QFont("Monospace", 12);
        else {
            foreach (QString family, database.families()) {
                if (database.isFixedPitch(family)) {
                    font = QFont(family, 12);
                    break;
                }
            }
        }
    ui -> lbl_error -> setFont(font);
}


void MainWindow::printText(std::string text) {
    ui -> lbl_json-> setPlainText(QString::fromUtf8(text.c_str()));
}

void MainWindow::printError(std::string error) {
    ui -> lbl_error-> setText(QString::fromUtf8(error.c_str()));
}

MainWindow::~MainWindow() {
    delete ui;
}




void MainWindow::on_btn_ChooseFile_clicked() {
    ui -> lbl_FilePath -> clear();
    ui -> lbl_json -> clear();
    ui-> lbl_error->clear();
    std::string err;
    QString pathFileName = QFileDialog::getOpenFileName(this, "Open File", "C://", "JSON File (*.json)");
    fas fasade =fas(app());
    ui -> lbl_FilePath -> setText(pathFileName);
    if (!pathFileName.isEmpty()) {
        std::string rt = pathFileName.toStdString();
        fasade.parseAll(rt);
        if (fasade.getError() == ""){
            printText(fasade.getJson());
        } else {
            if(!fasade.isFileError()){
                printText(fasade.getText());
            }
            printError(fasade.getError());
        }
    }
}

