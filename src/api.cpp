#include "../includes/api.hpp"

Api::Api(QObject *parent)
    : QObject{parent}
    , network_manager{new QNetworkAccessManager{this}} {
    Initialize();
}

Api &Api::GetInstance() {
    static Api api;
    return api;
}

void Api::Initialize() {
    connect(network_manager, &QNetworkAccessManager::sslErrors, this, &Api::IgnoreSslErrors);
    connect(network_manager, &QNetworkAccessManager::finished, this, &Api::ReceiveReply);
}

void Api::IgnoreSslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    reply->ignoreSslErrors(errors);
}

void Api::ReceiveReply(QNetworkReply *reply) {
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        const auto reply_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        switch (static_cast<HttpCode>(reply_code)) {
            case HttpCode::OK: {
                qDebug() << "200 OK";
                emit ReadyJson(QJsonDocument::fromJson(reply->readAll()));
                break;
            }
            case HttpCode::UNAUTHORIZED: {
                qDebug() << "401 UNAUTHORIZED";
                break;
            }
            case HttpCode::NOT_FOUND: {
                qDebug() << "404 NOT FOUND";
                break;
            }
            default: {
                qDebug() << reply_code << "unknown code";
                break;
            }
        }
    } else {
        qDebug() << "Reply error:" << reply->errorString();
    }
}

void Api::Get(const QUrl &url, const QMap<QString, QString> &headers) const {
    network_manager->get(BuildRequest(url, headers));
}

void Api::Post(const QUrl &url, const QMap<QString, QString> &headers, const QString &data) const {
    network_manager->post(BuildRequest(url, headers), data.toUtf8());
}

QNetworkRequest Api::BuildRequest(const QUrl &url, const QMap<QString, QString> &headers) const {
    QNetworkRequest request;
    request.setUrl(url);
    for (const auto &[key, value] : headers.toStdMap()) {
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }
    return request;
}
