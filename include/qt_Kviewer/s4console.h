#ifndef S4CONSOLE_H
#define S4CONSOLE_H

#include <QDialog>

namespace Ui {
class s4console;
}

class s4console : public QDialog
{
    Q_OBJECT

public:
    explicit s4console(QWidget *parent = nullptr);
    ~s4console();

private:
    Ui::s4console *ui;
};

#endif // S4CONSOLE_H
