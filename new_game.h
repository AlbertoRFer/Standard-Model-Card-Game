#ifndef NEW_GAME_H
#define NEW_GAME_H

#include <QDialog>

namespace Ui {
class new_game;
}

class new_game : public QDialog
{
    Q_OBJECT
    
public:
    explicit new_game(QWidget *parent = 0);
    ~new_game();
    
private:
    Ui::new_game *ui;
};

#endif // NEW_GAME_H
