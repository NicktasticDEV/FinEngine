#pragma once

namespace FinEngine {

    class System {
        public:
            virtual ~System() = default;

            virtual void Init();
            virtual void Shutdown();

            static System* Create();
    };

}