#ifndef XMPPCLIENT_H
#define XMPPCLIENT_H

#include <QObject>
#include "qxmpp/QXmppClient.h"
#include "qxmpp/QXmppLogger.h"
#include "qxmpp/QXmppCallManager.h"
#include "qxmpp/QXmppTransferManager.h"
#include "qxmpp/QXmppMucManager.h"
#include "Client.h"

class CGlobalUserQXmpp;
class CClientXmpp : public CClient
{
    Q_OBJECT

public:
    explicit CClientXmpp(QObject *parent = 0);
    virtual ~CClientXmpp();

    /**
     * @brief 登录  
     *
     * @param szUserName：用户名  
     * @param szPassword：登录密码  
     * @param status：登录状态  
     * @return int：成功返回0，失败返回非0  
     */
    virtual int Login(const QString& szUserName = QString(), 
                      const QString &szPassword = QString(),
                      CUserInfo::USER_INFO_STATUS status = CUserInfo::Online);
    //请求本地用户信息  
    virtual int RequestUserInfoLocale();
    //请求指定好友的信息  
    virtual int RequestUserInfoRoster(const QString& szId);
    //设置用户状态· 
    virtual int setClientStatus(CUserInfo::USER_INFO_STATUS status);

    /**
     * @brief //增加好友  
     *
     * @param szId：好友id
     * @return int：成功返回0，失败返回非0  
     */
    virtual int RosterAdd(const QString& szId, SUBSCRIBE_TYPE type = SUBSCRIBE_REQUEST,
                          const QString &szName = QString(), const QSet<QString> &groups = QSet<QString>());
    /**
     * @brief 删除好友  
     *
     * @param szId：好友Id
     * @return int：成功返回0，失败返回非0  
     */
    virtual int RosterRemove(const QString& szId);

    virtual int SendMessage(const QString& szId, const QString &szMsg);

private:
    QXmppPresence::AvailableStatusType StatusToPresence(CUserInfo::USER_INFO_STATUS status);
    CUserInfo::USER_INFO_STATUS StatusFromPresence(QXmppPresence::AvailableStatusType status);

    int InitConnect();

private slots:
    void slotRegisterConnected();
    void slotClientError(QXmppClient::Error e);
    void slotClientIqReceived(const QXmppIq &iq);
    void slotStateChanged(QXmppClient::State state);
    void slotRosterReceived();
    void slotClientVCardReceived();
    //得到好友详细信息时触发  
    void slotvCardReceived(const QXmppVCardIq&);
    void slotPresenceReceived(const QXmppPresence &presence);
    void slotItemAdded(const QString &szId);
    void slotItemChanged(const QString& szId);
    void slotItemRemoved(const QString& szId);

private:
    QXmppClient m_Client;
    QSharedPointer<CGlobalUserQXmpp> m_User;
    QXmppCallManager m_CallManager;
    QXmppMucManager m_MucManager;
    QXmppTransferManager m_TransferManager;
};

#endif // XMPPCLIENT_H