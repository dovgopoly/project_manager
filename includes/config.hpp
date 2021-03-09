#ifndef CONFIG_H
#define CONFIG_H

namespace config {

constexpr auto ZERO_MARGINS = QMargins{0, 0, 0, 0};
constexpr auto ZERO_SPACING = 0;
constexpr auto LOGOTYPE_PATH = ":/img/logotype.jpg";
constexpr auto UNKNOWN_IMAGE_PATH = ":/img/unknown.jpg";

namespace main_window {

constexpr auto WINDOW_TITLE = "Project manager";
constexpr auto MIN_WINDOW_WIDTH = 640;
constexpr auto MIN_WINDOW_HEIGHT = 480;

namespace header {

constexpr auto HEADER_HEIGHT = 70;
constexpr auto ARROW_BACK_ICON_PATH = ":/img/back_arrow.jpg";
constexpr auto ARROW_ICON_WIDTH = 30;
constexpr auto ARROW_ICON_HEIGHT = 30;
constexpr auto HEADER_MARGINS = QMargins{30, 0, 30 + ARROW_ICON_WIDTH, 0};
constexpr auto LOGOTYPE_WIDTH = 50;
constexpr auto LOGOTYPE_HEIGHT = 50;

}

}

namespace login_window {

constexpr auto OBJECT_NAME = "LoginWindow";
constexpr auto STYLESHEET_PATH = ":/qss/login_window.qss";
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
constexpr auto PLACEHOLDER_COLOR = "#678cb8";
constexpr auto PLACEHOLDER_FONT_STYLE = "italic";
constexpr auto FORM_TEXT_COLOR = "black";
constexpr auto FORM_TEXT_STYLE = "normal";

}

namespace project_list_window {

constexpr auto STYLESHEET_PATH = ":/qss/project_list_window.qss";
constexpr auto HEADER_HEIGHT = 60;
constexpr auto HEADER_LOGOTYPE_HEIGHT = 50;
constexpr auto HEADER_LOGOTYPE_WIDTH = 50;
constexpr auto HEADER_TITLE = "Projects";
constexpr auto PROJECT_ICON_WIDTH = 50;
constexpr auto PROJECT_ICON_HEIGHT = 50;
constexpr auto PROJECT_LIST_VIEW_SPACING = 1;
constexpr auto SIGN_OUT_BUTTON_LABEL = "← Sign out";

namespace project_item {

constexpr auto CONTENT_MARGIN = 10;
constexpr auto ICON_WIDTH = 50;
constexpr auto ICON_HEIGHT = 50;
constexpr auto FONT_SIZE = 15;
constexpr auto SPACING = 15;

}

}

namespace ticket_list_window {

constexpr auto HEADER_TITLE = "Tickets";
constexpr auto STYLESHEET_PATH = ":/qss/ticket_list_window.qss";

}

namespace ticket_edit_window {

constexpr auto UP_ARROW_PATH = ":/img/up_arrow.png";
constexpr auto DOWN_ARROW_PATH = ":/img/down_arrow.png";
constexpr auto STYLESHEET_PATH = ":/qss/ticket_edit_window.qss";
constexpr auto ARROW_SPINBOX_WIDTH = 15;
constexpr auto ARROW_SPINBOX_HEIGHT = 15;
constexpr auto MAIN_LAYOUT_MARGINS = QMargins{20, 20, 20, 20};
constexpr auto MAIN_LAYOUT_SPACING = 15;
constexpr auto SPINBOX_VERTICAL_SPACING = 2;
constexpr auto SPINBOX_HORIZONTAL_SPACING = 10;
constexpr auto PRIORITY_WIDGET_RADIUS = 8;
constexpr auto PRIORITY_WIDGET_VERTICAL_SPACING = 2;
constexpr auto SAVE_BUTTON_LABEL = "Save";
constexpr auto CANCEL_BUTTON_LABEL = "Cancel";
constexpr auto BUTTON_LAYOUT_SPACING = 8;
constexpr auto HEADER_TITLE = "Ticket edit";

}

}

#endif