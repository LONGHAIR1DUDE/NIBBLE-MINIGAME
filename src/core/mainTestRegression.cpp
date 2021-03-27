#include <iostream>
#include "Terrain.h"
#include "Serpent.h"
using namespace std;

int main() {
    Terrain ter;
    bool mouv = true;
    Serpent serp(2, 9, 4, ter, mouv);
    serp.testRegression();
    ter.testRegression();
    return 0;
}