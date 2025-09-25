#include "../../includes.hpp"
// someone asked for me to showcase wiht this one time so here it is
bool accuratePercentage = false;
int decimalPlaces = 4;
// i was told this would work? bro idk ill just remove this tbh
class $modify(PlayLayer) {
    float customGetProgress() {
        try {
            return utils::getActualProgress(this);
        } catch (...) {
            if (m_player1 && m_levelLength > 0) {
                float percent = (m_player1->getPositionX() / m_levelLength) * 100.0f;
                if (percent > 100.0f) percent = 100.0f;
                if (percent < 0.0f) percent = 0.0f;
                return percent;
            }
            return this->getCurrentPercent();
        }
    }
    
    void updateProgressbar() {
        PlayLayer::updateProgressbar();
        
        if (!accuratePercentage || !m_percentageLabel) return;
        
        float percent = customGetProgress();
        m_percentageLabel->setString(fmt::format("{:.{}f}%", percent, decimalPlaces).c_str());
        
        if (m_progressFill && m_progressBar) {
            m_progressFill->setTextureRect({
                0, 0,
                (m_progressBar->getTextureRect().getMaxX() - 5) * percent / 100.f,
                m_progressBar->getTextureRect().getMaxY() / 2
            });
        }
    }
};