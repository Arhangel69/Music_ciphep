#include "mc_pr/mainwindow.hpp"
#include "mc_pr/mymusiccipher.hpp"
#include "mc_pr/mymidi.hpp"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //mmc::mymusiccipher z;
    //z.keygen();
    //z.encrypt();
    MainWindow w;
    w.show();
    std::cout<<"Complete!\n";
    return a.exec();
}
