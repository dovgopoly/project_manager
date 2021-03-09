#ifndef TICKET_DELEGATE_HPP
#define TICKET_DELEGATE_HPP

#include <QStyledItemDelegate>
#include <QPainter>

class TicketDelegate : public QStyledItemDelegate {
 Q_OBJECT
 public:
    explicit TicketDelegate(QObject *parent = nullptr);
    ~TicketDelegate() override = default;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

 private:
    QModelIndex m_last_pressed_index;
};

#endif