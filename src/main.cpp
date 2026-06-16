#include <iostream>

#include "Renderer.h"

int main() {
    Renderer renderer;
    renderer.init();

    while (!renderer.isTerminated) {
        renderer.render();
    }

    return 0;
}
