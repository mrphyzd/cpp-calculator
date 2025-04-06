#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    for(const auto& type: TYPES){
        ui->cmb_controller->addItem(type.second);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb){
    if(!cb){
        std::abort();
    }

    controller_cb_ = cb;
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb){
    if(!cb){
        std::abort();
    }

    operation_cb_ = cb;
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb){
    if(!cb){
        std::abort();
    }

    control_cb_ = cb;
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb){
    if(!cb){
        std::abort();
    }

    digit_cb_ = cb;
}

void MainWindow::SetInputText(const std::string& text){
    ui->l_result->setStyleSheet("");
    ui->l_result->setText(QString(text.c_str()));
}

void MainWindow::SetErrorText(const std::string& text){
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString(text.c_str()));
}

void MainWindow::SetFormulaText(const std::string& text){
    ui->l_formula->setText(QString(text.c_str()));
}

void MainWindow::SetMemText(const std::string& text){
    ui->l_memory->setText(QString(text.c_str()));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key){
    if(key == std::nullopt){
        ui->tb_extra->setVisible(false);
        return;
    }
    ui->tb_extra->setVisible(true);
    ui->tb_extra->setText(QString(key.value().c_str()));
}

void MainWindow::on_pb_zero_clicked(){
    digit_cb_(0);
}

void MainWindow::on_pb_one_clicked(){
    digit_cb_(1);
}

void MainWindow::on_pb_two_clicked(){
    digit_cb_(2);
}

void MainWindow::on_pb_three_clicked(){
    digit_cb_(3);
}

void MainWindow::on_pb_four_clicked(){
    digit_cb_(4);
}

void MainWindow::on_pb_five_clicked(){
    digit_cb_(5);
}

void MainWindow::on_pb_six_clicked(){
    digit_cb_(6);
}

void MainWindow::on_pb_seven_clicked(){
    digit_cb_(7);
}

void MainWindow::on_pb_eignt_clicked(){
    digit_cb_(8);
}

void MainWindow::on_pb_nine_clicked(){
    digit_cb_(9);
}

void MainWindow::on_tb_extra_clicked(){
    control_cb_(ControlKey::EXTRA_KEY);
}

void MainWindow::on_pb_pm_clicked(){
    control_cb_(ControlKey::PLUS_MINUS);
}

void MainWindow::on_pb_equal_clicked(){
    control_cb_(ControlKey::EQUALS);
}

void MainWindow::on_pb_one_clear_clicked(){
    control_cb_(ControlKey::BACKSPACE);
}

void MainWindow::on_pb_all_clear_clicked(){
    control_cb_(ControlKey::CLEAR);
}

void MainWindow::on_pb_mc_clicked(){
    control_cb_(ControlKey::MEM_CLEAR);
}

void MainWindow::on_pb_mr_clicked(){
    control_cb_(ControlKey::MEM_LOAD);
}

void MainWindow::on_pb_ms_clicked(){
    control_cb_(ControlKey::MEM_SAVE);
}

void MainWindow::on_pb_plus_clicked(){
    operation_cb_(Operation::ADDITION);
}

void MainWindow::on_pb_minus_clicked(){
    operation_cb_(Operation::SUBTRACTION);
}

void MainWindow::on_pb_mult_clicked(){
    operation_cb_(Operation::MULTIPLICATION);
}

void MainWindow::on_pb_division_clicked(){
    operation_cb_(Operation::DIVISION);
}

void MainWindow::on_pb_pow_clicked(){
    operation_cb_(Operation::POWER);
}

void MainWindow::on_cmb_controller_currentIndexChanged(int index)
{
    for(const auto& type: TYPES){
        if(type.second == ui->cmb_controller->currentText()){
            controller_cb_(type.first);
            break;
        }
    }
}


