#include <stdexcept>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "grid.hpp"
#include "random.hpp"
#include "adpter.hpp"

constexpr int canvas_width = 512;
constexpr int canvas_height = 512;

namespace {
    enum class World {
        terran16,
        terran32,
        terran64,
        terran128,
        terran256,
    };

    World world_from_combo(const QComboBox& world_combo) {
        auto text = world_combo.currentText();

        if (text == "Terran 16x16") {
            return World::terran16;
        } else if (text == "Terran 32x32") {
            return World::terran32;
        } else if (text == "Terran 64x64") {
            return World::terran64;
        } else if (text == "Terran 128x128") {
            return World::terran128;
        } else if (text == "Terran 256x256") {
            return World::terran256;
        } else {
            throw std::runtime_error {"Unknown world text"
                                      + text.toStdString()};
        }
    }

    // Generate terran with a (length, length) grid
    auto generate_terran(int length) {
        Grid<double> grid {length, length};

        Rand_double rd(0, 1, 0);
        for (auto& elem : grid) {
            elem = rd();
        }

        return grid;
    }
}

struct MainWindowImpl {
    QGraphicsScene scene { QRect(0, 0, canvas_width, canvas_height) };
    QGraphicsPixmapItem* item = nullptr;

    void draw_from_graph(const Graph& graph,
                         int block_width,
                         int block_height);
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    impl_(std::make_unique<MainWindowImpl>())
{
    ui->setupUi(this);
    ui->canvasView->setScene(&impl_->scene);
    ui->canvasView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->canvasView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_loadWorldButton_clicked()
{
    World current_world = world_from_combo(*ui->worldsCombo);

    Grid<double> grid;
    switch (current_world) {
    case World::terran16:
        grid = generate_terran(16);
        break;
    case World::terran32:
        grid = generate_terran(32);
        break;
    case World::terran64:
        grid = generate_terran(64);
        break;
    case World::terran128:
        grid = generate_terran(128);
        break;
    case World::terran256:
        grid = generate_terran(256);
        break;
    }

    auto world = graph_from_grid(grid);

    impl_->draw_from_graph(world, grid.width(), grid.height());
}

void MainWindowImpl::draw_from_graph(const Graph& graph,
                                     int width,
                                     int height)
{
    // Draw
    QPixmap canvas {canvas_width, canvas_height};
    QPainter painter {&canvas};

    const auto block_width = canvas_width / width;
    const auto block_height = canvas_height / height;

    for (auto x = 0; x != width; ++x) {
        for (auto y = 0; y != height; ++y) {
            auto vertex = graph.get_vertex(x, y);
            auto scale = vertex->cost;
            auto color = QColor {static_cast<int>(scale * 255),
                         static_cast<int>(scale * 255),
                         static_cast<int>(scale * 255)};

            const auto draw_x = x * block_width;
            const auto draw_y = y * block_height;

            painter.fillRect(draw_x,
                             draw_y,
                             draw_x + block_width,
                             draw_y + block_height,
                             color);
        }
    }

    scene.clear();
    item = scene.addPixmap(canvas);
    //auto canvas = ui->canvas;


}
