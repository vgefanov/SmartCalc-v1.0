#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_open_bracket, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_close_bracket, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_arccos, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_arcsin, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_arctan, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trig_log_operations()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton *button = (QPushButton *)sender();
    if (ui->result_show->text().endsWith("0") && ui->result_show->text().size() == 1)
    {
        ui->result_show->setText(button->text());
    }
    else
    {
        if (ui->result_show->text().endsWith("x") != 1 || button->text() != "x")
        {
            ui->result_show->setText(ui->result_show->text() + button->text());
        }
    }
}

void MainWindow::operations()
{
    QPushButton *button = (QPushButton *)sender();
    int operator_ex = 1;
    double all_numbers;
    QString new_label;
    if(ui->result_show->text().endsWith("+") ||
            ui->result_show->text().endsWith("-") ||
            ui->result_show->text().endsWith("*") ||
            ui->result_show->text().endsWith("÷") ||
            ui->result_show->text().endsWith("x^y") ||
            ui->result_show->text().endsWith("mod"))
    {
        operator_ex = 0;
    }
    if (button->text() == "%")
    {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * 0.01;
        new_label = QString::number(all_numbers, 'g', 15);
        ui->result_show->setText(new_label);
    }
    else if (button->text() == "+" && operator_ex)
    {
        if (ui->result_show->text() == "0")
        {
            ui->result_show->setText("+");
        }
        else
        {
            ui->result_show->setText(ui->result_show->text() + "+");
        }
    }
    else if (button->text() == "-" && operator_ex)
    {
        if (ui->result_show->text() == "0")
        {
            ui->result_show->setText("-");
        }
        else
        {
            ui->result_show->setText(ui->result_show->text() + "-");
        }
    }
    else if (button->text() == "*" && operator_ex)
    {
        ui->result_show->setText(ui->result_show->text() + "*");
    }
    else if (button->text() == "÷" && operator_ex)
    {
        ui->result_show->setText(ui->result_show->text() + "/");
    }
    else if (button->text() == "x^y" && operator_ex)
    {
        ui->result_show->setText(ui->result_show->text() + "^");
    }
    else if (button->text() == "mod" && operator_ex)
    {
        ui->result_show->setText(ui->result_show->text() + " mod ");
    }
}

void MainWindow::trig_log_operations()
{
    QPushButton *button = (QPushButton *)sender();
    int operator_ex = 1;
    if (ui->result_show->text().endsWith("acos") ||
    ui->result_show->text().endsWith("asin") ||
    ui->result_show->text().endsWith("atan") ||
    ui->result_show->text().endsWith("cos") ||
    ui->result_show->text().endsWith("sin") ||
    ui->result_show->text().endsWith("tan") ||
    ui->result_show->text().endsWith("sqrt") ||
    ui->result_show->text().endsWith("ln") ||
    ui->result_show->text().endsWith("log"))
    {
        operator_ex = 0;
    }
    if (ui->result_show->text().endsWith("0") && ui->result_show->text().size() == 1)
    {
        if (button->text() == "acos")
        {
            ui->result_show->setText("acos(");
        }
        else if (button->text() == "asin")
        {
            ui->result_show->setText("asin(");
        }
        else if (button->text() == "atan")
        {
            ui->result_show->setText("atan(");
        }
        else if (button->text() == "cos")
        {
            ui->result_show->setText("cos(");
        }
        else if (button->text() == "sin")
        {
            ui->result_show->setText("sin(");
        }
        else if (button->text() == "tan")
        {
            ui->result_show->setText("tan(");
        }
        else if (button->text() == "sqrt")
        {
            ui->result_show->setText("sqrt(");
        }
        else if (button->text() == "ln")
        {
            ui->result_show->setText("ln(");
        }
        else if (button->text() == "log")
        {
            ui->result_show->setText("log(");
        }
    }
    else
    {
        if (button->text() == "acos" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "acos(");
        }
        else if (button->text() == "asin" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "asin(");
        }
        else if (button->text() == "atan" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "atan(");
        }
        else if (button->text() == "cos" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "cos(");
        }
        else if (button->text() == "sin" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "sin(");
        }
        else if (button->text() == "tan" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "tan(");
        }
        else if (button->text() == "sqrt" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "sqrt(");
        }
        else if (button->text() == "ln" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "ln(");
        }
        else if (button->text() == "log" && operator_ex)
        {
            ui->result_show->setText(ui->result_show->text() + "log(");
        }
    }
}

