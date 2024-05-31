#include "legendItem.hpp"

template <typename T>

graphics::components::LegendItem<T>::LegendItem(std::string p_name, T p_value,
                                                std::string p_unit)
    : name(p_name), value(p_value), unit(p_unit) {}

template <typename T> graphics::components::LegendItem<T>::~LegendItem() {}

template <typename T>
std::string graphics::components::LegendItem<T>::getName() const {
  return name;
}

template <typename T> T graphics::components::LegendItem<T>::getValue() const {
  return value;
}

template <typename T>
std::string graphics::components::LegendItem<T>::getUnit() const {
  return unit;
}

template <typename T>
void graphics::components::LegendItem<T>::setName(const std::string &p_name) {
  name = p_name;
}

template <typename T>
void graphics::components::LegendItem<T>::setValue(const T &p_value) {
  value = p_value;
}

template <typename T>
void graphics::components::LegendItem<T>::setUnit(const std::string &p_unit) {
  unit = p_unit;
}

template class graphics::components::LegendItem<int>;
template class graphics::components::LegendItem<float>;
template class graphics::components::LegendItem<double>;
