#include "../includes/ticket.hpp"

Ticket::Ticket(const int id, QString name, QString description, const int priority)
    : m_id{id}
    , m_name{std::move(name)}
    , m_description{std::move(description)}
    , m_priority{priority} {
}

int Ticket::GetId() const {
    return m_id;
}

QString Ticket::GetName() const {
    return m_name;
}

QString Ticket::GetDescription() const {
    return m_description;
}

int Ticket::GetPriority() const {
    return m_priority;
}

void Ticket::SetId(const int id) {
    m_id = id;
}

void Ticket::SetName(QString name) {
    m_name = std::move(name);
}

void Ticket::SetDescription(QString description) {
    m_description = std::move(description);
}

void Ticket::SetPriority(const int priority) {
    m_priority = priority;
}
