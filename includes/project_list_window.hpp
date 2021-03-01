#ifndef PROJECT_LIST_WINDOW_HPP
#define PROJECT_LIST_WINDOW_HPP

#include <QWidget>

#include "abstract_window.hpp"

class ProjectListWindow : public AbstractWindow {
 Q_OBJECT
 public:
    explicit ProjectListWindow(QStackedLayout &stack, QWidget *parent = nullptr);
    ~ProjectListWindow() override = default;

 private:
    void Initialize();
};


#endif