#ifndef COMTABLEWID_H
#define COMTABLEWID_H

#include <QWidget>
#include "common.h"

namespace Ui {
class ComTableWid;
}

class ComTableWid : public QWidget
{
    Q_OBJECT

public:
    explicit ComTableWid(QWidget *parent = 0);
    ~ComTableWid();

    void initPackets(sDevPackets *packets) { mPackets = packets; }
protected:
    void initTableWid(QStringList &header, int line, const QString &title);
    void setTableItem(int id, int column, const QString &str);
    void setTableRow(int id, QStringList &listStr);
    void checkTableRow(int line);

    void clearRow(int row);
    void clearTable();
    void setItemColor(int id, int column, int alarm);    

protected slots:
    virtual void timeoutDone(){}

protected:
    QTimer *timer;
    sDevPackets *mPackets;
    int mSwValue;  // 开关状态，开的值 默认为1

private:
    void initTableWidget(QStringList &header);
    void addItemContent(int row, int column, const QString &content);
    void addRowContent(QStringList &list);
    void addInitRow();
    void addTableRows(int line);
    void delTableRows(int line);

private:
    Ui::ComTableWid *ui;
};

#endif // COMTABLEWID_H
