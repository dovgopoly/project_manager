#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include "abstract_requester.hpp"

class Authenticator : public AbstractRequester {
 Q_OBJECT
 public:
    Q_DISABLE_COPY(Authenticator);

    static Authenticator &GetInstance();

    void AuthenticateUser(const QString &login, const QString &password) const;

    void SetCurrentToken(const QString &token);
    QString GetCurrentToken() const;

 private:
    explicit Authenticator(QObject *parent = nullptr);

    QString m_token;
};

#endif