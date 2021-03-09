#include <QLabel>
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMovie>

#include "../includes/login_window.hpp"
#include "../includes/config.hpp"
#include "../includes/project_list_window.hpp"
#include "../includes/private_config.hpp"

LoginWindow::LoginWindow(Stack &stack, QWidget *parent)
    : AbstractWindow{stack, parent}
    , m_login_field{new QLineEdit{this}}
    , m_password_field{new QLineEdit{this}}
    , m_login_button{new QPushButton{config::login_window::LOGIN_BUTTON_LABEL, this}}
    , m_forgot_password_button{new QPushButton{config::login_window::FORGOT_PASSWORD_BUTTON_LABEL, this}} {

    Initialize();
}

void LoginWindow::Initialize() {
    using namespace config;
    using namespace config::login_window;

    SetStyleSheet(STYLESHEET_PATH);
    setObjectName(OBJECT_NAME);

    auto *const logotype =
        new Image(LOGOTYPE_PATH, LOGOTYPE_WIDTH, LOGOTYPE_HEIGHT, Image::HighQuality | Image::RoundedCorners);

    m_login_field->setFixedSize(FIXED_FORM_LINE_WIDTH, FIXED_FORM_LINE_HEIGHT);
    m_login_field->setPlaceholderText(LOGIN_FIELD_PLACEHOLDER);

    m_password_field->setFixedSize(FIXED_FORM_LINE_WIDTH, FIXED_FORM_LINE_HEIGHT);
    m_password_field->setPlaceholderText(PASSWORD_FIELD_PLACEHOLDER);
    m_password_field->setEchoMode(QLineEdit::Password);

    m_login_button->setObjectName(LOGIN_BUTTON_OBJECT_NAME);
    m_login_button->setFixedSize(FIXED_FORM_LINE_WIDTH, FIXED_FORM_LINE_HEIGHT);
    m_login_button->setCursor(Qt::PointingHandCursor);

    m_forgot_password_button->setObjectName(FORGOT_PASSWORD_BUTTON_OBJECT_NAME);
    m_forgot_password_button->setCursor(Qt::PointingHandCursor);

    auto *const vertical_layout = new QVBoxLayout{this};
    vertical_layout->setAlignment(Qt::AlignCenter);
    vertical_layout->addWidget(logotype, 0, Qt::AlignHCenter);
    vertical_layout->addWidget(m_login_field);
    vertical_layout->addWidget(m_password_field);
    vertical_layout->addWidget(m_login_button);
    vertical_layout->addWidget(m_forgot_password_button);

    vertical_layout->setSpacing(FORM_SPACING);

    connect(m_login_field, &QLineEdit::textChanged, this, &LoginWindow::SetPlaceholderColor);
    connect(m_password_field, &QLineEdit::textChanged, this, &LoginWindow::SetPlaceholderColor);
    connect(m_login_button, &QPushButton::clicked, this, &LoginWindow::LoginButtonClicked);
    connect(m_forgot_password_button, &QPushButton::clicked, this, &LoginWindow::ForgotPasswordButtonClicked);
    connect(&Authenticator::GetInstance(), &Authenticator::ResponseReady, this, &LoginWindow::ParseToken);
    connect(&Authenticator::GetInstance(), &Authenticator::ErrorsOccurred, this, &LoginWindow::ShowErrorsToUser);
}

void LoginWindow::SetPlaceholderColor() {
    using namespace config::login_window;
    if (auto *const line_edit = qobject_cast<QLineEdit *>(sender())) {
        if (line_edit->text().isEmpty()) {
            line_edit->setStyleSheet(
                QString("font-style: %1; color: %2").arg(PLACEHOLDER_FONT_STYLE, PLACEHOLDER_COLOR));
        } else {
            line_edit->setStyleSheet(
                QString("font-style: %1; color: %2").arg(FORM_TEXT_STYLE, FORM_TEXT_COLOR));
        }
    }
}

void LoginWindow::LoginButtonClicked() {
    auto &authenticator = Authenticator::GetInstance();
    authenticator.AuthenticateUser(m_login_field->text(), m_password_field->text());
}

void LoginWindow::ForgotPasswordButtonClicked() {
    using namespace private_config;
    m_login_field->setText(DEFAULT_LOGIN);
    m_password_field->setText(DEFAULT_PASSWORD);
}

void LoginWindow::ParseToken(const QByteArray &json_to_parse) {
    const auto json_object = QJsonDocument::fromJson(json_to_parse).object();
    const auto token = json_object["token"].toString();
    SignInToAccount(token);
}

void LoginWindow::ShowErrorsToUser(const std::variant<QString, Api::HttpCode> &reason) {
    // TODO: implement
}

void LoginWindow::SignInToAccount(const QString &token) {
    auto &authenticator = Authenticator::GetInstance();
    authenticator.SetCurrentToken(token);

    auto *const project_list_window = new ProjectListWindow{GetStack(), parentWidget()};
    project_list_window->PutSelfToStack();
}
