#include "tui/Term.h"
#include "tui/Widget.h"

std::vector<char> user, pwd;

decltype(auto) login() {
    using namespace tui;
    return ui<Center>(
            ui<VListView>(
                    ui<HCenter>(
                            ui<Box>(
                                    ui<WText>(L"银行管理系统登录")
                            )
                    ),
                    ui<Struct>(2, 1),
                    ui<HListView>(
                            ui<WText>(L"用户名: "),
                            ui_args<TextField>([](TextField &b) {
                                b.setFocusOrder(0);
                            }, &user, 25)
                    ),
                    ui<HListView>(
                            ui<WText>(L"密码: "),
                            ui<Struct>(1, 2),
                            ui_args<TextField>([](TextField &b) {
                                b.setFocusOrder(1);
                            }, &pwd, 25)
                    ),
                    ui<Struct>(2, 1),
                    ui<HListView>(
                            ui_args<Button>(
                                    [](Button &b) {
                                        b.setFocusOrder(2);
                                    },
                                    ui<Box>(
                                            ui<WText>(
                                                    L"  登录  "
                                            )
                                    )
                            ),
                            ui<Struct>(1, 5),
                            ui_args<Button>(
                                    [](Button &b) {
                                        b.setFocusOrder(3);
                                    },
                                    ui<Box>(
                                            ui<WText>(
                                                    L"  退出  "
                                            )
                                    )
                            )
                    )
            )
    );
}

decltype(auto) mainMenu() {
    using namespace tui;
    return ui<Center>(
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
    );
}

int main() {
    using namespace tui;
    //setlocale(LC_ALL, nullptr);
    Term term(GetStdHandle(STD_OUTPUT_HANDLE));
    term.push(login());
    term.capture();

    term.waitKey();
    return 0;
}
