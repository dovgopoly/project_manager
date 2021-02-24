#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>
#include <optional>

#include "ticket.hpp"

class Project {
 public:
    Project() = default;
    ~Project() = default;
    Project(const Project &) = default;
    Project &operator=(const Project &) = default;
    Project(int id, QString name, QUrl icon, std::optional<QList<Ticket>> tickets = std::nullopt);

    int GetId() const;
    QString GetName() const;
    QUrl GetIcon() const;
    std::optional<QList<Ticket>> GetTickets() const;

 private:
    int m_id;
    QString m_name;
    QUrl m_icon;
    std::optional<QList<Ticket>> m_tickets;
};

Q_DECLARE_METATYPE(Project);

#endif