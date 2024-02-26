#include "calculator.h"
#include "ui_calculator.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QRegularExpression>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    QVBoxLayout *vLayout = new QVBoxLayout(ui->centralwidget);
    display = new QLineEdit;
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(50);
    vLayout->addWidget(display);

    QGridLayout *gridLayout = new QGridLayout();
    vLayout->addLayout(gridLayout);
    QStringList buttons {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };
    int position = 0;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j)
        {
            QPushButton *button = new QPushButton(buttons[position++]);
            gridLayout->addWidget(button, i ,j);
            connect(button, &QPushButton::clicked,this, [=]() {
                onPushButton(button->text());
            });
        }
    }
    setFixedSize(300,400);
}

void Calculator::onPushButton(const QString &buttonText) {
    QString currentText = display->text();
    QString lastChar = currentText.isEmpty() ? "" : currentText.right(1);
    if (buttonText == "-" && (currentText.isEmpty() || isOperator(lastChar))) {
        display->setText(currentText + buttonText);
        return;
    }
    if (buttonText == "C") {
        display->clear();
    } else if (buttonText == "=") {
        evaluateExpression();
    } else if (!isOperator(buttonText) || !isOperator(lastChar)) {
        display->setText(currentText + buttonText);
    }
}

void Calculator::evaluateExpression() {
    QString expression = display->text();
    if (expression.isEmpty())
        return;

    QRegularExpression regExp("[+\\-*/]");
    QStringList operands = expression.split(regExp);
    if (operands.size() != 2)
        return;
    QString operand1_str = operands[0];
    QString operand2_str = operands[1];
    double operand1 = operands[0].toDouble();
    double operand2 = operands[1].toDouble();
    QString operation = expression.mid(operands[0].size(), 1);
    if (operand1_str.startsWith('-')) {
        operand1 = -operand1;
    }

    double result = 0;
    if (operation == "+")
        result = operand1 + operand2;
    else if (operation == "-")
        result = operand1 - operand2;
    else if (operation == "*")
        result = operand1 * operand2;
    else if (operation == "/") {
        if (operand2 == 0) {
            display->setText("Error: Division by zero");
            return;
        }
        result = operand1 / operand2;
    }

    display->setText(QString::number(result));
}

bool Calculator::isOperator(const QString &str) {
    return str == "+" || str == "-" || str == "*" || str == "/";
}

Calculator::~Calculator()
{
    delete ui;
}
