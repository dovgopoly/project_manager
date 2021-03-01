#include <QLabel>
#include <QHBoxLayout>
#include <QListView>

#include "../includes/project_list_window.hpp"
#include "../includes/config.hpp"
#include "../includes/image.hpp"
#include "../includes/project_model.hpp"
#include "../includes/project_delegate.hpp"

ProjectListWindow::ProjectListWindow(QStackedLayout &stack, QWidget *parent)
    : AbstractWindow{stack, parent} {

    Initialize();
    PutSelfToStack();
}

void ProjectListWindow::Initialize() {
    using namespace config;
    using namespace config::project_list_window;

    setAttribute(Qt::WA_StyledBackground, true);

    auto *const header = new QWidget{this};
    header->setFixedHeight(HEADER_HEIGHT);

    auto *const header_logotype =
        new Image{LOGOTYPE_PATH, HEADER_LOGOTYPE_WIDTH, HEADER_LOGOTYPE_HEIGHT, Image::HighQuality, this};
    auto *const header_label = new QLabel{HEADER_LABEL, this};

    auto *const header_layout = new QHBoxLayout{header};
    header_layout->addWidget(header_logotype);
    header_layout->addWidget(header_label);
    header_layout->setAlignment(Qt::AlignCenter);

    auto *const project_list_view = new QListView{this};
    project_list_view->setModel(new ProjectModel);
    project_list_view->setItemDelegate(new ProjectDelegate);

    auto *const main_layout = new QVBoxLayout{this};
    main_layout->setSpacing(ZERO_SPACING);
    main_layout->setContentsMargins(ZERO_MARGINS);
    main_layout->addWidget(header);
    main_layout->addWidget(project_list_view);
}
