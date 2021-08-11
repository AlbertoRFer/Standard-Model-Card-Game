#ifndef INPUT_NAME_H
#define INPUT_NAME_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class Input_name;
}

class Input_name : public QDialog
{
    Q_OBJECT
    
public:
    explicit Input_name(QWidget *parent = 0);
    QString nombre();
    ~Input_name();
    
private:
    Ui::Input_name *ui;
    QLineEdit* Edit;
};

#endif // INPUT_NAME_H
