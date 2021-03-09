#include <QEvent>
#include <QFontDatabase>

#include "../includes/project_delegate.hpp"
#include "../includes/project.hpp"
#include "../includes/config.hpp"
#include "../includes/project_model.hpp"

ProjectDelegate::ProjectDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {
}

void ProjectDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    using namespace config::project_list_window::project_item;

    if (!index.isValid()) {
        return;
    }

    const auto project = qvariant_cast<Project>(index.model()->data(index, Qt::DisplayRole));
    const auto project_icon =
        project.GetIcon()->pixmap().scaled(ICON_WIDTH, ICON_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    const auto project_name = project.GetName();
    const auto content_rect =
        option.rect.adjusted(CONTENT_MARGIN, CONTENT_MARGIN, -CONTENT_MARGIN, -CONTENT_MARGIN);
    const bool hover = option.state & QStyle::State_MouseOver;
    const auto chosen_project =
        qvariant_cast<QModelIndex>(index.model()->data(index, ProjectModel::ChosenProjectRole));

    painter->save();

    if (index == chosen_project) {
        painter->setBrush(Qt::blue);
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
    } else if (hover) {
        painter->setBrush(Qt::lightGray);
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
    } else {
        painter->setBrush(Qt::white);
        painter->setPen(Qt::NoPen);
        painter->drawRect(option.rect);
    }

    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPixmap(content_rect.topLeft(), project_icon);

    if (index == chosen_project) {
        painter->setPen(Qt::white);
    } else {
        painter->setPen(Qt::black);
    }

    QFont font;
    font.setPixelSize(FONT_SIZE);
    font.setWeight(QFont::Normal);

    painter->setFont(font);
    painter->drawText(content_rect.left() + project_icon.width() + SPACING,
                      content_rect.top() + (content_rect.height() + FONT_SIZE) / 2,
                      project_name);

    if (index.row() < index.model()->rowCount() - 1) {
        painter->setPen(QPen{Qt::gray, 1});
        painter->drawLine(option.rect.bottomLeft().x(),
                          option.rect.bottomLeft().y() + 2,
                          option.rect.bottomRight().x(),
                          option.rect.bottomRight().y() + 2);
    }

    painter->restore();
}

QSize ProjectDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    using namespace config::project_list_window::project_item;
    if (!index.isValid()) {
        return QSize{};
    }
    return QSize(0, 2 * CONTENT_MARGIN + ICON_HEIGHT);
}
