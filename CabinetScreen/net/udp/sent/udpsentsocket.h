#ifndef UDPSENTSOCKET_H
#define UDPSENTSOCKET_H

#include <QtCore>
#include <QtNetwork>

#define UDP_HB_PORT     18725 /*UDP心跳端口*/
#define UDP_SENT_PORT   18750 /*UDP发送端口*/

#define IF_ETH_NUM  2
#define ETH_ONE     "eth0"
#define ETH_TWO     "eth1"

void udp_sent_data(int i, const QString &ip, int port, uchar *buf, uint len);
void udp_sent_data(int i, const QString &ip, uchar *buf, uint len);
#endif // UDPSENTSOCKET_H
