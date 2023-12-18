#include "Controller.hpp"
#include "View.hpp"

int main() {
    Controller controller(nullptr);  // Peut être nullptr pour le moment
    View view(&controller);
    controller = Controller(&view);
    controller.run();

    return 0;
}
