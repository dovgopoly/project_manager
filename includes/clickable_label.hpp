#ifndef CLICKABLE_LABEL_HPP
#define CLICKABLE_LABEL_HPP

#include <QLabel>

class ClickableLabel : public QLabel {
 Q_OBJECT
 public:
    explicit ClickableLabel(QWidget *parent = nullptr);
    explicit ClickableLabel(const QString &text = {}, QWidget *parent = nullptr);
    ~ClickableLabel() override = default;

 signals:
    void clicked();
    void doubleClicked();

 protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif