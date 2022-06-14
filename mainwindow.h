#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <lexer.h>
#include <codeeditor.h>
#include <memory>
#include <logic.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void printError(std::string error);
    void printText(std::string text);
    ~MainWindow();
private slots:
    void on_btn_ChooseFile_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
