#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QMainWindow>
#include <QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE
class Calculator : public QMainWindow
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
private slots:
    void onPushButton(const QString &buttonText);
    void evaluateExpression();
    bool isOperator(const QString &str);

private:
    Ui::Calculator *ui;
    QLineEdit *display;
};
#endif // CALCULATOR_H
