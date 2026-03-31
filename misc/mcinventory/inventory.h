#pragma once
#include <QString>
class item {
private:
    QString _name;
    const unsigned short _stack_size;
    unsigned short _amount;
public:
    item() {
        _name = NULL;
        _stack_size = 0;
        _amount = 0;
    }
    item(QString name) {
        _name = name;
        _stack_size = 64;
        _amount = 1;
    }
    item(QString name, unsigned short stack_size) {
        _name = name;
        _stack_size = stack_size;
        _amount = 1;
    }
    item(QString name, unsigned short stack_size, unsigned short amount) {
        _name = name;
        _stack_size = stack_size;
        _amount = amount;
    }

    QString get_name() {
        return _name;
    }
    unsigned short get_stack_size() {
        return _stack_size;
    }
    unsigned short get_amount() {
        return _amount;
    }

    void set_amount(unsigned short amount) {
        _amount = amount;
    }

    item split() {
        item returnvalue(_name, _stack_size);
        if (this->get_amount() == 1) {
            this->item();
            return returnvalue;
        }
        unsigned short original_amount = this->get_amount();
        unsigned short halved_amount = original_amount / 2;
        this->set_amount(original_amount - halved_amount);
        returnvalue.set_amount(halved_amount);
        return returnvalue;
    }
};
