#ifndef NEWSTUDENT_H
#define NEWSTUDENT_H

#include <QDialog>

namespace Ui {
class NewStudent;
}

class NewStudent : public QDialog
{
    Q_OBJECT

public:
    explicit NewStudent(QWidget *parent = nullptr);
    ~NewStudent();

private:
    Ui::NewStudent *ui;
};

#endif // NEWSTUDENT_H
