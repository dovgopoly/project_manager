#ifndef ABSTRACT_WINDOW_HPP
#define ABSTRACT_WINDOW_HPP

#include <QWidget>

#include "stack.hpp"

class AbstractWindow : public QWidget {
 Q_OBJECT
 public:
    Stack &GetStack();

    virtual int GetHeaderFlags() const;
    virtual QString GetHeaderTitle() const;

 protected:
    explicit AbstractWindow(Stack &stack, QWidget *parent = nullptr);

    void SetStyleSheet(const QString &qss_file_path);

 private:
    Stack &m_stack;

 public slots:
    void PutSelfToStack();
    void RemoveSelfFromStack();
};

#endif