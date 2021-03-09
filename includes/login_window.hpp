#ifndef LOGIN_WINDOW_HPP
#define LOGIN_WINDOW_HPP

#include <QPushButton>
#include <QLineEdit>

#include "abstract_window.hpp"
#include "authenticator.hpp"

class LoginWindow : public AbstractWindow {
 Q_OBJECT

 public:
    explicit LoginWindow(Stack &stack, QWidget *parent = nullptr);

 private:
    QLineEdit *const m_login_field;
    QLineEdit *const m_password_field;
    QPushButton *const m_login_button;
    QPushButton *const m_forgot_password_button;

    void Initialize();
    void SignInToAccount(const QString &token);

 signals:
    void Authorized(const QString &login, const QString &password);

 private slots:
    void LoginButtonClicked();
    void ForgotPasswordButtonClicked();
    void SetPlaceholderColor();
    void ParseToken(const QByteArray &json_to_parse);
    void ShowErrorsToUser(const std::variant<QString, Api::HttpCode> &reason);
};

#endif