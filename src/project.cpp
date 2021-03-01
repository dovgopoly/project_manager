#include "../includes/project.hpp"
#include "../includes/config.hpp"

#include <utility>

Project::Project(int id, QString name, const QUrl &url, std::optional<QList<Ticket>> tickets)
    : m_id{id}
    , m_name{std::move(name)}
    , m_icon{new Image{
        url,
        config::project_list_window::PROJECT_ICON_WIDTH,
        config::project_list_window::PROJECT_ICON_HEIGHT,
        Image::HighQuality | Image::RoundedCorners}}
    , m_tickets{std::move(tickets)} {
}

int Project::GetId() const {
    return m_id;
}

QString Project::GetName() const {
    return m_name;
}

Image *Project::GetIcon() const {
    return m_icon;
}

std::optional<QList<Ticket>> Project::GetTickets() const {
    return m_tickets;
}
