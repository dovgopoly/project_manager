#ifndef ABSTRACT_WINDOW_HPP
#define ABSTRACT_WINDOW_HPP

#include <QWidget>
#include <QStackedLayout>

class AbstractWindow : public QWidget {
 Q_OBJECT
 public:
    explicit AbstractWindow(QStackedLayout &stack, QWidget *parent = nullptr);
    ~AbstractWindow() override = default;

 protected:
    void PutSelfToStack();
    void RemoveSelfFromStack();
    QStackedLayout &GetStack();
    void SetStyleSheet(const QString &qss_file_path);

 private:
    QStackedLayout &m_stack;
    QWidget *m_previous_widget;
};

#endif