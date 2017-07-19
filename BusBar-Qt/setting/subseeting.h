#ifndef SUBSEETING_H
#define SUBSEETING_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include "common.h"
#include "subsettingthreshold.h"

namespace Ui {
class SubSeeting;
}

class SubSeeting : public QWidget
{
    Q_OBJECT

public:
    explicit SubSeeting(QWidget *parent = 0);
    ~SubSeeting();

    void updateWid(int index);

private:
    void initWidget();
    void initTableWidget();
    void setName(int row , int column );
    void setFirstPhrase(int row , int column );
    void setSecondPhrase(int row , int column );
    void setThreePhrase(int row , int column );
    void setTem(int row , int column );

private slots:
    void itemDoubleClicked(QTableWidgetItem* item);

private:
    Ui::SubSeeting *ui;
    QTableWidget *mWidget;
    sDataPacket *mPacket ;
    int mIndex;
};

#endif // SUBSEETING_H
