#include <stdexcept>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <future>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "grid.hpp"
#include "random.hpp"
#include "adpter.hpp"
#include "graphicsview.hpp"

constexpr int canvas_width = 512;
constexpr int canvas_height = 512;

namespace {
    enum class World_type {
        terran16,
        terran32,
        terran64,
        terran128,
        terran256,
    };

    World_type world_from_combo(const QComboBox& world_combo) {
        auto text = world_combo.currentText();

        if (text == "Terran 16x16") {
            return World_type::terran16;
        } else if (text == "Terran 32x32") {
            return World_type::terran32;
        } else if (text == "Terran 64x64") {
            return World_type::terran64;
        } else if (text == "Terran 128x128") {
            return World_type::terran128;
        } else if (text == "Terran 256x256") {
            return World_type::terran256;
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

struct World_info {
    std::future<Graph> world_graph_handle;
    int row_count;
    int column_count;
};

struct MainWindowImpl {
    QGraphicsScene scene { QRect(0, 0, canvas_width, canvas_height) };
    QGraphicsPixmapItem* item = nullptr;
    QGraphicsRectItem* start_rect = nullptr;
    QGraphicsRectItem* dest_rect = nullptr;
    std::unique_ptr<World_info> world;

    void draw_grid(const Grid<double>& grid);

    void refresh_world(int row, int column) {
        world = std::make_unique<World_info>();
        world->row_count = row;
        world->column_count = column;
    }

    void canvas_clicked (int x, int y);
    void clear_path();
    void load_new_world(World_type world);
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    impl_(std::make_unique<MainWindowImpl>())
{
    ui->setupUi(this);
    auto canvasView = new GraphicsView(ui->centralWidget);
    canvasView->setObjectName(QStringLiteral("canvasView"));
    canvasView->setGeometry(QRect(10, 40, canvas_width, canvas_height));
    canvasView->setScene(&impl_->scene);

    connect(canvasView, SIGNAL(mouse_click(int, int)),
            this, SLOT(canvas_clicked(int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadWorldButton_clicked()
{
    World_type world_type = world_from_combo(*ui->worldsCombo);
    impl_->load_new_world(world_type);
}

#include <QDebug>
void MainWindow::canvas_clicked(int x, int y)
{
    impl_->canvas_clicked(x, y);
}


void MainWindow::on_clear_clicked()
{
    impl_->clear_path();
}

void MainWindowImpl::load_new_world(World_type world_type)
{
    int world_width, world_height;
    switch (world_type) {
    case World_type::terran16:
        world_width = world_height = 16;
        break;
    case World_type::terran32:
        world_width = world_height = 32;
        break;
    case World_type::terran64:
        world_width = world_height = 64;
        break;
    case World_type::terran128:
        world_width = world_height = 128;
        break;
    case World_type::terran256:
        world_width = world_height = 256;
        break;
    }

    auto grid = generate_terran(world_width);
    refresh_world(world_width, world_height);
    draw_grid(grid);

    world->world_graph_handle = std::async(std::launch::async, [grid](){
        return graph_from_grid(grid);
    });
}

void MainWindowImpl::draw_grid(const Grid<double>& grid)
{
    // Draw
    QPixmap canvas {canvas_width, canvas_height};
    QPainter painter {&canvas};

    const auto width = grid.width();
    const auto height = grid.height();
    const auto block_width = canvas_width / width;
    const auto block_height = canvas_height / height;

    for (auto x = 0; x != width; ++x) {
        for (auto y = 0; y != height; ++y) {
            auto scale = grid.at(x, y);
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

    if (item) {
        scene.removeItem(item);
    }
    item = scene.addPixmap(canvas);
}

void MainWindowImpl::canvas_clicked(int x, int y) {
    if (!world) return;
    const auto width = world->row_count;
    const auto height = world->column_count;
    const auto block_width = canvas_width / width;
    const auto block_height = canvas_height / height;

    const auto row = x / block_width;
    const auto column = y / block_height;

    QRectF rect(row * block_width, column * block_height,
                block_width, block_height);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);

    if (!start_rect) {
        start_rect = scene.addRect(rect, pen);
    } else if (!dest_rect) {
        dest_rect = scene.addRect(rect, pen);
    } else {
        scene.removeItem(start_rect);
        scene.removeItem(dest_rect);
        start_rect = scene.addRect(rect, pen);
        dest_rect = nullptr;
    }

}

void MainWindowImpl::clear_path()
{
    if (start_rect) {
        scene.removeItem(start_rect);
        start_rect = nullptr;
    }

    if (dest_rect) {
        scene.removeItem(dest_rect);
        dest_rect = nullptr;
    }
}
