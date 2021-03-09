#ifndef PROJECT_DELEGATE_HPP
#define PROJECT_DELEGATE_HPP

#include <QStyledItemDelegate>
#include <QPainter>

class ProjectDelegate : public QStyledItemDelegate {
 Q_OBJECT
 public:
    explicit ProjectDelegate(QObject *parent = nullptr);
    ~ProjectDelegate() override = default;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif