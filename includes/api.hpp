#ifndef API_HPP
#define API_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QUrl>
#include <QPixmap>
#include <QImage>

#include <optional>

class Api : public QObject {
 Q_OBJECT
 public:
    Api(const Api &) = delete;
    Api &operator=(const Api &) = delete;

    static Api &GetInstance();

    QNetworkReply *Get(const QUrl &url, const QMap<QString, QString> &headers = {}) const;
    QNetworkReply *Post(const QUrl &url, const QMap<QString, QString> &headers, const QString &data) const;

    enum class HttpCode {
        OK = 200,
        UNAUTHORIZED = 401,
        NOT_FOUND = 404
    };
 private:
    explicit Api(QObject *parent = nullptr);
    ~Api() override = default;

    QNetworkRequest BuildRequest(const QUrl &url, const QMap<QString, QString> &headers) const;

    QNetworkAccessManager *const m_network_manager;


 private slots:
    void IgnoreSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
};

#endif