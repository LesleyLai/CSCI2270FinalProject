#ifndef GRAPHICSVIEW_HPP
#define GRAPHICSVIEW_HPP

#include <QGraphicsView>

// Customized graphics view that respond to mouse click
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget *parent = nullptr);

signals:
    void mouse_click(int x, int y);

private:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // GRAPHICSVIEW_HPP
