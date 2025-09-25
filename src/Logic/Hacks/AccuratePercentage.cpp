#include "../../includes.hpp"
// someone asked for me to showcase wiht this one time so here it is
bool accuratePercentage = false;
int decimalPlaces = 4;

class $modify(PlayLayer) {
    void updateProgressbar() {
        PlayLayer::updateProgressbar();
        
        if (!accuratePercentage || !m_percentageLabel) return;
        
        float percent = utils::getActualProgress(this);
        m_percentageLabel->setString(fmt::format("{:.{}f}%", percent, decimalPlaces).c_str());
        m_progressFill->setTextureRect({
            0, 0,
            (m_progressBar->getTextureRect().getMaxX() - 5) * percent / 100.f,
            m_progressBar->getTextureRect().getMaxY() / 2
        });
    }
};