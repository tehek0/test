#include "nlohmann/json.hpp"
#include <fstream>

class QString;

using json = nlohmann::ordered_json;

struct shield {
    QString name;
    QString desc;
    double coef;
    QString type;
};