#pragma once

namespace FinEngine {

    class System {
        public:
            virtual ~System() = default;

            virtual void Init() = 0;
            virtual void Shutdown() = 0;

            static System* Create();
    };

}