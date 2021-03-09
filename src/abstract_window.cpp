#include "../includes/abstract_window.hpp"
#include "../includes/header.hpp"

#include <QFile>

AbstractWindow::AbstractWindow(Stack &stack, QWidget *parent)
    : QWidget{parent}
    , m_stack{stack} {

    setAttribute(Qt::WA_StyledBackground, true);
}

void AbstractWindow::PutSelfToStack() {
    m_stack.Push(this);
}

void AbstractWindow::RemoveSelfFromStack() {
    m_stack.Pop();
}

void AbstractWindow::SetStyleSheet(const QString &qss_file_path) {
    QFile file{qss_file_path};
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();
}

Stack &AbstractWindow::GetStack() {
    return m_stack;
}

int AbstractWindow::GetHeaderFlags() const {
    return Header::NoFlags;
}

QString AbstractWindow::GetHeaderTitle() const {
    return QString{};
}
