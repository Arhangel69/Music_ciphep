#include "mc_pr/mainwindow.hpp"
#include "ui_mainwindow.h"
#include "mc_pr/mymusiccipher.hpp"
#include <string>
#include <QFileDialog>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mmc::mymusiccipher* MMC = new mmc::mymusiccipher();
    ui->file_path_enc->setPlainText("/home/user/text.txt");
    ui->file_path_enc_2->setPlainText("/home/user/cipher.mid");
    ui->file_path_dec->setPlainText("/home/user/text.txt");
    ui->file_path_dec_2->setPlainText("/home/user/cipher.mid");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}

void MainWindow::on_btn_encrypt_clicked()
{
    QFileDialog dialog_open_file(this);
    QString path_ciph = dialog_open_file.getSaveFileName();
    QString path_clear = dialog_open_file.getOpenFileName();
    ui->file_path_enc->setPlainText(path_ciph+".mid");
    ui->file_path_enc_2->setPlainText(path_clear);
    MMC.keygen();
    MMC.encrypt(path_clear.toStdString(), path_ciph.toStdString());
}

void MainWindow::on_btn_decrypt_clicked()
{
    QFileDialog dialog_open_file(this);
    dialog_open_file.setNameFilter(tr("Cipher (*.mid)"));
    dialog_open_file.setFileMode(QFileDialog::ExistingFile);
    QString path_ciph = dialog_open_file.getOpenFileName();
    QString path_clear = dialog_open_file.getSaveFileName();
    ui->file_path_dec->setPlainText(path_ciph);
    MMC.decrypt(path_clear.toStdString(), path_ciph.toStdString());
}

void MainWindow::on_btn_read_key_clicked()
{
    QFileDialog dialog_open_file(this);
    dialog_open_file.setNameFilter(tr("Key (*.kdakey)"));
    dialog_open_file.setFileMode(QFileDialog::ExistingFile);
    QString path = dialog_open_file.getOpenFileName();
    ui->key_path->setPlainText(path);
    MMC.read_key(path.toStdString());
}

void MainWindow::on_btn_write_key_clicked()
{
    QFileDialog dialog_open_file(this);
    dialog_open_file.setFileMode(QFileDialog::AnyFile);
    QString path = dialog_open_file.getSaveFileName();
    ui->key_path->setPlainText(path+".kdakey");
    MMC.write_key(path.toStdString(),".kdakey");
}

void MainWindow::on_btn_rekeygen_clicked()
{

}
