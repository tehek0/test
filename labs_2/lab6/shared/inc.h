#include "nlohmann/json.hpp"
#include <fstream>

class QString;

using json = nlohmann::ordered_json;

struct shield {
    QString name;
    QString desc;
    double coef;
    QString type;
    shield(QString name_, QString desc_, double coef_, QString type_): name(name_), desc(desc_), coef(coef_), type(type_)  
    {}
    shield(json obj): name(QString::fromStdString(obj["name"])), desc(QString::fromStdString(obj["desc"])), coef(obj["coef"]), type(QString::fromStdString(obj["type"]))
    {}
};
