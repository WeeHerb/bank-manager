//
// Created by mslxl on 11/24/2022.
//

// hey, im a nester!
// care shit mountain!

#include<sstream>

#include "custom_account.h"

#include "tui/Widget.h"
#include "glob/wildcard.hpp"
#include "tui/dialog/msgbox.h"
#include "core/data/Database.h"
#include "core/data/Customer.h"

void customerAccountAddPage(tui::Term &term) {
    using namespace tui;
    std::vector<char> number;
    std::vector<char> name;
    std::vector<char> telephone;
    std::vector<char> id;
    bool isVIP = false;

    auto widget = ui<Center>(
            ui<VListView>(
                    ui<Box>(
                            ui<Table<2>>(
                                    tableRow(ui<WText>(L"卡号:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(0);
                                    }, &number, 20)),
                                    tableRow(ui<WText>(L"姓名:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(1);
                                    }, &name, 20)),
                                    tableRow(ui<WText>(L"电话:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(2);
                                    }, &telephone, 20)),
                                    tableRow(ui<WText>(L"身份证:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(3);
                                    }, &id, 20)),
                                    tableRow(ui<Text>(" VIP:"), ui_args<Checkbox>([](Checkbox &b) {
                                        b.setFocusOrder(4);
                                    }, &isVIP))

                            )
                    ),
                    ui<Struct>(2, 1),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>(
                                            [&term, &number, &name, &telephone, &id, &isVIP](WTextButton &btn) {
                                                btn.setFocusOrder(5);
                                                btn.setActionListener([&term, &number, &name, &telephone, &id, &isVIP] {
                                                    Customer newCustomer{
                                                            number.data(),
                                                            name.data(),
                                                            telephone.data(),
                                                            id.data(),
                                                            isVIP,
                                                            0, 0
                                                    };
                                                    Database::getInstance()->customer.push_back(newCustomer);
                                                    term.pop();
                                                });
                                            }, L"添加"),
                                    ui<Struct>(1, 3),
                                    ui_args<WTextButton>([&term](WTextButton &btn) {
                                        btn.setFocusOrder(6);
                                        btn.setActionListener([&term] {
                                            term.pop();
                                        });
                                    }, L"返回")
                            )
                    )
            )
    );
    term.push(widget);
    term.invalidate();
    term.capture();
    term.invalidate();
}

void customerAccountEditPage(tui::Term &term, Customer &customer) {
    using namespace tui;
    std::vector<char> number(customer.cardID.begin(), customer.cardID.end());
    number.push_back('\0');

    std::vector<char> name(customer.name.begin(), customer.name.end());
    name.push_back('\0');

    std::vector<char> telephone(customer.telephone.begin(), customer.telephone.end());
    telephone.push_back('\0');

    std::vector<char> id(customer.id.begin(), customer.id.end());
    id.push_back('\0');

    bool isVIP = customer.vip;

    auto widget = ui<Center>(
            ui<VListView>(
                    ui<Box>(
                            ui<Table<2>>(
                                    tableRow(ui<WText>(L"卡号:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(0);
                                    }, &number, 20)),
                                    tableRow(ui<WText>(L"姓名:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(1);
                                    }, &name, 20)),
                                    tableRow(ui<WText>(L"电话:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(2);
                                    }, &telephone, 20)),
                                    tableRow(ui<WText>(L"身份证:"), ui_args<TextField>([](TextField &b) {
                                        b.setFocusOrder(3);
                                    }, &id, 20)),
                                    tableRow(ui<Text>(" VIP:"), ui_args<Checkbox>([](Checkbox &b) {
                                        b.setFocusOrder(4);
                                    }, &isVIP))

                            )
                    ),
                    ui<Struct>(2, 1),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>(
                                            [&term, &number, &name, &telephone, &id, &isVIP, &customer](WTextButton &btn) {
                                                btn.setFocusOrder(5);
                                                btn.setActionListener([&term, &number, &name, &telephone, &id, &isVIP, &customer] {
                                                    customer.cardID = number.data();
                                                    customer.id = id.data();
                                                    customer.telephone = telephone.data();
                                                    customer.name = name.data();
                                                    customer.vip = isVIP;
                                                    term.pop();
                                                });
                                            }, L"应用"),
                                    ui<Struct>(1, 3),
                                    ui_args<WTextButton>([&term](WTextButton &btn) {
                                        btn.setFocusOrder(6);
                                        btn.setActionListener([&term] {
                                            term.pop();
                                        });
                                    }, L"返回")
                            )
                    )
            )
    );

    term.push(widget);
    term.invalidate();
    term.capture();
    term.invalidate();
}

