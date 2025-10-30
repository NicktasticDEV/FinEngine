#pragma once
namespace FinEngine {

    class Audio {
        public:
            virtual ~Audio() = default;

            virtual void Init() = 0;
            virtual void Shutdown() = 0;
            virtual void TestSound() = 0;

            static Audio* Create();
    };

}