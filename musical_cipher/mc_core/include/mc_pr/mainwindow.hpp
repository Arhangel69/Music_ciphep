#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "mc_pr/mymusiccipher.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:

private slots:
    void on_btn_exit_clicked();
    void on_btn_encrypt_clicked();
    void on_btn_decrypt_clicked();
    void on_btn_read_key_clicked();
    void on_btn_write_key_clicked();
    void on_btn_rekeygen_clicked();

private:
    Ui::MainWindow *ui;
    mmc::mymusiccipher MMC;
};

#endif // MAINWINDOW_HPP
