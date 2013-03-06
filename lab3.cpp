#include <iostream>

#include "GlGlut.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "CSE 5542 - Lab 3" << endl;
	cout << "Dan Ziemba, 2013" << endl << endl;
	cout << "Controls:" << endl;
	cout << "\t'1' - Phong shader" << endl;
	cout << "\t'2' - Checkerboard shader" << endl;
	cout << "\t'3' - Wood shader" << endl;
	cout << "\t'4' - Point light source" << endl;

	lab3::GlGlut g;
	g.start(&argc, argv);

	return 0;
}
