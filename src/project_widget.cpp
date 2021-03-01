#include <QHBoxLayout>

#include "../includes/project_widget.hpp"

ProjectWidget::ProjectWidget(const Project &project, QWidget *parent)
    : QWidget{parent} {

    Initialize(project);
}

void ProjectWidget::Initialize(const Project &project) {
    using namespace config;
    using namespace config::project_widget;

    setAttribute(Qt::WA_StyledBackground, true);

    setContentsMargins(MARGINS);
    auto *const horizontal_layout = new QHBoxLayout{this};

    horizontal_layout->setSpacing(SPACING);
    horizontal_layout->setContentsMargins(ZERO_MARGINS);

    horizontal_layout->addWidget(project.GetIcon());
    horizontal_layout->addWidget(new QLabel{project.GetName()});
}
