//
// Created by mslxl on 11/24/2022.
//


#include "../data/Customer.h"
#include "custom_account.h"
#include "tui/Widget.h"
#include "core/data/Database.h"

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


void page::customerAccountPage(tui::Term &term) {
    using namespace tui;
    auto &db = Database::getInstance()->customer;
    auto infoIter = db.begin();
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
                    ui<TableBuilder<7, 5, LinkedList<Customer>, Customer>>(curPage, db, [&db, &infoIter](Customer &data) {
                        return tableRow(
                                ui<Checkbox>(&data.vip),
                                ui<Text>(data.cardID),
                                ui<Text>(data.name),
                                ui<Text>(data.telephone),
                                ui<Text>(data.id),
                                ui<Text>(std::to_string(data.amount)),
                                ui<Text>("-" + std::to_string(data.debit)));
                    }),
                    ui<Struct>(2, 1),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>([&term](WTextButton &b) {
                                                             b.setFocusOrder(0);
                                                             b.setActionListener([&term]() {
                                                                 customerAccountAddPage(term);
                                                                 term.invalidate();
                                                             });
                                                         },
                                                         L"添加"
                                    ),
                                    ui<Struct>(1, 1),
                                    ui_args<WTextButton>([](WTextButton &b) {
                                                             b.setFocusOrder(3);
                                                         },
                                                         L"搜索"
                                    ),
                                    ui<Struct>(1, 1),
                                    ui_args<Button>([&term](Button &b) {
                                                        b.setFocusOrder(4);
                                                        b.setActionListener([&term] {
                                                            term.pop();
                                                        });
                                                    },
                                                    ui<WText>(L"返回")
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