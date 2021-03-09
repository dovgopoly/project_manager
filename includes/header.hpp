#ifndef HEADER_HPP
#define HEADER_HPP

#include <QWidget>
#include <QLabel>

#include "image.hpp"

class Header : public QWidget {
    Q_OBJECT
 public:
    friend class MainWindow;

    explicit Header(QWidget *parent = nullptr);

    enum {
        NoFlags = 0,
        ShowHeader = 1 << 0,
        ShowBackArrow = 1 << 1,
        ShowTitle = 1 << 2
    };

    void SetProperties(int properties);
    void SetTitle(const QString &title);

 private:
    void Initialize();

    Image *const m_back_arrow_icon;
    QLabel *const m_title;
    QHBoxLayout *const m_main_layout;
};

#endif