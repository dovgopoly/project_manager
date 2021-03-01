#include "../includes/api.hpp"

Api::Api(QObject *parent)
    : QObject{parent}
    , m_network_manager{new QNetworkAccessManager{this}} {
    connect(m_network_manager, &QNetworkAccessManager::sslErrors, this, &Api::IgnoreSslErrors);
    connect(m_network_manager, &QNetworkAccessManager::finished, m_network_manager, &QNetworkAccessManager::deleteLater);
}

Api &Api::GetInstance() {
    static Api api;
    return api;
}

void Api::IgnoreSslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    reply->ignoreSslErrors(errors);
}

QNetworkReply *Api::Get(const QUrl &url, const QMap<QString, QString> &headers) const {
    return m_network_manager->get(BuildRequest(url, headers));
}

QNetworkReply *Api::Post(const QUrl &url, const QMap<QString, QString> &headers, const QString &data) const {
    return m_network_manager->post(BuildRequest(url, headers), data.toUtf8());
}

QNetworkRequest Api::BuildRequest(const QUrl &url, const QMap<QString, QString> &headers) const {
    QNetworkRequest request;
    request.setUrl(url);
    for (const auto &[key, value] : headers.toStdMap()) {
        request.setRawHeader(key.toUtf8(), value.toUtf8());
    }
    return request;
}
