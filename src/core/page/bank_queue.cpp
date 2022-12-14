//
// Created by mslxl on 12/13/2022.
//

#include <queue>
#include <sstream>
#include <codecvt>
#include <locale>

#include "bank_queue.h"
#include "tui/Widget.h"
#include "tui/dialog/msgbox.h"
#include "core/data/Database.h"

void page::queuePage(tui::Term &term) {
    using namespace tui;
    std::queue<std::pair<int, Customer *> > queue;
    std::queue<std::pair<int, Customer *> > queueVip;
    unsigned int counter = 0;

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
                            ui_args<WTextButton>([&term, &counter, &queue, &queueVip](WTextButton &t) {
                                t.setActionListener([&term, &counter, &queue, &queueVip]() {
                                    auto value = inputbox<char, wchar_t, wchar_t, wchar_t>(term, L"请输入账户名", true,
                                                                                           L"确定", true, L"取消");
                                    if (value.has_value()) {
                                        auto pattern = value.value();
                                        auto &db = Database::getInstance()->customer;
                                        Customer *ptr = nullptr;
                                        for (auto iter = db.begin(); iter != db.end(); ++iter) {
                                            if (iter->cardID == pattern) {
                                                ptr = &*iter;
                                                break;
                                            }
                                        }
                                        if (ptr == nullptr) {
                                            msgbox<wchar_t, wchar_t, wchar_t>(term, L"不存在此用户", true, L"确定",
                                                                              false, L"");
                                            return;
                                        }
                                        counter++;
                                        if (ptr->vip) {
                                            queueVip.emplace(counter, ptr);
                                        } else {
                                            queue.emplace(counter, ptr);
                                        }
                                        std::wstring msg = L"取号成功，您是:";
                                        msg += std::to_wstring(counter);
                                        msg += L"号";
                                        msgbox<wchar_t, wchar_t, wchar_t>(term, msg, true, L"确定",
                                                                          false, L"");
                                    }
                                });
                                t.setFocusOrder(0);
                            }, L"取号")
                    ),
                    ui<Struct>(2, 2),
                    ui<HCenter>(
                            ui<HListView>(
                                    ui_args<WTextButton>([&term, &queue, &queueVip](WTextButton &t) {
                                        t.setActionListener([&term, &queue, &queueVip]() {
                                            if (queue.empty() && queueVip.empty()) {
                                                msgbox<wchar_t, wchar_t, wchar_t>(term, L"无用户排队", true, L"确定",
                                                                                  false, L"");
                                                return;
                                            }
                                            if(!queue.empty()){
                                                auto data = queue.front();
                                                queue.pop();
                                                std::wstringstream  wss;
                                                std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
                                                wss << L"请" << data.first << L"号" << conv.from_bytes(data.second->name) << L"前往普通窗口";
                                                msgbox<wchar_t, wchar_t, wchar_t>(term, wss.str(), true, L"确定",
                                                                                  false, L"");
                                            }else{
                                                auto data = queueVip.front();
                                                queueVip.pop();
                                                std::wstringstream  wss;
                                                std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
                                                wss << L"请" << data.first << L"号" << conv.from_bytes(data.second->name) << L"前往普通窗口";
                                                msgbox<wchar_t, wchar_t, wchar_t>(term, wss.str(), true, L"确定",
                                                                                  false, L"");
                                            }

                                        });
                                        t.setFocusOrder(1);
                                    }, L"普通窗口：下一位"),
                                    ui<Struct>(2, 2),
                                    ui_args<WTextButton>([&term, &queue, &queueVip](WTextButton &t) {
                                        t.setActionListener([&term, &queue, &queueVip]() {
                                            if (queue.empty() && queueVip.empty()) {
                                                msgbox<wchar_t, wchar_t, wchar_t>(term, L"无用户排队", true, L"确定",
                                                                                  false, L"");
                                                return;
                                            }
                                            if(!queueVip.empty()){
                                                auto data = queueVip.front();
                                                queueVip.pop();
                                                std::wstringstream  wss;
                                                std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
                                                wss << L"请" << data.first << L"号" << conv.from_bytes(data.second->name) << L"前往VIP窗口";
                                                msgbox<wchar_t, wchar_t, wchar_t>(term, wss.str(), true, L"确定",
                                                                                  false, L"");
                                            }else{
                                                auto data = queue.front();
                                                queue.pop();
                                                std::wstringstream  wss;
                                                std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
                                                wss << L"请" << data.first << L"号" << conv.from_bytes(data.second->name) << L"前往VIP窗口";
                                                msgbox<wchar_t, wchar_t, wchar_t>(term, wss.str(), true, L"确定",
                                                                                  false, L"");
                                            }
                                        });
                                        t.setFocusOrder(2);
                                    }, L"VIP窗口：下一位")
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

