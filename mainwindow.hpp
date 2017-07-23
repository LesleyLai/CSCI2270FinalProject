#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

struct MainWindowImpl;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadWorldButton_clicked();
    void canvas_clicked(int x, int y);

    void on_clear_clicked();

private:
    Ui::MainWindow* ui;
    std::unique_ptr<MainWindowImpl> impl_;
};

#endif // MAINWINDOW_HPP
