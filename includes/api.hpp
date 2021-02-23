#ifndef API_HPP
#define API_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QUrl>

class Api : public QObject {
 Q_OBJECT
 public:
    Api(const Api &) = delete;
    Api &operator=(const Api &) = delete;

    static Api &GetInstance();

    void Get(const QUrl &url, const QMap<QString, QString> &headers) const;
    void Post(const QUrl &url, const QMap<QString, QString> &headers, const QString &data) const;

 private:
    explicit Api(QObject *parent = nullptr);
    ~Api() override = default;

    enum class HttpCode {
        OK = 200,
        UNAUTHORIZED = 401,
        NOT_FOUND = 404
    };

    void Initialize();
    QNetworkRequest BuildRequest(const QUrl &url, const QMap<QString, QString> &headers) const;

    QNetworkAccessManager *const network_manager;

 signals:
    void ReadyJson(const QJsonDocument &json);

 private slots:
    void IgnoreSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
    void ReceiveReply(QNetworkReply *reply);
};

#endif