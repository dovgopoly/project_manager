#include "../includes/abstract_requester.hpp"

AbstractRequester::AbstractRequester(QObject *parent)
    : QObject(parent) {
}

void AbstractRequester::ReceiveData() {
    auto *const reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        const auto reply_code =
            static_cast<Api::HttpCode>(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt());
        if (reply_code == Api::HttpCode::OK) {
            emit ResponseReady(reply->readAll());
        } else {
            emit ErrorsOccurred(reply_code);
        }
    } else {
        emit ErrorsOccurred(reply->errorString());
    }
}
