#ifndef CONFIG_H
#define CONFIG_H

namespace config {

constexpr auto WINDOW_TITLE = "Project manager";
constexpr auto MIN_WINDOW_WIDTH = 640;
constexpr auto MIN_WINDOW_HEIGHT = 480;
constexpr auto ZERO_MARGINS = QMargins{0, 0, 0, 0};
constexpr auto ZERO_SPACING = 0;
constexpr auto LOGOTYPE_PATH = ":/img/logotype.jpg";
constexpr auto UNKNOWN_IMAGE_PATH = ":/img/unknown.jpg";

namespace login_window {

constexpr auto OBJECT_NAME = "LoginWindow";
constexpr auto STYLESHEET_PATH = ":/qss/main.qss";
constexpr auto LOGOTYPE_WIDTH = 100;
constexpr auto LOGOTYPE_HEIGHT = 100;
constexpr auto FIXED_FORM_LINE_WIDTH = 300;
constexpr auto FIXED_FORM_LINE_HEIGHT = 30;
constexpr auto LOGIN_FIELD_PLACEHOLDER = "Email";
constexpr auto PASSWORD_FIELD_PLACEHOLDER = "Password";
constexpr auto LOGIN_BUTTON_OBJECT_NAME = "LoginButton";
constexpr auto LOGIN_BUTTON_LABEL = "Login";
constexpr auto FORGOT_PASSWORD_BUTTON_OBJECT_NAME = "ForgotPasswordButton";
constexpr auto FORGOT_PASSWORD_BUTTON_LABEL = "Forgot password?";
constexpr auto FORM_SPACING = 15;

}

namespace project_list_window {

constexpr auto HEADER_HEIGHT = 60;
constexpr auto HEADER_LOGOTYPE_HEIGHT = 50;
constexpr auto HEADER_LOGOTYPE_WIDTH = 50;
constexpr auto HEADER_LABEL = "All projects";
constexpr auto PROJECT_ICON_WIDTH = 50;
constexpr auto PROJECT_ICON_HEIGHT = 50;

}

namespace project_widget {

constexpr auto MARGINS = QMargins{10, 10, 0, 10};
constexpr auto SPACING = 15;

}

}

#endif