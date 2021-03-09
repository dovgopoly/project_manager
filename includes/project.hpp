#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>
#include <optional>

#include "ticket.hpp"
#include "image.hpp"

class Project {
 public:
    Project() = default;
    ~Project() = default;
    Project(const Project &) = default;
    Project &operator=(const Project &) = default;
    Project(int id, QString name, const QUrl &icon);

    int GetId() const;
    QString GetName() const;
    Image *GetIcon() const;

 private:
    int m_id;
    QString m_name;
    Image *m_icon;
};

Q_DECLARE_METATYPE(Project);

#endif