#ifndef TICKET_MODEL_HPP
#define TICKET_MODEL_HPP

#include <QAbstractListModel>

#include "ticket.hpp"

class TicketModel : public QAbstractListModel {
 Q_OBJECT
 public:
    explicit TicketModel(QObject *parent = nullptr);
    ~TicketModel() override = default;

    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void LoadTicketsForProject(int project_id);

    enum Roles {
        ChosenTicketRole = Qt::UserRole,
    };

 private:
    void Initialize();

    QList<Ticket> m_ticket_list;
    QModelIndex m_chosen_ticket;

 private slots:
    void ParseTicketsToList(const QByteArray &json_to_parse);
};

#endif