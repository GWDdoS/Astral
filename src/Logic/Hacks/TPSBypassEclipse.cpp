// THIS NEEDS A MAJOR UPDATE IN THE FUTURE TO FIX FPS VALUES; NAT FPS FIX AND THE PLATFORM BASED MEM CALC FIX
// eclipse would modify original memory patches or smt
// add lock delta

#include "../../includes.hpp"


class $modify(TPSBypassHook, GJBaseGameLayer) {
    struct Fields {
        double extraDelta = 0.0;
    };
    
    void update(float dt) override {
        auto fields = m_fields.self();
        fields->extraDelta += dt;
        
        auto spt = 1.0 / tpsValue; // ticks PER second
        auto steps = std::round(fields->extraDelta / spt);
        auto newDelta = steps * spt;
        fields->extraDelta -= newDelta;
        
        GJBaseGameLayer::update(newDelta);
    }
};