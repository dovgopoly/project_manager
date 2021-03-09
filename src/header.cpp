#include <QHBoxLayout>
#include <QFile>

#include "../includes/header.hpp"
#include "../includes/config.hpp"

Header::Header(QWidget *parent)
    : QWidget{parent}
    , m_back_arrow_icon{new Image{config::main_window::header::ARROW_BACK_ICON_PATH,
                                  config::main_window::header::ARROW_ICON_WIDTH,
                                  config::main_window::header::ARROW_ICON_HEIGHT,
                                  Image::HighQuality,
                                  this}}
    , m_title{new QLabel{this}}
    , m_main_layout{new QHBoxLayout{this}} {

    Initialize();
}

void Header::Initialize() {
    using namespace config;
    using namespace config::main_window::header;

    setAttribute(Qt::WA_StyledBackground, true);
    setFixedHeight(HEADER_HEIGHT);

    QFile file{HEADER_STYLESHEET};
    file.open(QFile::ReadOnly);
    setStyleSheet(file.readAll());
    file.close();

    auto *const logotype_icon =
        new Image{LOGOTYPE_PATH, LOGOTYPE_WIDTH, LOGOTYPE_HEIGHT, Image::HighQuality, this};

    m_main_layout->setSpacing(ZERO_SPACING);
    m_main_layout->setContentsMargins(HEADER_MARGINS_WITHOUT_BACK_ARROW);
    m_main_layout->setAlignment(Qt::AlignVCenter);

    m_back_arrow_icon->setCursor(Qt::PointingHandCursor);

    m_main_layout->addWidget(m_back_arrow_icon);
    m_main_layout->addStretch(1);
    m_main_layout->addWidget(logotype_icon);
    m_main_layout->addWidget(m_title);
    m_main_layout->addStretch(1);

}

void Header::SetTitle(const QString &title) {
    m_title->setText(title);
}

void Header::SetProperties(int properties) {
    using namespace config::main_window::header;
    if (properties & ShowHeader) {
        show();
    } else {
        hide();
    }
    if (properties & ShowBackArrow) {
        m_back_arrow_icon->show();
        m_main_layout->setContentsMargins(HEADER_MARGINS_WITH_BACK_ARROW);
    } else {
        m_back_arrow_icon->hide();
        m_main_layout->setContentsMargins(HEADER_MARGINS_WITHOUT_BACK_ARROW);
    }
    if (properties & ShowTitle) {
        m_title->show();
    } else {
        m_title->hide();
    }
}
