#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>
#include <QStackedLayout>

#include <stack>

#include "abstract_window.hpp"
#include "login_window.hpp"
#include "image.hpp"

class Header;

class MainWindow : public QWidget {
 Q_OBJECT
 public:
    explicit MainWindow(QWidget *parent = nullptr);

 private:
    void SetupHeader(AbstractWindow *current_top_window);

    void Initialize();

    Stack *const m_stack;
    Header *const m_header;

 private slots:
    void SetupWindow(AbstractWindow *current_top_window);
};

#endif