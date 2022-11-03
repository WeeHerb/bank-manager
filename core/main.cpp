#include <iostream>
#include <windows.h>

#include "tui/term_attr.h"
#include "tui/widget.h"

tui::TermAttr init_term() {
    auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    tui::TermAttr term(hConsole);
    term.set_text_attr(tui::FG_COMMON | tui::BG_COMMON);
    term.init(std::cout);
    return term;
}

int main() {
    auto term = init_term();
    using namespace tui;

    term.proceed(std::make_shared<center>(
            std::make_shared<attr>(
                    tui::color(BACKGROUND_GREEN) | tui::color(FOREGROUND_RED),
                    std::make_shared<box>(
                            std::make_shared<attr>(
                                    tui::color(BACKGROUND_GREEN) | tui::FG_COMMON | tui::FG_INTENSITY,
                                    std::make_shared<text>("Bank Man")
                            )
                    )
            )
    ), std::cout);

    term.wait_key();
    term.refresh_size();


    term.clear(std::cout);
    term.wait_key();
    return 0;
}