void MainWindow::on_pushButton_dot_clicked()
{
    if (ui->result_show->text().endsWith(".") != 1)
    {
        ui->result_show->setText(ui->result_show->text() + ".");
    }
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->result_show->setText("0");
    ui->lineEdit_x->setText("");
    ui->lineEdit_x_begin->setText("");
    ui->lineEdit_x_end->setText("");
    ui->lineEdit_y_begin->setText("");
    ui->lineEdit_y_end->setText("");
}

void MainWindow::on_pushButton_equal_clicked()
{
    char* str = new char(ui->result_show->text().length());
    QByteArray barr = ui->result_show->text().toLatin1();
    strlcpy(str, barr, ui->result_show->text().length() + 1);
    int exec;
    double res = 0.0;
    double value_of_x = 0.0;
    if (ui->result_show->text() != "Значение x")
    {
        value_of_x = ui->lineEdit_x->text().toDouble();
    }
    if (ui->result_show->text().contains("x"))
    {
        exec = calculation(str, value_of_x, &res);
    }
    else
    {
        exec = calculation(str, value_of_x, &res);
    }
    if (exec == 1)
    {
        QMessageBox::about(this, "Error. Incorrect data", "Error. Incorrect data");
    }
    else
    {
        QString value = QString::number(res, 'g', 15);
        ui->result_show->setText(value);
    }
}

QString MainWindow::show_label()
{
    QString new_label = ui->result_show->text();
    if (new_label == "0")
    {
        new_label = "";
    }
    return new_label;
}

void MainWindow::on_pushButton_backspace_clicked()
{
    QString new_label = show_label();
    if (new_label.endsWith("asin(") ||
            new_label.endsWith("acos(") ||
            new_label.endsWith("atan(") ||
            new_label.endsWith(" mod ") ||
            new_label.endsWith("sqrt("))
    {
        new_label = new_label.left(new_label.size() - 5);
    }
    else if (new_label.endsWith("sin(") ||
             new_label.endsWith("cos(") ||
             new_label.endsWith("tan(") ||
             new_label.endsWith("log("))
    {
        new_label = new_label.left(new_label.size() - 4);
    }
    else if (new_label.endsWith("ln("))
    {
        new_label = new_label.left(new_label.size() - 3);
    }
    else
    {
        new_label = new_label.left(new_label.size() - 1);
    }
    if (new_label == "")
    {
        new_label = "0";
    }
    ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_graf_clicked()
{
    QString label = show_label();
    QCustomPlot *graphic = new QCustomPlot();
    graphWindow = new QWidget();
    graphWindow->setFixedSize(500, 500);
    graphWindow->setWindowTitle(label);
    graphWindow->setLayout(new QGridLayout());
    graphWindow->layout()->addWidget(graphic);
    graphWindow->show();
    if (ui->lineEdit_x_begin->text().isEmpty())
    {
        xBegin = -100;
    }
    else
    {
        xBegin = ui->lineEdit_x_begin->text().toDouble();
    }
    if (ui->lineEdit_x_end->text().isEmpty())
    {
        xEnd = 100;
    }
    else
    {
        xEnd = ui->lineEdit_x_end->text().toDouble();
    }
    if (ui->lineEdit_y_begin->text().isEmpty())
    {
        yBegin = -100;
    }
    else
    {
        yBegin = ui->lineEdit_y_begin->text().toDouble();
    }
    if (ui->lineEdit_y_end->text().isEmpty())
    {
        yEnd = 100;
    }
    else
    {
        yEnd = ui->lineEdit_y_end->text().toDouble();
    }
    graphic->xAxis->setRange(xBegin, xEnd);
    graphic->yAxis->setRange(yBegin, yEnd);
    char* str = new char(ui->result_show->text().length());
    QByteArray barr = ui->result_show->text().toLatin1();
    strlcpy(str, barr, ui->result_show->text().length() + 1);
    h = 0.1;
    N = (xBegin - xEnd)/h + 2;
    int exec = 0;
    for (X = xBegin; X < xEnd && exec == 0; X += h)
    {
        x.push_back(X);
        double res = 0.0;
        exec = calculation(str, X, &res);
        y.push_back(res);
    }
    if (exec == 1)
    {
        QMessageBox::about(this, "Error. Incorrect data", "Error. Incorrect data");
    }
    else
    {
        graphic->addGraph();
        graphic->graph(0)->addData(x, y);
        graphic->replot();
    }
    x.clear();
    y.clear();
    if (str != nullptr)
    {
        delete str;
    }
}

void MainWindow::on_radioButton_credit_clicked()
{
    credit = new Credit;
    credit->show();
}

void MainWindow::on_radioButton_deposit_clicked()
{
    QMessageBox::about(this, "Error. Incorrect data", "Депозитный я не сделал, но кнопочка тянет на 40%");
}

