#ifndef ABSTRACT_REQUESTER_HPP
#define ABSTRACT_REQUESTER_HPP

#include <variant>

#include "api.hpp"

class AbstractRequester : public QObject {
 Q_OBJECT
 protected:
    explicit AbstractRequester(QObject *parent = nullptr);

 signals:
    void ErrorsOccurred(const std::variant<QString, Api::HttpCode> &reason);
    void ResponseReady(const QByteArray &response);

 protected slots:
    void ReceiveData();
};

#endif