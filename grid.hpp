#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <stdexcept>

// Grid is a 2 dimension fix-sized array
template <typename T>
class Grid {
public:
    using iterator = typename std::vector<T>::iterator;

    Grid() = default;

    // Create a grid from width and height
    Grid(int width, int height);

    int width() const { return width_; }
    int height() const { return height_; }
    int size() const { return width_ * height_; }

    // Copy and move operations
    Grid(const Grid& other) = default;
    Grid& operator=(const Grid& other) = default;
    Grid(Grid&& other) = default;
    Grid& operator=(Grid&& other) = default;

    // Return true if x and y are in the range of Grid
    bool inBounds(int x, int y) const;

    // Element access
    const T& at(int x, int y) const;
    T& at(int x, int y);

    // Iterating support
    iterator begin();
    iterator end();


private:
    std::vector<T> elems_;
    int width_;
    int height_;
};

template <typename T>
Grid<T>::Grid(int width, int height)
    : elems_ (static_cast<size_t>(width * height)),
      width_{width},
      height_{height} {}

template <typename T>
bool Grid<T>::inBounds(int x, int y) const {
    if (x < 0 || x >= width_) return false;
    if (y < 0 || y >= height_) return false;
    return true;
}

template <typename T>
const T& Grid<T>::at(int x, int y) const {
    if (!inBounds(x, y)) {
        auto x_s = std::to_string(x);
        auto y_s = std::to_string(y);
        throw std::out_of_range{"(" + x_s + "," + y_s + ") is out of index."};
    }
    auto index = static_cast<size_t>(y * width_ + x);
    return elems_[index];
}

template <typename T>
T& Grid<T>::at(int x, int y)
{
    return const_cast<double&>(static_cast<const Grid*>(this)->at(x, y));
}

template <typename T>
typename Grid<T>::iterator Grid<T>::begin()
{
    return elems_.begin();
}

template <typename T>
typename Grid<T>::iterator Grid<T>::end()
{
    return elems_.end();
}

#endif // GRID_HPP
