//
// Created by Carlos on 01/05/2021.
//

#include "../supermarket/supermarket.h"
#include "runtime.h"
#include "navigation.h"
#include "io.h"

int runtime::as_new() {
    auto supermarket = supermarket::create();
    supermarket::process(supermarket);
    Navigation managementMenu = navigation::management::buildNavigation(supermarket);

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

    return 0;
}
