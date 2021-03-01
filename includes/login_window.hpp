#ifndef LOGIN_WINDOW_HPP
#define LOGIN_WINDOW_HPP

#include <QPushButton>
#include <QLineEdit>

#include "abstract_window.hpp"
#include "authenticator.hpp"

class LoginWindow : public AbstractWindow {
 Q_OBJECT

 public:
    explicit LoginWindow(QStackedLayout &stack, QWidget *parent = nullptr);
    ~LoginWindow() override = default;

 private:
    QLineEdit *const login_field;
    QLineEdit *const password_field;
    QPushButton *const login_button;
    QPushButton *const forgot_password_button;

    void Initialize();
    void SignInToAccount(int token);

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