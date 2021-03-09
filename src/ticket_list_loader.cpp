#include <QString>

#include "../includes/ticket_list_loader.hpp"
#include "../includes/private_config.hpp"

TicketListLoader::TicketListLoader(QObject *parent)
    : AbstractRequester{parent} {
}

TicketListLoader &TicketListLoader::GetInstance() {
    static TicketListLoader ticket_list_loader;
    return ticket_list_loader;
}

void TicketListLoader::DownloadTicketList(const QString &token, const int id) const {
    using namespace private_config;
    auto *const response = Api::GetInstance().Get(
        QString{"%1/project/tickets/%2/"}.arg(LINK_PREFIX, QString::number(id + 1)),
        {{"authorization", token}}
    );
    connect(response, &QNetworkReply::finished, this, &TicketListLoader::ReceiveData);
}
