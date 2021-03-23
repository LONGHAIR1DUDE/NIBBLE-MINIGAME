#include <iostream>
#include "Terrain.h"
#include "Serpent.h"
using namespace std;

int main() {
    Terrain ter;
    Serpent serp(9, 4, ter);
    serp.testRegression();
    return 0;
}