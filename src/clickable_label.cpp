#include "../includes/clickable_label.hpp"

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel{parent} {
    setCursor(Qt::PointingHandCursor);
}

ClickableLabel::ClickableLabel(const QString &text, QWidget *parent)
    : QLabel{text, parent} {
    setCursor(Qt::PointingHandCursor);
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();
}

void ClickableLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    emit doubleClicked();
}
