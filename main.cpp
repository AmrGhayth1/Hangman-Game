#include "stdafx.h"
#include "HangManProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
 {
    QApplication a(argc, argv);
    HangManProject w;
    w.show();
    return a.exec();
}
