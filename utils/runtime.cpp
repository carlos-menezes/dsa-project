#include "../supermarket/supermarket.h"
#include "runtime.h"
#include "navigation.h"
#include "io.h"

[[noreturn]] void handleRuntime(Supermarket &supermarket, Navigation &managementMenu) {
    char input;
    while (true) {
        navigation::main::getInput(input);
        switch (input) {
            case 'n':
                io::output::flushScreen();
                supermarket::process(supermarket);
                break;
            case 'm':
                navigation::management::process(managementMenu);
                break;
            default:
                break;
        }
    }
}

int runtime::asNew() {
    auto supermarket = supermarket::create();
    supermarket::process(supermarket);
    Navigation managementMenu = navigation::management::buildNavigation(supermarket);
    handleRuntime(supermarket, managementMenu);
    return 1;
}

int runtime::fromFile(const std::string &path) {
    Supermarket supermarket{};
    try {
        supermarket = supermarket::loadState(path);
    } catch (std::invalid_argument &e) {
        io::output::error(e.what());
        return 1;
    }

    Navigation managementMenu = navigation::management::buildNavigation(supermarket);
    supermarket::printData(supermarket);
    handleRuntime(supermarket, managementMenu);
}
