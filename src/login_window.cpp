#include <QLabel>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>

#include "../includes/login_window.hpp"
#include "../includes/config.hpp"
#include "../includes/image.hpp"
#include "../includes/project_list_window.hpp"

LoginWindow::LoginWindow(QStackedLayout &stack, QWidget *parent)
    : AbstractWindow{stack, parent}
    , login_field{new QLineEdit{this}}
    , password_field{new QLineEdit{this}}
    , login_button{new QPushButton{config::login_window::LOGIN_BUTTON_LABEL, this}}
    , forgot_password_button{new QPushButton{config::login_window::FORGOT_PASSWORD_BUTTON_LABEL, this}} {
    Initialize();
    PutSelfToStack();
}

void LoginWindow::Initialize() {
    using namespace config;
    using namespace config::login_window;

    setAttribute(Qt::WA_StyledBackground, true);

    SetStyleSheet(STYLESHEET_PATH);
    setObjectName(OBJECT_NAME);

    auto *const logotype =
        new Image(LOGOTYPE_PATH, LOGOTYPE_WIDTH, LOGOTYPE_HEIGHT, Image::HighQuality | Image::RoundedCorners);

    login_field->setFixedSize(FIXED_FORM_LINE_WIDTH, FIXED_FORM_LINE_HEIGHT);
    login_field->setPlaceholderText(LOGIN_FIELD_PLACEHOLDER);

    password_field->setFixedSize(FIXED_FORM_LINE_WIDTH, FIXED_FORM_LINE_HEIGHT);
    password_field->setPlaceholderText(PASSWORD_FIELD_PLACEHOLDER);
    password_field->setEchoMode(QLineEdit::Password);

    login_button->setObjectName(LOGIN_BUTTON_OBJECT_NAME);
    login_button->setFixedSize(FIXED_FORM_LINE_WIDTH, FIXED_FORM_LINE_HEIGHT);
    login_button->setCursor(Qt::PointingHandCursor);

    forgot_password_button->setObjectName(FORGOT_PASSWORD_BUTTON_OBJECT_NAME);
    forgot_password_button->setCursor(Qt::PointingHandCursor);

    auto *const vertical_layout = new QVBoxLayout{this};
    vertical_layout->addStretch(1);
    vertical_layout->addWidget(logotype, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(login_field, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(password_field, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(login_button, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(forgot_password_button, 0, Qt::AlignHCenter);
    vertical_layout->addStretch(1);
    vertical_layout->setSpacing(FORM_SPACING);

    connect(login_field, &QLineEdit::textChanged, this, &LoginWindow::SetPlaceholderColor);
    connect(password_field, &QLineEdit::textChanged, this, &LoginWindow::SetPlaceholderColor);
    connect(login_button, &QPushButton::clicked, this, &LoginWindow::LoginButtonClicked);
    connect(forgot_password_button, &QPushButton::clicked, this, &LoginWindow::ForgotPasswordButtonClicked);

    connect(&Authenticator::GetInstance(), &Authenticator::ResponseReady, this, &LoginWindow::ParseToken);
    connect(&Authenticator::GetInstance(), &Authenticator::ErrorsOccurred, this, &LoginWindow::ShowErrorsToUser);
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
    Authenticator::GetInstance().AuthenticateUser(login_field->text(), password_field->text());
}

void LoginWindow::ForgotPasswordButtonClicked() {
    // TODO: implement
}

void LoginWindow::ParseToken(const QByteArray &json_to_parse) {
    const auto json_object = QJsonDocument::fromJson(json_to_parse).object();
    const auto token = json_object["token"].toString().toInt();
    SignInToAccount(token);
}

void LoginWindow::ShowErrorsToUser(const std::variant<QString, Api::HttpCode> &reason) {
    // TODO: implement
}

void LoginWindow::SignInToAccount(const int token) {
    qDebug() << "LoginWindow::SignInToAccount" << token;
    new ProjectListWindow{GetStack(), this};
}
