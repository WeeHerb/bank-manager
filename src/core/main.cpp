#include "tui/Term.h"
#include "tui/Widget.h"

#include "core/page/login.h"

int main() {
    using namespace tui;
    //setlocale(LC_ALL, nullptr);
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));

    page::loginPage(term);

    term.waitKey();
    return 0;
}
