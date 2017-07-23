#ifndef GRID_HPP
#define GRID_HPP

#include <memory>
#include <string>
#include <stdexcept>

// Grid is a 2 dimension fix-sized array
class Grid {
public:
    Grid() = default;

    // Create a grid from width and height
    Grid(int width, int height);

    int width() const;
    int height() const;
    int size() const;

    // Move operations
    Grid(Grid&& other) = default;
    Grid& operator=(Grid&& other) = default;

    // Return true if x and y are in the range of Grid
    bool inBounds(int x, int y) const;

    // Element access
    const double& at(int x, int y) const;
    double& at(int x, int y);

    // Iterating support
    double* begin();
    double* end();


private:
    std::unique_ptr<double[]> elems_;
    int width_;
    int height_;
};

Grid::Grid(int width, int height)
    : elems_ {std::make_unique<double[]>(static_cast<size_t>(width * height))},
      width_{width},
      height_{height} {}

int Grid::width() const {
    return width_;
}

int Grid::height() const {
    return height_;
}

int Grid::size() const {
    return width_ * height_;
}

bool Grid::inBounds(int x, int y) const {
    if (x < 0 || x >= width_) return false;
    if (y < 0 || y >= height_) return false;
    return true;
}

const double& Grid::at(int x, int y) const {

    if (!inBounds(x, y)) {
        auto x_s = std::to_string(x);
        auto y_s = std::to_string(y);
        throw std::out_of_range{"(" + x_s + "," + y_s + ") is out of index."};
    }
    auto index = static_cast<size_t>(y * width_ + x);
    return elems_[index];
}

double& Grid::at(int x, int y)
{
    return const_cast<double&>(static_cast<const Grid*>(this)->at(x, y));
}

double* Grid::begin()
{
    return elems_.get();
}

double* Grid::end()
{
    return elems_.get() + size();
}

#endif // GRID_HPP
