//
// Created by mslxl on 12/12/2022.
//

#include<vector>
#include "cash_reception.h"
#include "tui/Widget.h"
#include "core/data/Database.h"
#include "core/data/Customer.h"
#include "tui/dialog/msgbox.h"


void servicePage(tui::Term &term, Customer &item) {
    using namespace tui;

    auto widget = ui<Center>(
            ui<VListView>(
                    ui<HCenter>(
                            ui<AttrFill>(
                                    color::BG_GREEN | color::FG_COMMON,
                                    ui<Box>(
                                            ui<HListView>(std::make_shared<Struct>(1, 4),
                                                          ui<WText>(
                                                                  L"存取贷业务管理"),
                                                          ui<Struct>(1, 4)
                                            )
                                    )
                            )
                    ),
                    ui<Struct>(1, 1),
                    ui<HCenter>(
                            ui_args<WTextButton>([&term, &item](WTextButton &t) {
                                t.setFocusOrder(0);
                                t.setActionListener([&term, &item]() {
                                    std::wstring msg = L"";
                                    msg += L"余额(含利息)：";
                                    msg += std::to_wstring(item.amount());
                                    msg += L", 借贷：";
                                    msg += std::to_wstring(item.debit());
                                    msgbox<wchar_t, wchar_t, wchar_t>(term, msg, true, L"确定", false, L"");
                                });

                            }, L"余额")
                    ),
                    ui<HCenter>(
                            ui_args<WTextButton>([&term, &item](WTextButton &t) {
                                t.setActionListener([&term, &item]() {
                                    auto name = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入业务名", true,
                                                                                          L"确定", true, L"取消");
                                    auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入存款", true,
                                                                                           L"存入", true, L"取消");
                                    if (value.has_value() && name.has_value()) {
                                        long double v = std::stold(value.value());
                                        item.amountChange.push_back(Transaction{
                                                (long long) time(nullptr),
                                                name.value(),
                                                v
                                        });
                                    }
                                });
                                t.setFocusOrder(1);
                            }, L"存款")
                    ),
                    ui<HCenter>(
                            ui_args<WTextButton>([&term, &item](WTextButton &t) {
                                t.setFocusOrder(2);
                                t.setActionListener([&term, &item]() {
                                    auto name = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入业务名", true,
                                                                                          L"确定", true, L"取消");
                                    auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入取款", true,
                                                                                           L"去出", true, L"取消");
                                    if (value.has_value() && name.has_value()) {
                                        long double v = std::stold(value.value());
                                        item.amountChange.push_back(Transaction{
                                                (long long) time(nullptr),
                                                name.value(),
                                                -v
                                        });
                                    }
                                });
                            }, L"取款")
                    ),

                    ui<HCenter>(
                            ui_args<WTextButton>([&term, &item](WTextButton &t) {
                                t.setFocusOrder(3);
                                t.setActionListener([&term, &item]() {
                                    auto name = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入业务名", true,
                                                                                          L"确定", true, L"取消");
                                    auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入贷款金额",
                                                                                           true,
                                                                                           L"贷款", true, L"取消");
                                    if (value.has_value() && name.has_value()) {
                                        long double v = std::stold(value.value());
                                        item.debitChange.push_back(Transaction{
                                                (long long) time(nullptr),
                                                name.value(),
                                                v
                                        });
                                    }
                                });
                            }, L"贷款")
                    ),
                    ui<HCenter>(
                            ui_args<WTextButton>([&term, &item](WTextButton &t) {
                                t.setFocusOrder(4);
                                t.setActionListener([&term, &item]() {
                                    auto name = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入业务名", true,
                                                                                          L"确定", true, L"取消");
                                    auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入还款金额",
                                                                                           true,
                                                                                           L"还款", true, L"取消");
                                    if (value.has_value() && name.has_value()) {
                                        long double v = std::stold(value.value());
                                        item.debitChange.push_back(Transaction{
                                                (long long) time(nullptr),
                                                name.value(),
                                                -v
                                        });
                                    }
                                });
                            }, L"还款")
                    ),
                    ui<Struct>(2, 2),
                    ui<HCenter>(
                            ui_args<WTextButton>([&term](WTextButton &t) {
                                t.setFocusOrder(5);
                                t.setActionListener([&term]() {
                                    term.pop();
                                });
                            }, L"返回")
                    )
            )
    );

    term.push(widget);
    term.invalidate();
    term.capture();
    term.invalidate();
}


void page::cashReceptionPage(tui::Term &term) {
    using namespace tui;
    std::vector<char> username, pwd;

    auto widget = ui<Center>(
            ui<Box>(
                    ui<VListView>(
                            ui<HCenter>(ui<WText>(L"存取贷业务管理")),
                            ui<Struct>(2, 2),
                            ui<Table<2>>(
                                    tableRow(
                                            ui<WText>(L"卡号："),
                                            ui_args<TextField>([](TextField &t) {
                                                t.setFocusOrder(0);
                                            }, &username, 20)),
                                    tableRow(
                                            ui<WText>(L"密码："),
                                            ui_args<TextField>([](TextField &t) {
                                                t.setFocusOrder(1);
                                            }, &pwd, 20))
                            ),
                            ui<Struct>(2, 2),
                            ui<HCenter>(
                                    ui<HListView>(
                                            ui_args<WTextButton>([&term, &username, &pwd](WTextButton &t) {
                                                t.setFocusOrder(2);
                                                t.setActionListener([&term, &username, &pwd]() {
                                                    auto &db = Database::getInstance()->customer;
                                                    for (auto iter = db.begin(); iter != db.end(); ++iter) {
                                                        if (iter->cardID == std::string(username.data())) {
                                                            if (iter->password == std::string(pwd.data())) {
                                                                // here: login success
                                                                term.pop();
                                                                servicePage(term, *iter);
                                                                return;
                                                            } else {
                                                                msgbox<wchar_t, wchar_t, wchar_t>(term, L"密码错误",
                                                                                                  true,
                                                                                                  L"确定", false, L"");
                                                                return;
                                                            }
                                                        }
                                                    }
                                                    msgbox<wchar_t, wchar_t, wchar_t>(term, L"卡号不存在", true,
                                                                                      L"确定", false, L"");
                                                    return;
                                                });
                                            }, L"登录"),
                                            ui<Struct>(2, 2),
                                            ui_args<WTextButton>([&term](WTextButton &t) {
                                                t.setFocusOrder(3);
                                                t.setActionListener([&term]() {
                                                    term.pop();
                                                });
                                            }, L"返回")
                                    )
                            )
                    )
            )
    );
    term.push(widget);
    term.invalidate();
    term.capture();
    term.invalidate();
}
