#include <QEvent>

#include "../includes/ticket_delegate.hpp"
#include "../includes/ticket.hpp"
#include "../includes/priority_widget.hpp"
#include "../includes/config.hpp"

TicketDelegate::TicketDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {
}

void TicketDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    using namespace config::ticket_list_window::ticket_item;

    if (!index.isValid()) {
        return;
    }

    const auto ticket = qvariant_cast<Ticket>(index.model()->data(index, Qt::DisplayRole));

    const auto ticket_id = ticket.GetId();
    const auto &ticket_name = ticket.GetName();
    const auto &ticket_description = ticket.GetDescription();
    const auto ticket_priority = ticket.GetPriority();

    const bool hover = option.state & QStyle::State_MouseOver;
    const auto content_rect =
        option.rect.adjusted(CONTENT_MARGIN, CONTENT_MARGIN, -CONTENT_MARGIN, -CONTENT_MARGIN);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    QLinearGradient gradient;
    gradient.setStart(0, 0);
    gradient.setFinalStop(option.rect.width(), option.rect.height());
    gradient.setColorAt(0, GRADIENT_BEGIN_COLOR);
    gradient.setColorAt(1, GRADIENT_END_COLOR);

    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);

    painter->drawRoundedRect(option.rect.topLeft().x() + SHADOW_THICKNESS,
                             option.rect.topLeft().y() + SHADOW_THICKNESS,
                             option.rect.width(),
                             option.rect.height(),
                             RADIUS,
                             RADIUS);

    if (hover) {
        painter->setBrush(HOVER_COLOR);
    } else {
        painter->setBrush(Qt::white);
    }
    painter->drawRoundedRect(option.rect, RADIUS, RADIUS);

    QFont header_font;
    header_font.setWeight(QFont::Bold);
    header_font.setPixelSize(HEADER_FONT_SIZE);
    painter->setFont(header_font);
    painter->setPen(Qt::black);
    painter->drawText(content_rect.left(),
                      content_rect.top() + HEADER_FONT_SIZE,
                      QString{"%1. %2"}.arg(QString::number(ticket_id), ticket_name));

    QFont description_font;
    description_font.setPixelSize(DESCRIPTION_FONT_SIZE);
    description_font.setWeight(QFont::Normal);

    if (!ticket_description.isEmpty()) {
        painter->setFont(description_font);
        painter->setPen(Qt::darkGray);

        const int max_letters_count = MAX_LETTERS_COEFFICIENT * content_rect.width() / DESCRIPTION_FONT_SIZE;

        if (ticket_description.size() <= max_letters_count) {
            painter->drawText(content_rect.left(),
                              content_rect.top() + HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + SPACING,
                              ticket_description);
        } else {
            painter->drawText(content_rect.left(),
                              content_rect.top() + HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + SPACING,
                              ticket_description.mid(0, max_letters_count) + "...");
        }
    } else {
        description_font.setItalic(true);
        painter->setFont(description_font);
        painter->setPen(Qt::black);

        painter->drawText(content_rect.left(),
                          content_rect.top() + HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + SPACING,
                          EMPTY_DESCRIPTION_LABEL);
    }

    const auto priority_rect =
        content_rect.adjusted(0, HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + 3 * SPACING, 0, 0);

    painter->restore();

    auto *const priority_widget = new PriorityWidget();

    priority_widget->SetRadius(PRIORITY_WIDGET_RADIUS);
    priority_widget->SetVerticalSpacing(PRIORITY_WIDGET_VERTICAL_SPACING);
    priority_widget->SetHorizontalSpacing(PRIORITY_WIDGET_HORIZONTAL_SPACING);
    priority_widget->SetPriority(ticket_priority);
    priority_widget->setGeometry(priority_rect);

    auto painter_device = painter->device();
    painter->end();

    QPixmap pixmap(priority_widget->sizeHint());
    pixmap.fill(Qt::white);

    priority_widget->render(&pixmap, QPoint{}, QRegion{}, QWidget::DrawChildren);
    painter->begin(painter_device);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPixmap(priority_rect.topLeft(), pixmap);
}

QSize TicketDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    using namespace config::ticket_list_window::ticket_item;

    if (!index.isValid()) {
        return QSize{};
    }
    return QSize(0, HEIGHT);
}
