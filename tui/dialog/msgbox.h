//
// Created by mslxl on 11/22/2022.
//


#pragma once

#include<string>
#include "../Term.h"
#include "../widget/Box.h"
#include "../widget/Struct.h"
#include "../widget/Center.h"
#include "../widget/BasicText.h"
#include "../widget/HListView.h"
#include "../widget/VListView.h"
#include "../widget/Visible.h"
#include "../widget/Button.h"

namespace tui {
    template<class T, class Y=T, class N=T>
    bool msgbox(Term &term, std::basic_string<T> msg,
                bool confirm, std::basic_string<Y> confirmText,
                bool cancel, std::basic_string<N> cancelText) {
        bool ans = true;
        auto page = ui<Center>(
                ui<Box>(
                        ui<VListView>(
                                ui<HCenter>(
                                        ui<BasicText<std::basic_string<T>>>(msg)
                                ),
                                ui<Struct>(1, 1),
                                ui<HCenter>(ui<HListView>(
                                                    ui<Struct>(2, 1),
                                                    ui<Visible>(
                                                            confirm,
                                                            ui_args<Button>(
                                                                    [&ans, &term](Button &b) {
                                                                        b.setFocusOrder(1);
                                                                        b.setActionListener([&ans, &term]() {
                                                                            ans = true;
                                                                            term.pop();
                                                                        });
                                                                    },
                                                                    ui<BasicText<std::basic_string<Y>>>(confirmText)
                                                            )
                                                    ),
                                                    ui<Struct>(2, 1),
                                                    ui<Visible>(
                                                            cancel,
                                                            ui_args<Button>(
                                                                    [&ans, &term](Button &b) {
                                                                        b.setFocusOrder(2);
                                                                        b.setActionListener([&ans, &term]() {
                                                                            ans = false;
                                                                            term.pop();
                                                                        });
                                                                    },
                                                                    ui<BasicText<std::basic_string<N>>>(cancelText)
                                                            )
                                                    ),
                                                    ui<Struct>(2, 1)
                                            )
                                )
                        )
                )
        );

        term.push(page);
        term.invalidate();
        term.capture();
        term.invalidate();

        return ans;
    }
}