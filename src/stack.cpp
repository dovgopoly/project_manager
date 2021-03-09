#include "../includes/stack.hpp"
#include "../includes/abstract_window.hpp"

#include <QWidget>

Stack::Stack(QWidget *parent)
    : QStackedLayout{parent} {
}

void Stack::Push(AbstractWindow *window) {
    addWidget(window);
    setCurrentWidget(window);
    m_stack.push(window);
    emit CurrentWidgetChanged(window);
}

void Stack::Pop() {
    removeWidget(currentWidget());
    m_stack.pop();
    assert(!m_stack.empty());
    setCurrentWidget(m_stack.top());
    emit CurrentWidgetChanged(m_stack.top());
}