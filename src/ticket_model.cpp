#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../includes/ticket_model.hpp"
#include "../includes/ticket_list_loader.hpp"

TicketModel::TicketModel(QObject *parent)
    : QAbstractListModel{parent} {

    Initialize();
}

void TicketModel::Initialize() {
    auto &ticket_list_loader = TicketListLoader::GetInstance();
    connect(&ticket_list_loader, &TicketListLoader::ResponseReady, this, &TicketModel::ParseTicketsToList);
}

int TicketModel::rowCount(const QModelIndex &index) const {
    return m_ticket_list.count();
}

QVariant TicketModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        QVariant{};
    }
    switch (role) {
        case Qt::DisplayRole: {
            return QVariant::fromValue(m_ticket_list.at(index.row()));
        }
        case ChosenTicketRole: {
            return m_chosen_ticket;
        }
        default: {
            return QVariant{};
        }
    }
}

bool TicketModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    switch (role) {
        case Qt::EditRole: {
            m_ticket_list.replace(index.row(), qvariant_cast<Ticket>(value));
            return true;
        }
        case ChosenTicketRole: {
            m_chosen_ticket = qvariant_cast<QModelIndex>(value);
        }
        default: {
            return false;
        }
    }
}

Qt::ItemFlags TicketModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return QAbstractListModel::flags(index);
}

void TicketModel::ParseTicketsToList(const QByteArray &json_to_parse) {
    beginRemoveRows(QModelIndex(), 0, m_ticket_list.count() - 1);
    m_ticket_list.clear();
    endRemoveRows();

    const auto json_object = QJsonDocument::fromJson(json_to_parse).object();
    const auto tickets = json_object["tickets"].toArray();

    beginInsertRows(QModelIndex(), 0, tickets.count() - 1);
    for (const QJsonValue &ticket : tickets) {
        const auto ticket_object = ticket.toObject();
        const auto name = ticket_object["name"].toString();
        const auto description = ticket_object["description"].toString();
        const auto priority = ticket_object["priority"].toInt();
        const auto id = ticket_object["id"].toInt();
        m_ticket_list.emplace_back(id, name, description, priority);
    }
    endInsertRows();
}

void TicketModel::LoadTicketsForProject(const int project_id) {
    const auto &token = Authenticator::GetInstance().GetCurrentToken();
    auto &ticket_list_loader = TicketListLoader::GetInstance();
    ticket_list_loader.DownloadTicketList(token, project_id);
}
