#include "tui/Term.h"
#include "tui/Widget.h"

#include "core/page/meun.h"

int main() {
    using namespace tui;
    //setlocale(LC_ALL, nullptr);
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));

    page::menuPage(term);

    term.waitKey();
    return 0;
}
