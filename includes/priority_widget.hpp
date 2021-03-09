#ifndef PRIORITY_WIDGET_HPP
#define PRIORITY_WIDGET_HPP

#include <QWidget>

class PriorityWidget : public QWidget {
 Q_OBJECT
 public:
    explicit PriorityWidget(QWidget *parent = nullptr);

    int GetPriority() const;

    void SetPriority(int priority);
    void SetVerticalSpacing(int vertical_spacing);
    void SetHorizontalSpacing(int horizontal_spacing);
    void SetRadius(int radius);

    QSize sizeHint() const override;

 protected:
    void paintEvent(QPaintEvent *paint_event) override;

 private:
    static constexpr int VERTICAL_DOTS_COUNT = 2;
    static constexpr int HORIZONTAL_DOTS_COUNT = 5;

    int m_priority{5};
    int m_vertical_spacing{1};
    int m_horizontal_spacing{2};
    int m_radius{10};

 public slots:
    void Increment();
    void Decrement();
};

#endif