#include <iostream>
#include "tui/Term.h"
#include "tui/widget/Text.h"


int main() {
    using namespace tui;
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));
    term.push(std::make_shared<Text>("WWW"));
    term.draw();

    getchar();
    return 0;
}
