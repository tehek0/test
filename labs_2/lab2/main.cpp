#include "car.h"

using namespace std;

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	car s;
	s.add_item("2");
	s.add_item("1");
	s.add_item("3");
	s.add_item("2");
	s.add_item("5");
	s.add_item("1");
	s.add_item("3");
	s.add_item("2");
	s.add_item("4");
	s.add_item("2");
	
	car w("P", "1", "A555AV");
	w.add_item("3");
	w.info();
	s.set_govID(govIDgenerate());
	s.info();
	car p;
	p = s - w;
	
	w.set_govID(govIDgenerate());
	
	p.info();
}