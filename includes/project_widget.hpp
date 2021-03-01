#ifndef PROJECT_WIDGET_HPP
#define PROJECT_WIDGET_HPP

#include <QWidget>

#include "project.hpp"
#include "config.hpp"
#include "image.hpp"

class ProjectWidget : public QWidget {
 Q_OBJECT
 public:
    explicit ProjectWidget(const Project &project, QWidget *parent = nullptr);
    ~ProjectWidget() override = default;

 private:
    void Initialize(const Project &project);
};

#endif