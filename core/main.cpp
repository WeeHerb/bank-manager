#include "tui/Term.h"
#include "tui/Widget.h"


int main() {
    using namespace tui;
    setlocale(LC_ALL, nullptr);
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));
    term.push(
            std::make_shared<Center>(
                    std::make_shared<VListView>(
                            std::make_shared<HCenter>(
                                    std::make_shared<AttrFill>(
                                            color::BG_GREEN | color::FG_COMMON,
                                            std::make_shared<Box>(
                                                    std::make_shared<WText>(L"银行管理系统")
                                            )
                                    )
                            ),
                            std::make_shared<Struct>(2, 1),
                            std::make_shared<Text>("1. This is first option"),
                            std::make_shared<Text>("2. This is second option"),
                            std::make_shared<Struct>(2, 1),
                            std::make_shared<Box>(
                                    std::make_shared<HCenter>(
                                            std::make_shared<HListView>(
                                                    std::make_shared<Box>(
                                                            std::make_shared<Text>("Cancel")
                                                    ),
                                                    std::make_shared<Struct>(1, 3),
                                                    std::make_shared<Box>(
                                                            std::make_shared<Text>("  Ok  ")
                                                    )
                                            )
                                    )
                            )

                    )
            )
    );
    term.draw();

    term.waitKey();
    return 0;
}
