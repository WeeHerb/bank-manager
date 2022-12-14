//
// Created by mslxl on 11/16/2022.
//

#include "meun.h"
#include "custom_account.h"
#include "staff_manager.h"
#include "cash_reception.h"
#include "transaction_query.h"
#include "bank_queue.h"
#include "login.h"

#include "core/data/database.h"
#include "bank_map.h"
#include "tui/dialog/msgbox.h"

void page::menuPage(tui::Term &term) {
    using namespace tui;
    auto widget = ui<Center>(
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
                    ui_args<Button>([&term](Button &b) {
                        b.setFocusOrder(0);
                        b.setActionListener([&term]() {
                            if (page::loginPage(term))
                                staffManagerPage(term);
                        });
                    }, ui<WText>(L"1.银行职员管理")),
                    ui_args<Button>([&term](Button &b) {
                        b.setFocusOrder(1);
                        b.setActionListener([&term]() {
                            if (page::loginPage(term))
                                customerAccountPage(term);
                        });
                    }, ui<WText>(L"2.客户账号管理")),
                    ui_args<Button>([&term](Button &b) {
                        b.setFocusOrder(2);
                        b.setActionListener([&term]() {
                            cashReceptionPage(term);
                        });
                    }, ui<WText>(L"3.存取贷业务管理")),
                    ui_args<Button>([&term](Button &b) {
                        b.setFocusOrder(3);
                        b.setActionListener([&term]() {
                            transactionQueryPage(term);
                        });
                    }, ui<WText>(L"4.业务查询")),
                    ui_args<Button>([&term](Button &b) {
                        b.setFocusOrder(4);
                        b.setActionListener([&term]() {
                            queuePage(term);
                        });
                    }, ui<WText>(L"5.银行排队管理")),
                    ui_args<Button>([&term](Button &b) {
                        b.setFocusOrder(5);
                        b.setActionListener([&term]() {
                            mapPage(term);
                        });
                    }, ui<WText>(L"6.银行网点查询")),
                    ui<Struct>(2, 1),

                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<Button>(
                                            [&term](Button &b) {
                                                b.setFocusOrder(6);
                                                b.setActionListener([&term]() {
                                                    Database::getInstance()->flush();
                                                    std::exit(0);
                                                });

                                            },
                                            ui<Box>(
                                                    std::make_shared<WText>(L"保存退出")
                                            )
                                    ),
                                    ui<Struct>(1, 8),
                                    ui_args<Button>(
                                            [&term](Button &b) {
                                                b.setFocusOrder(7);
                                                b.setActionListener([&term]() {
                                                    if (msgbox<wchar_t, wchar_t, wchar_t>(term, L"退出并不保存信息?",
                                                                                          true, L"确定",
                                                                                          true, L"取消"))
                                                        std::exit(0);
                                                });
                                            },
                                            ui<Box>(
                                                    std::make_shared<WText>(L"退出登录")
                                            )
                                    )
                            )
                    )
            )
    );
    term.push(widget);
    term.invalidate();
    term.capture();
}