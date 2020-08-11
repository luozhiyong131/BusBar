#ifndef INTERFACECHANGESIG_H
#define INTERFACECHANGESIG_H

#include <QObject>

class InterfaceChangeSig : public QObject
{
    Q_OBJECT
    explicit InterfaceChangeSig(QObject *parent = nullptr);
public:
    ~InterfaceChangeSig();
    static InterfaceChangeSig* get(QObject *parent = nullptr);

    void changeType(int);

signals:
     void typeSig(int);
};

#endif // INTERFACECHANGESIG_H
