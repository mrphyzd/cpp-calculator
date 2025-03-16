#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pb_zero_clicked()
{
    SetNumber("0");
}

void MainWindow::on_pb_one_clicked()
{
    SetNumber("1");
}

void MainWindow::on_pb_two_clicked()
{
    SetNumber("2");
}

void MainWindow::on_pb_three_clicked()
{
    SetNumber("3");
}

void MainWindow::on_pb_four_clicked()
{
    SetNumber("4");
}

void MainWindow::on_pb_five_clicked()
{
    SetNumber("5");
}

void MainWindow::on_pb_six_clicked()
{
    SetNumber("6");
}

void MainWindow::on_pb_seven_clicked()
{
    SetNumber("7");
}

void MainWindow::on_pb_eignt_clicked()
{
    SetNumber("8");
}

void MainWindow::on_pb_nine_clicked()
{
    SetNumber("9");
}

void MainWindow::SetNumber(QString number)
{
    if(input_number_ == "0" && number != "."){
        input_number_ = number;
    }else{
        input_number_ += number;
    }
    active_number_= input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::on_pb_dot_clicked()
{
    SetNumber(".");
}

void MainWindow::on_pb_pm_clicked()
{
    active_number_ = -active_number_;
    input_number_ = QString::number(active_number_);
    ui->l_result->setText(input_number_);
}

void MainWindow::on_pb_one_clear_clicked()
{
    input_number_.chop(1);
    active_number_ = input_number_.toDouble();
    ui->l_result->setText(input_number_);
}

void MainWindow::on_pb_mc_clicked()
{
    memory_saved_ = false;
    ui->l_memory->setText("");
}

void MainWindow::on_pb_mr_clicked()
{
    if(!memory_saved_){
        return;
    }

    active_number_ = memory_cell_;
    input_number_ = QString::number(active_number_);
    ui->l_result->setText(input_number_);
}

void MainWindow::on_pb_ms_clicked()
{
    memory_saved_ = true;
    memory_cell_ = active_number_;
    input_number_.clear();
    ui->l_memory->setText("M");
}

void MainWindow::on_pb_all_clear_clicked()
{
    input_number_.clear();
    active_number_ = 0.;
    ui->l_result->setText("0");
    ui->l_formula->setText("");
    current_operation_ = OperationTypes::NO_OPERATION;
}

void MainWindow::on_pb_plus_clicked()
{
    SetOperation(OperationTypes::ADDITION);
}

void MainWindow::on_pb_minus_clicked()
{
    SetOperation(OperationTypes::SUBTRACTION);
}

void MainWindow::on_pb_mult_clicked()
{
    SetOperation(OperationTypes::MULTIPLICATION);
}

void MainWindow::on_pb_division_clicked()
{
    SetOperation(OperationTypes::DIVISION);
}

void MainWindow::on_pb_pow_clicked()
{
    SetOperation(OperationTypes::POWER);
}

void MainWindow::SetOperation(OperationTypes operation_type)
{
    if(current_operation_ == OperationTypes::NO_OPERATION){
        calculator_.Set(active_number_);
    }

    ui->l_formula->setText(input_number_ + GetOperationSign(operation_type));
    current_operation_ = operation_type;
    input_number_.clear();
}


QString MainWindow::GetOperationSign(OperationTypes operation_type)
{
    switch(operation_type)
    {
    case OperationTypes::ADDITION:
        return " + ";
    case OperationTypes::SUBTRACTION:
        return " − ";
    case OperationTypes::DIVISION:
        return " ÷ ";
    case OperationTypes::MULTIPLICATION:
        return " × ";
    case OperationTypes::POWER:
        return " ^ ";
    case OperationTypes::NO_OPERATION:
    default:
        return "";
    }
}


void MainWindow::on_pb_equal_clicked()
{
    if(current_operation_ == OperationTypes::NO_OPERATION){
        return;
    }

    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + GetOperationSign(current_operation_) + QString::number(active_number_) + " =");

    switch (current_operation_) {
    case OperationTypes::ADDITION:
        calculator_.Add(active_number_);
        break;
    case OperationTypes::SUBTRACTION:
        calculator_.Sub(active_number_);
        break;
    case OperationTypes::DIVISION:
        calculator_.Div(active_number_);
        break;
    case OperationTypes::MULTIPLICATION:
        calculator_.Mul(active_number_);
        break;
    case OperationTypes::POWER:
        calculator_.Pow(active_number_);
        break;
    default:
        break;
    }

    active_number_ = calculator_.GetNumber();
    input_number_ = QString::number(active_number_);
    ui->l_result->setText(input_number_);
    current_operation_ = OperationTypes::NO_OPERATION;
}












