//
// Created by mslxl on 11/16/2022.
//

#include "login.h"
#include "meun.h"
#include "tui/dialog/msgbox.h"

void page::loginPage(tui::Term &term) {
    using namespace tui;
    std::vector<char> user, pwd;

    auto widget = ui<Center>(
            ui<Box>(
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
                            ui<HCenter>(
                                    ui<HListView>(
                                            ui_args<Button>(
                                                    [&term, &user, &pwd](Button &b) {
                                                        b.setFocusOrder(2);
                                                        b.setActionListener([&term, &user, &pwd]() {
                                                            if (std::string_view("admin") == user.data()
                                                                && std::string_view("admin") == pwd.data()) {

                                                                user.clear(), user.push_back('\0');
                                                                pwd.clear(), pwd.push_back('\0');

                                                                page::menuPage(term);
                                                                term.invalidate();
                                                            } else {
                                                                user.clear(), user.push_back('\0');
                                                                pwd.clear(), pwd.push_back('\0');

                                                                tui::msgbox<wchar_t, wchar_t, wchar_t>(term,
                                                                                  L"用户名或密码错误",
                                                                                  true, L"确定", false, L".");
                                                            }
                                                        });
                                                    },
                                                    ui<Box>(
                                                            ui<WText>(
                                                                    L"登录"
                                                            )
                                                    )
                                            ),
                                            ui<Struct>(1, 10),
                                            ui_args<Button>(
                                                    [](Button &b) {
                                                        b.setFocusOrder(3);
                                                        b.setActionListener([]() {
                                                            std::exit(0);
                                                        });
                                                    },
                                                    ui<Box>(
                                                            ui<WText>(
                                                                    L"退出"
                                                            )
                                                    )
                                            )
                                    )
                            )

                    )
            )
    ); // ))))));)}         :_(
    term.push(widget);
    term.invalidate();
    term.capture();
}