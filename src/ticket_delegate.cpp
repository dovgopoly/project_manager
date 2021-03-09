#include <QEvent>

#include "../includes/ticket_delegate.hpp"
#include "../includes/ticket.hpp"
#include "../includes/priority_widget.hpp"

TicketDelegate::TicketDelegate(QObject *parent)
    : QStyledItemDelegate{parent} {
}

void TicketDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) {
        return;
    }

    const auto ticket = qvariant_cast<Ticket>(index.model()->data(index, Qt::DisplayRole));

    const auto ticket_id = ticket.GetId();
    const auto &ticket_name = ticket.GetName();
    const auto &ticket_description = ticket.GetDescription();
    const auto ticket_priority = ticket.GetPriority();

    const bool hover = option.state & QStyle::State_MouseOver;

    const auto content_rect = option.rect.adjusted(16, 16, -16, -16);

    painter->save();

    painter->setBrush(hover ? QColor(245, 245, 245) : Qt::white);
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(option.rect, 15, 15);


    constexpr int HEADER_FONT_SIZE = 18;
    constexpr int DESCRIPTION_FONT_SIZE = 14;

    QFont header_font;
    header_font.setWeight(QFont::Bold);
    header_font.setPixelSize(HEADER_FONT_SIZE);
    painter->setFont(header_font);
    painter->setPen(Qt::black);
    painter->drawText(content_rect.left(),
                      content_rect.top() + HEADER_FONT_SIZE,
                      QString::number(ticket_id) + ". " + ticket_name);

    QFont description_font;
    description_font.setPixelSize(DESCRIPTION_FONT_SIZE);
    description_font.setWeight(QFont::Normal);

    if (!ticket_description.isEmpty()) {
        painter->setFont(description_font);
        painter->setPen(Qt::darkGray);

        const int max_letters_count = content_rect.width() / DESCRIPTION_FONT_SIZE;
        assert(max_letters_count > 0);

        painter->drawText(content_rect.left(),
                          content_rect.top() + HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + 15,
                          ticket_description.size() < max_letters_count ?
                            ticket_description : ticket_description.mid(0, max_letters_count) + "...");
    } else {
        description_font.setItalic(true);
        painter->setFont(description_font);
        painter->setPen(Qt::black);

        painter->drawText(content_rect.left(),
                          content_rect.top() + HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + 15,
                          "No description yet :(");
    }

    const auto priority_rect = content_rect.adjusted(0, HEADER_FONT_SIZE + DESCRIPTION_FONT_SIZE + 15 + 25, 0, 0);
    painter->restore();

    auto *const priority_widget = new PriorityWidget();

    priority_widget->SetRadius(5);
    priority_widget->SetVerticalSpacing(2);
    priority_widget->SetHorizontalSpacing(2);
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
    if (!index.isValid()) {
        return QSize{};
    }
    return QSize(0, 130);
}
