#pragma once
#include <QString>
#include <vector>

class item {
protected:
    QString _name;
    QString _asset;
    unsigned int _stack;
    unsigned int _max_stack_size;
    unsigned int _base_cost;
public:
    item() = default;
    item(const QString& name,
         const QString& asset,
         unsigned int stack,
         unsigned int max_stack_size,
         unsigned int base_cost):
        _name(name),
        _asset(asset),
        _stack(stack),
        _max_stack_size(max_stack_size),
        _base_cost(base_cost)
    {}
    virtual ~item() = default;

    bool can_add(item* other);
    bool can_add(item* other, unsigned int count);
    void add();
    void add(unsigned int count);
    bool has_amount(unsigned int count);
    void remove();
    void remove(unsigned int count);
    QString get_name();
    QString get_asset();
    unsigned int get_stack();
    unsigned int get_max_stack_size();
    unsigned int get_base_cost();
    void set_name(const QString& name);
    void set_asset(const QString& asset);
    void set_stack(unsigned int stack);
    void set_max_stack_size(unsigned int max_stack_size);
    void set_base_cost(unsigned int base_cost);
    virtual bool operator==(item* other);
    virtual bool operator!=(item* other);
};

enum class armor_slot {
    helmet,
    chestplate,
    boots
};

class armor : public item {
protected:
    short _armor_points;
    armor_slot _armor_slot;
public:
    armor() = default;
    armor(const QString& name,
          const QString& asset,
          unsigned int stack,
          unsigned int max_stack_size,
          unsigned int base_cost,
          short armor_points, armor_slot armor_slot_):
        item(name, asset,
            stack, max_stack_size,
            base_cost),
        _armor_points(armor_points),
        _armor_slot(armor_slot_)
    {}
    armor_slot get_armor_slot();
    short get_armor_points();
    void set_armor_slot(armor_slot armor_slot_);
    void set_armor_points(short armor_points);
    bool operator==(armor* other);
    bool operator!=(armor* other);
    bool operator==(item* other) final;
    bool operator!=(item* other) final;
};

class apple: public item {
    apple(): item("Яблоко", ":/rs/apple.png", 1, 1000000, 5)
    {}
};

class coin: public item {
    coin(): item("Монета", ":/rs/coin.png", 1, 1000000, 1)
    {}
};
