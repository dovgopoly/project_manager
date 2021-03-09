#ifndef PROJECT_ICON_LIST_DELEGATE_HPP
#define PROJECT_ICON_LIST_DELEGATE_HPP

#include <QStyledItemDelegate>

class ProjectIconDelegate : public QStyledItemDelegate {
    Q_OBJECT
 public:
    explicit ProjectIconDelegate(QObject *parent = nullptr);
    ~ProjectIconDelegate() override = default;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif