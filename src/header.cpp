#include <QHBoxLayout>

#include "../includes/header.hpp"
#include "../includes/config.hpp"

Header::Header(QWidget *parent)
    : QWidget{parent}
    , m_back_arrow_icon{new Image{config::main_window::header::ARROW_BACK_ICON_PATH,
                                  config::main_window::header::ARROW_ICON_WIDTH,
                                  config::main_window::header::ARROW_ICON_HEIGHT,
                                  Image::HighQuality,
                                  this}}
    , m_title{new QLabel{this}} {

    Initialize();
}

void Header::Initialize() {
    using namespace config;
    using namespace config::main_window::header;

    setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(HEADER_HEIGHT);

    setStyleSheet("background-color: white; font-size: 18px; font-weight: normal;");

    auto *const logotype_icon =
        new Image{LOGOTYPE_PATH, LOGOTYPE_WIDTH, LOGOTYPE_HEIGHT, Image::HighQuality, this};

    auto *const main_horizontal_layout = new QHBoxLayout{this};
    main_horizontal_layout->setContentsMargins(HEADER_MARGINS);
    main_horizontal_layout->setAlignment(Qt::AlignVCenter);

    main_horizontal_layout->addWidget(m_back_arrow_icon);
    main_horizontal_layout->addStretch(1);
    main_horizontal_layout->addWidget(logotype_icon);
    main_horizontal_layout->addWidget(m_title);
    main_horizontal_layout->addStretch(1);
}

void Header::SetTitle(const QString &title) {
    m_title->setText(title);
}

void Header::SetProperties(int properties) {
    if (properties & ShowHeader) {
        show();
    } else {
        hide();
    }
    if (properties & ShowBackArrow) {
        m_back_arrow_icon->show();
    } else {
        m_back_arrow_icon->hide();
    }
    if (properties & ShowTitle) {
        m_title->show();
    } else {
        m_title->hide();
    }
}