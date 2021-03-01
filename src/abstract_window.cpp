#include "../includes/abstract_window.hpp"

#include <QFile>

AbstractWindow::AbstractWindow(QStackedLayout &stack, QWidget *parent)
    : QWidget{parent}
    , m_stack{stack} {
}

void AbstractWindow::PutSelfToStack() {
    m_stack.addWidget(this);
    m_stack.setCurrentWidget(this);
}

void AbstractWindow::RemoveSelfFromStack() {
    m_stack.removeWidget(this);
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