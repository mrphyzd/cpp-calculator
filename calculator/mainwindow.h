#pragma once

#include "calculator.h"

#include <QMainWindow>

enum OperationTypes{
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_one_clicked();
    void on_pb_plus_clicked();
    void on_pb_equal_clicked();
    void on_pb_minus_clicked();
    void on_pb_mult_clicked();
    void on_pb_division_clicked();
    void on_pb_pow_clicked();
    void on_pb_two_clicked();
    void on_pb_three_clicked();
    void on_pb_six_clicked();
    void on_pb_five_clicked();
    void on_pb_four_clicked();
    void on_pb_nine_clicked();
    void on_pb_eignt_clicked();
    void on_pb_seven_clicked();
    void on_pb_dot_clicked();
    void on_pb_pm_clicked();
    void on_pb_one_clear_clicked();
    void on_pb_mc_clicked();
    void on_pb_mr_clicked();
    void on_pb_ms_clicked();
    void on_pb_all_clear_clicked();
    void on_pb_zero_clicked();

private:
    void SetOperation(OperationTypes);
    QString GetOperationSign(OperationTypes);
    void SetNumber(QString);

private:
    Ui::MainWindow* ui;
    OperationTypes current_operation_ = NO_OPERATION;
    QString input_number_;
    Calculator calculator_;
    double active_number_;
    double memory_cell_;
    bool memory_saved_;
};
