#ifndef LEGEND_ITEM_HPP
#define LEGEND_ITEM_HPP

#include <string>

namespace graphics::components {

template <typename T> class LegendItem {
  public:
    LegendItem(std::string p_name, T p_value, std::string p_unit);
    ~LegendItem();

    std::string getName() const;
    T getValue() const;
    std::string getUnit() const;

    void setName(const std::string &p_name);
    void setValue(const T &p_value);
    void setUnit(const std::string &p_unit);

  private:
    std::string name;
    T value;
    std::string unit;
};

} // namespace graphics::components

#endif