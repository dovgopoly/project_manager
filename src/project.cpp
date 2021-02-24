#include "../includes/project.hpp"

#include <utility>

Project::Project(int id, QString name, QUrl icon, std::optional<QList<Ticket>> tickets)
    : m_id{id}
    , m_name{std::move(name)}
    , m_icon{std::move(icon)}
    , m_tickets{std::move(tickets)} {
}

int Project::GetId() const {
    return m_id;
}

QString Project::GetName() const {
    return m_name;
}

QUrl Project::GetIcon() const {
    return m_icon;
}

std::optional<QList<Ticket>> Project::GetTickets() const {
    return m_tickets;
}
