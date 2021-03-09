#include <QEvent>

#include "../includes/project.hpp"
#include "../includes/project_icon_delegate.hpp"
#include "../includes/project_model.hpp"

ProjectIconDelegate::ProjectIconDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {
}

void ProjectIconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) {
        return;
    }

    const auto project = qvariant_cast<Project>(index.model()->data(index, Qt::DisplayRole));

    const auto pixmap = project.GetIcon()->pixmap().scaled(50, 50);
    bool hover = option.state & QStyle::State_MouseOver;

    const auto chosen_project = index.model()->data(QModelIndex{}, ProjectModel::ChosenProjectRole);

    painter->save();

    if (index == chosen_project) {
        painter->setBrush(QBrush(Qt::blue));
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
    } else if (hover) {
        painter->setBrush(QBrush(Qt::lightGray));
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
    }

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->drawPixmap(10, option.rect.topLeft().y() + 10, pixmap);

    painter->restore();
}

QSize ProjectIconDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) {
        return QSize{};
    }
    return QSize{0, 70};
}

