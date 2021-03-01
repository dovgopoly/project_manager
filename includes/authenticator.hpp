#ifndef AUTHENTICATOR_HPP
#define AUTHENTICATOR_HPP

#include "abstract_requester.hpp"

class Authenticator : public AbstractRequester {
 Q_OBJECT
 public:
    Authenticator(const Authenticator &) = delete;
    Authenticator &operator=(const Authenticator &) = delete;

    static Authenticator &GetInstance();

    void AuthenticateUser(const QString &login, const QString &password) const;

 private:
    explicit Authenticator(QObject *parent = nullptr);
};

#endif