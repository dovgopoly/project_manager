#include <QPaintEvent>
#include <QPainter>

#include <algorithm>

#include "../includes/priority_widget.hpp"

PriorityWidget::PriorityWidget(QWidget *parent)
    : QWidget{parent} {
}

void PriorityWidget::paintEvent(QPaintEvent *paint_event) {
    const auto &rect = paint_event->rect();
    auto *const painter = new QPainter{this};

    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, true);

    for (int dot_index = 0; dot_index < HORIZONTAL_DOTS_COUNT; ++dot_index) {
        QColor circle_color;
        if (dot_index + 1 > m_priority) {
            if (dot_index < 3) {
                circle_color = QColor{Qt::gray};
            } else {
                circle_color = QColor{Qt::red};
            }
            circle_color.setAlphaF(.3f);
        } else {
            if (dot_index < 3) {
                circle_color = QColor{Qt::black};
            } else {
                circle_color = QColor{Qt::darkRed};
            }
        }
        painter->setBrush(circle_color);

        const int diameter = m_radius * 2;

        painter->drawEllipse(rect.left() + dot_index * (diameter + m_horizontal_spacing),
                             rect.top(),
                             diameter,
                             diameter);

        painter->drawEllipse(rect.left() + dot_index * (diameter + m_horizontal_spacing),
                             rect.top() + diameter + m_vertical_spacing,
                             diameter,
                             diameter);
    }
    painter->end();
}

QSize PriorityWidget::sizeHint() const {
     return QSize{HORIZONTAL_DOTS_COUNT * m_radius * 2 + (HORIZONTAL_DOTS_COUNT - 1) * m_horizontal_spacing,
                 VERTICAL_DOTS_COUNT * m_radius * 2 + (VERTICAL_DOTS_COUNT - 1) * m_vertical_spacing};
}

void PriorityWidget::Increment() {
    if (m_priority < 5) {
        ++m_priority;
    }
}

void PriorityWidget::Decrement() {
    if (m_priority > 1) {
        --m_priority;
    }
}

void PriorityWidget::SetVerticalSpacing(const int vertical_spacing) {
    m_vertical_spacing = vertical_spacing;
}

void PriorityWidget::SetHorizontalSpacing(const int horizontal_spacing) {
    m_horizontal_spacing = horizontal_spacing;
}

void PriorityWidget::SetRadius(const int radius) {
    m_radius = radius;
}

void PriorityWidget::SetPriority(const int priority) {
    if (priority > 5) {
        m_priority = 5;
    } else if (priority < 1) {
        m_priority = 1;
    } else {
        m_priority = priority;
    }
}

int PriorityWidget::GetPriority() const {
    return m_priority;
}
