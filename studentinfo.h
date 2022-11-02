#ifndef STUDENTINFO_H
#define STUDENTINFO_H

#include <QDialog>

namespace Ui {
class studentInfo;
}

class studentInfo : public QDialog
{
    Q_OBJECT

public:
    explicit studentInfo(QWidget *parent = nullptr, QList<QString> data = {});
    ~studentInfo();

private:
    Ui::studentInfo *ui;
    QList<QString> data;
};

#endif // STUDENTINFO_H
