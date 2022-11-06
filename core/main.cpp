#include "tui/Term.h"
#include "tui/Widget.h"


int main() {
    using namespace tui;
    setlocale(LC_ALL, nullptr);
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));
    term.push(
            std::make_shared<Center>(
                    std::make_shared<AttrFill>(
                            color::BG_GREEN | color::FG_COMMON,
                            std::make_shared<Box>(
                                    std::make_shared<WText>(L"银行管理系统")
                            )
                    )
            )
    );
    term.draw();

    term.waitKey();
    return 0;
}
