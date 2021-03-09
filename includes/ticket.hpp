#ifndef TICKET_HPP
#define TICKET_HPP

#include <QObject>
#include <QString>

class Ticket {
 public:
    Ticket() = default;
    ~Ticket() = default;
    Ticket(const Ticket &) = default;
    Ticket &operator=(const Ticket &) = default;
    Ticket(int id, QString name, QString description, int priority);

    int GetId() const;
    QString GetName() const;
    QString GetDescription() const;
    int GetPriority() const;

    void SetId(int id);
    void SetName(QString name);
    void SetDescription(QString description);
    void SetPriority(int priority);

 private:
    int m_id;
    QString m_name;
    QString m_description;
    int m_priority;
};

Q_DECLARE_METATYPE(Ticket);

#endif