#include <QVBoxLayout>

#include "../includes/login_window.hpp"
#include "../includes/config.hpp"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , login_field{new QLineEdit{this}}
    , password_field{new QLineEdit{this}}
    , login_button{new QPushButton{config::login_window::LOGIN_LABEL, this}}
    , forgot_password_button{new ClickableLabel{config::login_window::FORGOT_PASSWORD_LABEL, this}} {
    Initialize();
}

void LoginWindow::Initialize() {
    setObjectName(config::login_window::OBJECT_NAME);

    auto *const logotype = new QLabel{this};
    logotype->setPixmap(QPixmap::fromImage(QImage{config::LOGOTYPE_PATH}).scaled(
        config::login_window::LOGOTYPE_WIDTH,
        config::login_window::LOGOTYPE_HEIGHT));

    login_field->setFixedSize(config::login_window::FIXED_FORM_LINE_WIDTH,
                              config::login_window::FIXED_FORM_LINE_HEIGHT);
    login_field->setPlaceholderText(config::login_window::LOGIN_PLACEHOLDER);

    password_field->setFixedSize(config::login_window::FIXED_FORM_LINE_WIDTH,
                                 config::login_window::FIXED_FORM_LINE_HEIGHT);
    password_field->setPlaceholderText(config::login_window::PASSWORD_PLACEHOLDER);
    password_field->setEchoMode(QLineEdit::Password);

    login_button->setFixedSize(config::login_window::FIXED_FORM_LINE_WIDTH,
                               config::login_window::FIXED_FORM_LINE_HEIGHT);
    login_button->setCursor(Qt::PointingHandCursor);

    auto *const vertical_layout = new QVBoxLayout{this};
    vertical_layout->addStretch(1);
    vertical_layout->addWidget(logotype, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(login_field, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(password_field, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(login_button, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(forgot_password_button, 0, Qt::AlignHCenter);
    vertical_layout->addStretch(1);
    vertical_layout->setSpacing(config::login_window::FORM_SPACING);

    connect(login_field, &QLineEdit::textChanged, this, &LoginWindow::SetPlaceholderColor);
    connect(password_field, &QLineEdit::textChanged, this, &LoginWindow::SetPlaceholderColor);
    connect(login_button, &QPushButton::clicked, this, &LoginWindow::LoginButtonClicked);
    connect(forgot_password_button, &ClickableLabel::clicked, this, &LoginWindow::ForgotPasswordButtonClicked);
}

void LoginWindow::SetPlaceholderColor() {
    auto *const line_edit = qobject_cast<QLineEdit *>(sender());
    if (line_edit->text().isEmpty()) {
        line_edit->setStyleSheet(QString("font-style: %1; color: %2").arg("italic", "#678cb8"));
    } else {
        line_edit->setStyleSheet(QString("font-style: %1; color: %2").arg("normal", "black"));
    }
}

void LoginWindow::LoginButtonClicked() {
    // TODO: implement
}

void LoginWindow::ForgotPasswordButtonClicked() {
    // TODO: implement
}
