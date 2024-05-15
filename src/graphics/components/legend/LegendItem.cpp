#include "LegendItem.hpp"

template <typename T>

LegendItem<T>::LegendItem(std::string p_name, T p_value, std::string p_unit)
    : name(p_name), value(p_value), unit(p_unit) {}

template <typename T> LegendItem<T>::~LegendItem() {}

template <typename T> std::string LegendItem<T>::getName() const {
    return name;
}

template <typename T> T LegendItem<T>::getValue() const { return value; }

template <typename T> std::string LegendItem<T>::getUnit() const {
    return unit;
}

template <typename T> void LegendItem<T>::setName(const std::string &p_name) {
    name = p_name;
}

template <typename T> void LegendItem<T>::setValue(const T &p_value) {
    value = p_value;
}

template <typename T> void LegendItem<T>::setUnit(const std::string &p_unit) {
    unit = p_unit;
}

template class LegendItem<int>;
template class LegendItem<float>;
template class LegendItem<double>;
