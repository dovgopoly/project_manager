#include "../includes/abstract_window.hpp"

#include <QFile>

AbstractWindow::AbstractWindow(QStackedLayout &stack, QWidget *parent)
    : QWidget{parent}
    , m_stack{stack}
    , m_previous_widget{stack.isEmpty() ? nullptr : stack.currentWidget()} {
}

void AbstractWindow::PutSelfToStack() {
    m_stack.addWidget(this);
    m_stack.setCurrentWidget(this);
}

void AbstractWindow::RemoveSelfFromStack() {
    m_stack.removeWidget(this);
    m_stack.setCurrentWidget(m_previous_widget);
}

void AbstractWindow::SetStyleSheet(const QString &qss_file_path) {
    QFile file{qss_file_path};
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

QStackedLayout &AbstractWindow::GetStack() {
    return m_stack;
}