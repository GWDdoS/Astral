#include "includes.hpp"


using namespace geode::prelude;



class CheckpointData {
public:
    CheckpointData() = default;

    CheckpointData(PlayerObject* player1, PlayerObject* player2, PlayLayer* playLayer) {
        m_checkpointPlayLayer = utils::FixPlayLayerCheckpoint(playLayer);
        m_checkpointPlayer1 = utils::FixPlayerCheckpoint(player1);
        if (player2)
            m_checkpointPlayer2 = utils::FixPlayerCheckpoint(player2);
        
        // custom shit for the bot, TPS for ingame tps changing and framecount cus ye
        m_tpsValue = playLayer->getTpsValue();
        m_frameCount = playLayer->getFrameCount();
    }

    void apply(PlayerObject* player1, PlayerObject* player2, PlayLayer* playLayer) {
        m_checkpointPlayLayer.apply(playLayer);
        m_checkpointPlayer1.apply(player1);
        if (player2)
            m_checkpointPlayer2.apply(player2);
        
        playLayer->setTpsValue(m_tpsValue);
        playLayer->setFrameCount(m_frameCount);
    }

private:
    utils::FixPlayerCheckpoint m_checkpointPlayer1;
    utils::FixPlayerCheckpoint m_checkpointPlayer2;
    utils::FixPlayLayerCheckpoint m_checkpointPlayLayer;
    float m_tpsValue = tpsValue;
    float m_frameCount = frameCount;
};

class $modify(FixPlayLayer, PlayLayer) {
    struct Fields {
        std::unordered_map<CheckpointObject*, CheckpointData> m_checkpoints;
    };

    void resetLevel() {
        if (m_checkpointArray->count() <= 0)
            m_fields->m_checkpoints.clear();

        PlayLayer::resetLevel();
    }

    void loadFromCheckpoint(CheckpointObject* checkpoint) {
        auto fields = m_fields.self();
        if (fields->m_checkpoints.contains(checkpoint)) {
            PlayLayer::loadFromCheckpoint(checkpoint);

            CheckpointData& data = fields->m_checkpoints[checkpoint];
            data.apply(m_player1, m_gameState.m_isDualMode ? m_player2 : nullptr, this);

            return;
        }

        PlayLayer::loadFromCheckpoint(checkpoint);
    }

    CheckpointObject* createCheckpoint() {
        auto checkpoint = PlayLayer::createCheckpoint();
        if (!checkpoint)
            return checkpoint;

        if (m_gameState.m_currentProgress > 0) {
            CheckpointData data(m_player1, m_gameState.m_isDualMode ? m_player2 : nullptr, this);
            m_fields->m_checkpoints[checkpoint] = std::move(data);
        }

        return checkpoint;
    }

    void removeCheckpoint(bool first) {
        CheckpointObject* checkpoint = nullptr;
        if (m_checkpointArray->count()) {
            if (first) checkpoint = static_cast<CheckpointObject*>(m_checkpointArray->objectAtIndex(0));
            else checkpoint = static_cast<CheckpointObject*>(m_checkpointArray->lastObject());
        }

        auto fields = m_fields.self();
        if (checkpoint && fields->m_checkpoints.contains(checkpoint)) {
            fields->m_checkpoints.erase(checkpoint);
        }

        PlayLayer::removeCheckpoint(first);
    }

    #ifdef GEODE_IS_DESKTOP
    void storeCheckpoint(CheckpointObject* checkpoint) {
        auto oldCheckpoint = static_cast<CheckpointObject*>(m_checkpointArray->objectAtIndex(0));

        PlayLayer::storeCheckpoint(checkpoint);

        auto fields = m_fields.self();
        if (!m_checkpointArray->containsObject(oldCheckpoint) && fields->m_checkpoints.contains(oldCheckpoint)) {
            fields->m_checkpoints.erase(oldCheckpoint);
        }
    }
    #endif
};
