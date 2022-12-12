//
// Created by mslxl on 12/13/2022.
//

#include "transaction_query.h"
#include "tui/Widget.h"
#include "core/data/Database.h"
#include "tui/dialog/msgbox.h"
#include "glob/wildcard.hpp"

void queryPage(tui::Term &term, Customer &item) {
    using namespace tui;
    std::vector<Transaction> allTrans(item.amountChange.begin(), item.amountChange.end());
    std::copy(item.debitChange.begin(), item.debitChange.end(), std::back_inserter(allTrans));
    std::sort(allTrans.begin(), allTrans.end());
    std::reverse(allTrans.begin(), allTrans.end());
    short page = 0;
    auto widget = ui<Center>(
            ui<VListView>(
                    ui<HCenter>(
                            ui<AttrFill>(
                                    color::BG_GREEN | color::FG_COMMON,
                                    ui<Box>(
                                            ui<HListView>(std::make_shared<Struct>(1, 4),
                                                          ui<WText>(
                                                                  L"业务查询"),
                                                          ui<Struct>(1, 4)
                                            )
                                    )
                            )
                    ),
                    ui<Struct>(2, 2),
                    ui<Box>(
                            ui_args<TableBuilder<5, 7, std::vector<Transaction>, Transaction>>(
                                    [](TableBuilder<5, 7, std::vector<Transaction>, Transaction> &table) {
                                        table.setHeader(tableRow(
                                                ui<WText>(L"日期"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"名称"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"存款变化")
                                        ));

                                    }, page, allTrans, [](short index, Transaction &transaction) {
                                        return tableRow(
                                                ui<Text>(transaction.timeStr()),
                                                ui<Struct>(1, 1),
                                                ui<Text>(transaction.name),
                                                ui<Struct>(1, 1),
                                                ui<Text>(std::to_string(transaction.offset))
                                        );
                                    })
                    ),
                    ui<Struct>(1, 1),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>([&page, &term](WTextButton &t) {
                                        t.setFocusOrder(0);
                                        t.setActionListener([&page, &term]() {
                                            page--;
                                            term.rebuild();
                                            term.invalidate();
                                        });
                                    }, L"上一页"),
                                    ui_args<WTextButton>([&page, &term](WTextButton &t) {
                                        t.setFocusOrder(1);
                                        t.setActionListener([&page, &term]() {
                                            page++;
                                            term.rebuild();
                                            term.invalidate();
                                        });
                                    }, L"下一页"),
                                    ui<Struct>(2,2),
                                    ui_args<WTextButton>([&page, &allTrans, &term](WTextButton &t) {
                                        t.setFocusOrder(2);
                                        t.setActionListener([&page, &allTrans, &term]() {
                                            auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term,
                                                                                                   L"请输入要搜索的关键字(支持Wildcard)",
                                                                                                   true, L"搜索", true,
                                                                                                   L"取消");
                                            if (value.has_value()) {
                                                auto pattern = value.value();
                                                auto elem = std::find_if(allTrans.begin(), allTrans.end(),
                                                                         [&pattern](const Transaction &t) {
                                                                             return glob::match(t.name, pattern);
                                                                         });
                                                if (elem == allTrans.end()) {
                                                    msgbox<wchar_t, wchar_t, wchar_t>(term, L"未找到相关信息",
                                                                                      true, L"确定",
                                                                                      false, L"");
                                                } else {
                                                    page = short((elem - allTrans.begin()) / 6);
                                                    term.rebuild();
                                                    term.invalidate();
                                                }
                                            }
                                        });
                                    }, L"搜索")
                            )
                    ),

                    ui<HCenter>(
                            ui_args<WTextButton>([&term](WTextButton &t) {
                                t.setFocusOrder(3);
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

void page::transactionQueryPage(tui::Term &term) {
    using namespace tui;
    std::vector<char> username, pwd;

    auto widget = ui<Center>(
            ui<Box>(
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
                                                                queryPage(term, *iter);
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
