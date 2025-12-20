#pragma once

namespace FinEngine {

    class Windowing {
        public:
            virtual ~Windowing() = default;

            virtual void Init();
            virtual void Shutdown();
            virtual void Update();

            static Windowing* Create();
    };

}