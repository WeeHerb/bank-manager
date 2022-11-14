#include "tui/Term.h"
#include "tui/Widget.h"


int main() {
    using namespace tui;
    //setlocale(LC_ALL, nullptr);
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));
    term.push(
            ui<Center>(
                    ui<VListView>(
                            ui<HCenter>(
                                    ui<AttrFill>(
                                            color::BG_GREEN | color::FG_COMMON,
                                            ui<Box>(
                                                    ui<HListView>(std::make_shared<Struct>(1, 4),
                                                                                ui<WText>(
                                                                                        L"银行管理系统"),
                                                                                ui<Struct>(1, 4)
                                                    )
                                            )
                                    )
                            ),
                            ui<Struct>(2, 1),
                            ui_args<Button>([](Button &b) {
                                b.setFocusOrder(0);
                            }, ui<WText>(L"1.银行职员管理")),
                            ui_args<Button>([](Button &b) {
                                b.setFocusOrder(1);
                            }, ui<WText>(L"2.客户账号管理")),
                            ui_args<Button>([](Button &b) {
                                b.setFocusOrder(2);
                            }, ui<WText>(L"3.存取贷业务管理")),
                            ui_args<Button>([](Button &b) {
                                b.setFocusOrder(3);
                            }, ui<WText>(L"4.业务查询")),

                            ui<Struct>(2, 1),

                            ui<HCenter>(
                                    ui<HListView>(
                                            ui_args<Button>(
                                                    [](Button &b) {
                                                        b.setFocusOrder(4);
                                                    },
                                                    ui<Box>(
                                                            std::make_shared<Text>("  Save  ")
                                                    )
                                            ),
                                            ui<Struct>(1, 8),
                                            ui_args<Button>(
                                                    [](Button &b) {
                                                        b.setFocusOrder(5);
                                                    },
                                                    ui<Box>(
                                                            std::make_shared<Text>("  Exit  ")
                                                    )
                                            )

                                    )
                            )


                    )
            )
    );
    term.capture();

    term.waitKey();
    return 0;
}
