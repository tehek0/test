#include "mainwindow.h"
#include "inc/all.h"
#include <QApplication>

using json = nlohmann::json;

void init() {
    std::ifstream f("character.json");
    json j;
    if (!f.is_open()) {
        std::ofstream def("character.json");
        j["inventory"] = json::array();
        j["name"] = "Default Name";
        j["lvl"] = 1;
        j["xp"] = 0;
        j["xp_required"] = 100;
        j["required_coef"] = 1.5f;
        def << std::setw(4) << j << std::endl;
    } else {
        j = json::parse(f);
    }
    inventory _inventory;
    for (size_t i = 0; i < j["inventory"].size(); ++i) {
        _inventory.add_item(new item(j["inventory"][i]["name"], j["inventory"][i]["asset"]));
    }
    QString _name;
    unsigned int _lvl;
    unsigned long _xp;
    unsigned long _xp_required;
    float _required_coef = 0.25f;
    entity character(j["inventory"],j["name"],j["lvl"],j["xp"],j["xp_required"],j["required_coef"]);
}

int main(int argc, char *argv[])
{
    init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
