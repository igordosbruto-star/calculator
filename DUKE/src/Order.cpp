#include "Order.h"

namespace duke {

Order::Order(int i, std::string c, std::string it, int q)
    : id(i), cliente(std::move(c)), item(std::move(it)), quantidade(q) {}

} // namespace duke

