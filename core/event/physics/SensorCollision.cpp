#include "SensorCollision.hpp"
#include "spdlog/spdlog.h"
mad::core::SensorCollision::SensorCollision(int m_id) : Event(Event::Type::SensorCollision), m_id(m_id) {
    SPDLOG_INFO("sensor {}", m_id);
}
