#ifndef LOGIN_WINDOW_HPP
#define LOGIN_WINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class LoginWindow : public QWidget {
 Q_OBJECT

 public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow() override = default;

 private:
    QLineEdit *const login_field;
    QLineEdit *const password_field;
    QPushButton *const login_button;
    QPushButton *const forgot_password_button;

    void Initialize();

 signals:
    void Authorized(const QString &login, const QString &password);

 private slots:
    void LoginButtonClicked();
    void ForgotPasswordButtonClicked();
    void SetPlaceholderColor();
};

#endif