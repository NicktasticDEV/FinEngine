#pragma once

#include <vector>
#include "FinEngine/Core/FinBasic.h"

#include <algorithm>

namespace FinEngine {

    template <typename T>
    class FINENGINE_API FinTypedGroup : public FinBasic  {

        public:
            FinTypedGroup() : FinBasic() {};
            ~FinTypedGroup() = default;

            std::vector<T*> members;

            void update() override {
                for (auto& member : members) {
                    if (member->active) {
                        member->update();
                    }
                }
            };

            void draw() override {
                for (auto& member : members) {
                    if (member->visible) {
                        member->draw();
                    }
                }
            };

            void destroy() override {
                FinBasic::destroy();
                
                for (auto& member : members) {
                    member->destroy();
                }
                members.clear();
            };

            void add(T* member) {
                members.push_back(member);
            };

            void remove(T* member) {
                members.erase(std::remove(members.begin(), members.end(), member), members.end());
            };
    };

    using FinGroup = FinTypedGroup<FinBasic>;

}