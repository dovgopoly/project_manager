#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include <QStackedLayout>

#include "login_window.hpp"

class MainWindow : public QWidget {
 Q_OBJECT
 public:
    explicit MainWindow(QWidget *parent = nullptr);

 private:
    void Initialize();
    QStackedLayout *const m_stack;
};

#endif