void page::customerAccountPage(tui::Term &term) {
    using namespace tui;
    auto &db = Database::getInstance()->customer;
    short curPage = 0;

    auto widget = ui<Center>(
            ui<VListView>(
                    ui<HCenter>(
                            ui<AttrFill>(
                                    color::BG_GREEN | color::FG_COMMON,
                                    ui<Box>(
                                            ui<HListView>(std::make_shared<Struct>(1, 4),
                                                          ui<WText>(
                                                                  L"客户账户管理"),
                                                          ui<Struct>(1, 4)
                                            )
                                    )
                            )
                    ),
                    ui<Struct>(2, 2),
                    ui<Box>(
                            ui_args<TableBuilder<15, 7, LinkedList<Customer>, Customer>>(
                                    [](TableBuilder<15, 7, LinkedList<Customer>, Customer> &t) {
                                        t.setHeader(tableRow(
                                                ui<WText>(L"#"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"VIP"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"账户号"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"姓名"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"电话"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"身份证号"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"余额"),
                                                ui<Struct>(1, 1),
                                                ui<WText>(L"借贷")
                                        ));
                                    }, curPage, db, [](short index, Customer &data) {
                                        return tableRow(
                                                ui<Text>(std::to_string(index)),
                                                ui<Struct>(1, 1),
                                                ui<Checkbox>(&data.vip),
                                                ui<Struct>(1, 1),
                                                ui<Text>(data.cardID),
                                                ui<Struct>(1, 1),
                                                ui<Text>(data.name),
                                                ui<Struct>(1, 1),
                                                ui<Text>(data.telephone),
                                                ui<Struct>(1, 1),
                                                ui<Text>(data.id),
                                                ui<Struct>(1, 1),
                                                ui<Text>(std::to_string(data.amount)),
                                                ui<Struct>(1, 1),
                                                ui<Text>("-" + std::to_string(data.debit)));
                                    }
                            )
                    ),
                    ui<Struct>(2, 1),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>([&curPage, &term](WTextButton &b) {
                                                             b.setFocusOrder(0);
                                                             b.setActionListener([&curPage, &term]() {
                                                                 curPage--;
                                                                 term.rebuild();
                                                                 term.invalidate();
                                                             });
                                                         },
                                                         L"上一页"
                                    ),
                                    ui_args<WTextButton>([&curPage, &term](WTextButton &b) {
                                                             b.setFocusOrder(1);
                                                             b.setActionListener([&curPage, &term]() {
                                                                 curPage++;
                                                                 term.rebuild();
                                                                 term.invalidate();
                                                             });
                                                         },
                                                         L"下一页"
                                    )
                            )
                    ),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>([&term](WTextButton &b) {
                                                             b.setFocusOrder(2);
                                                             b.setActionListener([&term]() {
                                                                 customerAccountAddPage(term);
                                                                 term.rebuild();
                                                                 term.invalidate();
                                                             });
                                                         },
                                                         L"添加"
                                    ),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&term](WTextButton &b) {
                                                             b.setFocusOrder(3);
                                                             b.setActionListener([&term]() {
                                                                 auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(
                                                                         term,
                                                                         L"请输入要修改的账户序号",
                                                                         true, L"确定",
                                                                         true, L"取消"
                                                                 );
                                                                 if (value.has_value()) {
                                                                     std::stringstream ss;
                                                                     ss << value.value();
                                                                     int v;
                                                                     ss >> v;
                                                                     auto &db = Database::getInstance()->customer;
                                                                     if (v < 0 || v > db.size()) {
                                                                         msgbox<wchar_t, wchar_t, wchar_t>(
                                                                                 term,
                                                                                 L"无效的序号",
                                                                                 true, L"确定",
                                                                                 false, L"");
                                                                         return;
                                                                     }

                                                                     auto iter = db.begin();
                                                                     for (int i = 0; i < v; i++) ++iter;
                                                                     customerAccountEditPage(term, *iter);
                                                                     term.rebuild();
                                                                 }
                                                                 term.invalidate();
                                                             });
                                                         },
                                                         L"修改"

                                    ),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&term, &curPage](WTextButton &b) {
                                                             b.setFocusOrder(4);
                                                             b.setActionListener([&term, &curPage]() {
                                                                 auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(
                                                                         term,
                                                                         L"请输入要查找的内容，支持 Wildcard 表达式",
                                                                         true, L"确定",
                                                                         true, L"取消"
                                                                 );
                                                                 if (value.has_value()) {
                                                                     auto pattern = value.value();
                                                                     auto &db = Database::getInstance()->customer;
                                                                     int cnt = 0;
                                                                     bool found = false;
                                                                     for (auto iter = db.begin(); iter != db.end(); ++iter, ++cnt) {
                                                                         const auto &item = *iter;
                                                                         if (glob::match(item.id, pattern)
                                                                             || glob::match(item.cardID, pattern)
                                                                             || glob::match(item.telephone, pattern)
                                                                             || glob::match(item.name, pattern)) {
                                                                             curPage = short(cnt / 6);
                                                                             term.rebuild();
                                                                             found = true;
                                                                             break;
                                                                         }
                                                                     }
                                                                     if (!found) {
                                                                         msgbox<wchar_t, wchar_t, wchar_t>(term, L"未找到相关信息",
                                                                                                           true, L"确定",
                                                                                                           false, L"");
                                                                     }
                                                                     term.invalidate();
                                                                 }
                                                             });
                                                         },
                                                         L"搜索"
                                    ),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&term](WTextButton &b) {
                                                             b.setFocusOrder(5);
                                                             b.setActionListener([&term]() {
                                                                 auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(
                                                                         term,
                                                                         L"请输入要删除的账户序号",
                                                                         true, L"确定",
                                                                         true, L"取消"
                                                                 );
                                                                 if (value.has_value()) {
                                                                     std::stringstream ss;
                                                                     ss << value.value();
                                                                     int v;
                                                                     ss >> v;
                                                                     auto &db = Database::getInstance()->customer;
                                                                     if (v < 0 || v > db.size()) {
                                                                         msgbox<wchar_t, wchar_t, wchar_t>(
                                                                                 term,
                                                                                 L"无效的序号",
                                                                                 true, L"确定",
                                                                                 false, L"");
                                                                         return;
                                                                     }

                                                                     auto iter = db.begin();
                                                                     for (int i = 0; i < v; i++) ++iter;
                                                                     db.erase(iter);
                                                                     term.rebuild();
                                                                     term.invalidate();
                                                                 }
                                                             });
                                                         },
                                                         L"删除"
                                    ),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&term](WTextButton &b) {
                                                             b.setFocusOrder(6);
                                                             b.setActionListener([&term]() {
                                                                 term.pop();
                                                                 term.invalidate();
                                                             });
                                                         },
                                                         L"返回"
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