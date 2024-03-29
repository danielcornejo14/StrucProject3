#ifndef POPUP_H
#define POPUP_H

#include <QMainWindow>

namespace Ui {
class PopUp;
}

class PopUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit PopUp(QWidget *parent = nullptr);
    ~PopUp();

private slots:
    void on_yesBtn_clicked();

    void on_noBtn_clicked();

private:
    Ui::PopUp *ui;
};

#endif // POPUP_H
