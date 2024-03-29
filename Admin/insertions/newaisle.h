#ifndef NEWAISLE_H
#define NEWAISLE_H

#include <QMainWindow>

namespace Ui {
class newAisle;
}

class newAisle : public QMainWindow
{
    Q_OBJECT

public:
    explicit newAisle(QWidget *parent = nullptr);
    ~newAisle();

private slots:
    void on_newAisleConfirm_clicked();

private:
    Ui::newAisle *ui;
};

#endif // NEWAISLE_H
