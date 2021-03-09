#include <QEvent>

#include "../includes/project.hpp"
#include "../includes/project_icon_delegate.hpp"
#include "../includes/project_model.hpp"
#include "../includes/config.hpp"

ProjectIconDelegate::ProjectIconDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {
}

void ProjectIconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    using namespace config::ticket_list_window::icon_item;

    if (!index.isValid()) {
        return;
    }

    const auto project = qvariant_cast<Project>(index.model()->data(index, Qt::DisplayRole));
    const auto pixmap =
        project.GetIcon()->pixmap().scaled(WIDTH, HEIGHT, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    const bool hover = option.state & QStyle::State_MouseOver;

    const auto chosen_project = index.model()->data(QModelIndex{}, ProjectModel::ChosenProjectRole);

    const auto content_rect =
        option.rect.adjusted(CONTENT_MARGIN, CONTENT_MARGIN, -CONTENT_MARGIN, -CONTENT_MARGIN);

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

    painter->drawPixmap(content_rect, pixmap);

    painter->restore();
}

QSize ProjectIconDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    using namespace config::ticket_list_window;

    if (!index.isValid()) {
        return QSize{};
    }
    return QSize{0, PROJECT_ICON_ITEM_HEIGHT};
}

