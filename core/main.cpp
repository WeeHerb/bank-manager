#include <iostream>
#include <windows.h>

#include "tui/term_attr.h"


tui::TermAttr init_term(){
    auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    tui::TermAttr term(hConsole);
    term.set_text_attr(tui::FG_COMMON | tui::BG_COMMON);
    term.init(std::cout);
    return term;
}

int main() {
    auto term = init_term();
    term.wait_key();
    term.refresh_size();
    term.clear(std::cout);
    term.wait_key();
    return 0;
}
