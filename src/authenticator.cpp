#include "../includes/authenticator.hpp"
#include "../includes/private_config.hpp"

Authenticator::Authenticator(QObject *parent)
    : AbstractRequester{parent} {
}

Authenticator &Authenticator::GetInstance() {
    static Authenticator authenticator;
    return authenticator;
}

void Authenticator::AuthenticateUser(const QString &login, const QString &password) const {
    using namespace private_config;
    auto *const response = Api::GetInstance().Post(
        QUrl{QString{"%1/project/login/"}.arg(LINK_PREFIX)},
        {{"content-type", "application/json"}},
        QString{R"({"login" : "%1", "password" : "%2"})"}.arg(login, password)
    );
    connect(response, &QNetworkReply::finished, this, &Authenticator::ReceiveData);
}
