#ifndef STACK_HPP
#define STACK_HPP

#include <QStackedLayout>

#include <stack>

class AbstractWindow;

class Stack : public QStackedLayout {
 Q_OBJECT
 public:
    explicit Stack(QWidget *parent = nullptr);

 private:
    std::stack<AbstractWindow *> m_stack;

 signals:
    void CurrentWidgetChanged(AbstractWindow *window);

 public slots:
    void Push(AbstractWindow *window);
    void Pop();
};

#endif