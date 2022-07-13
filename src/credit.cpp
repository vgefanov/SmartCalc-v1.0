#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit)
{
    ui->setupUi(this);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_pushButton_raschet_clicked()
{
    double summa_credita, srok, stavka, mes_plateg_an, pereplata_an, obsh_summa_an, mes_percent_stavka, an_cof, chast_osn_dolga;
    double mes_plateg_dif = 0.0;
    double mes_plateg_dif_1 = 0.0;
    double obsh_summa_dif = 0.0;
    double pereplata_dif = 0.0;
    summa_credita = ui->lineEdit_summa_credita->text().toDouble();
    srok = ui->lineEdit_srok->text().toDouble();
    stavka = ui->lineEdit_stavka->text().toDouble();
    mes_percent_stavka = stavka / 12 / 100;
    an_cof = (mes_percent_stavka * pow((1 + mes_percent_stavka), srok)) / (pow((1 + mes_percent_stavka), srok) - 1);
    mes_plateg_an = summa_credita * an_cof;
    obsh_summa_an = mes_plateg_an * srok;
    pereplata_an = obsh_summa_an - summa_credita;

    chast_osn_dolga = summa_credita / srok;
    for (int i = 0; i < srok; ++i)
    {
        mes_plateg_dif = chast_osn_dolga + ((summa_credita - chast_osn_dolga * i) * mes_percent_stavka);
        if (i == 0)
        {
            mes_plateg_dif_1 = mes_plateg_dif;
        }
        obsh_summa_dif += mes_plateg_dif;
    }
    pereplata_dif = obsh_summa_dif - summa_credita;
    if (ui->lineEdit_summa_credita->text().isEmpty() || ui->lineEdit_srok->text().isEmpty() || ui->lineEdit_stavka->text().isEmpty())
    {
        QMessageBox::about(this, "Error. Incorrect data", "Не заполнишь - не посчитаю;)");
    }
    else
    {
        if (ui->comboBox_tip->currentIndex() == 0)
        {
            ui->label_mes_plateg->setText(QString::number(mes_plateg_an, 'f', 2));
            ui->label_pereplata->setText(QString::number(pereplata_an, 'f', 2));
            ui->label_obsh_summa->setText(QString::number(obsh_summa_an, 'f', 2));
        }
        if (ui->comboBox_tip->currentIndex() == 1)
        {
            ui->label_mes_plateg->setText(QString::number(mes_plateg_dif_1, 'f', 2) + " ... " + QString::number(mes_plateg_dif, 'f', 2));
            ui->label_pereplata->setText(QString::number(pereplata_dif, 'f', 2));
            ui->label_obsh_summa->setText(QString::number(obsh_summa_dif, 'f', 2));
        }
    }
}
