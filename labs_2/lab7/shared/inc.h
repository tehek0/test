#define ASIO_STANDALONE
#include "asio/include/asio.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

enum class weather {
    clear,
    cloudy,
    rain
};