#include "tui/Term.h"
#include "tui/widget/HCenter.h"
#include "tui/widget/Text.h"
#include "tui/widget/Box.h"
#include "tui/widget/AttrFill.h"


int main() {
    using namespace tui;
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));
    term.push(
            std::make_shared<HCenter>(
                    std::make_shared<AttrFill>(
                            color::BG_GREEN | color::FG_COMMON,
                            std::make_shared<Box>(
                                    std::make_shared<Text>("BankManager")
                            )
                    )
            )
    );
    term.draw();

    term.waitKey();
    return 0;
}
