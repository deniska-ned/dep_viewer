#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    qSetMessagePattern(
            "[%{type}] %{appname} (%{file}:%{line} %{function}) - %{message}");
    QApplication a(argc, argv);
    mainwindow w;
    w.show();
    return a.exec();
}
