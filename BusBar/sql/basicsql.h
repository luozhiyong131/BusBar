#ifndef BASICSQL_H
#define BASICSQL_H

#include <QtSql>
#include <QObject>

class BasicSql : public QObject
{
    Q_OBJECT
public:
    explicit BasicSql(QObject *parent = 0);

    enum{Remove,Insert,Update};
    virtual QString tableName() = 0;
    int  maxId(const QString &idName = "id");
    void remove(const QString &condition);

    int  maxId(const QString &idName, const QString &condition);
    int count(const QString &column_name, const QString &condition);

    QStringList listColumn(const QString &column_name, const QString &condition);
    QVector<int> listColumnToInt(const QString &column_name, const QString &condition);
    QVector<int> selectIds(const QString &condition);

    bool updateColumn(const QString& column_name, double value, const QString &condition);
    bool updateColumn(const QString& column_name, const QString& value, const QString &condition);

signals:
    void itemChanged(int id,int type);
protected:
    void throwError(const QSqlError& err); /// inline static
    QString tableMarking();
    void setTableMarking(const QString& marking);
private:
    static void initDb();
    
};




#endif // BASICSQL_H
