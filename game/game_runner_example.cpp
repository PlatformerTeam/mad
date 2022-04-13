//#include <event/management/producer/EventProducer.hpp>
//#include <event/management/dispatcher/EventDispatcher.hpp>
//#include <event/management/handler/WindowCloseHandler.hpp>
//#include <event/management/producer/SystemListener.hpp>
//#include <event/system/KeyHeld.hpp>
//#include <event/system/KeyPressed.hpp>
//#include <loader/LevelLoader.hpp>
//#include <runner/SequentialRunner.hpp>
//#include <visual/Camera.hpp>
//#include <world/LocalWorld.hpp>
//#include <world/entity/ViewableEntity.hpp>
//
//#include <SFML/Graphics/CircleShape.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>
//#include <spdlog/spdlog.h>
//
//
//class ArrowController : public mad::core::EventHandler {
//public:
//    explicit ArrowController(std::shared_ptr<mad::core::World> world,
//                             mad::core::Entity::Id entity_id)
//        : m_world(std::move(world)),
//          m_entity_id(entity_id) {}
//
//    void handle(const mad::core::Event &event) override {
//        SPDLOG_INFO("handle arrow event");
//
//        auto make_move_intent = [](mad::core::Vec2d dir) {
//            return mad::core::LambdaIntent(
//                    [=](mad::core::Entity &entity, mad::core::EventDispatcher &event_dispatcher) {
//                        mad::core::cast_to<mad::core::ViewableEntity>(entity).move(dir);
//                    });
//        };
//
//        if (event.type == mad::core::Event::Type::KeyPressed) {
//            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyPressed>(event);
//            if (keystroke.key_id == sf::Keyboard::Key::Up) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, -10.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Down) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, 10.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Left) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{-10.0f, 0.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Right) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{10.0f, 0.0f}));
//            }
//        } else if (event.type == mad::core::Event::Type::KeyHeld) {
//            const auto &keystroke = mad::core::const_cast_to<mad::core::KeyHeld>(event);
//            if (keystroke.key_id == sf::Keyboard::Key::Up) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, -0.01f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Down) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.0f, 0.01f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Left) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{-0.01f, 0.0f}));
//            } else if (keystroke.key_id == sf::Keyboard::Key::Right) {
//                m_world->manipulate_entity_id(m_entity_id, make_move_intent(mad::core::Vec2d{0.01f, 0.0f}));
//            }
//        }
//    }
//
//    std::unordered_set<mad::core::Event::Type> handled_types() override {
//        return {mad::core::Event::Type::KeyPressed, mad::core::Event::Type::KeyHeld};
//    }
//
//private:
//    std::shared_ptr<mad::core::World> m_world;
//    mad::core::Entity::Id m_entity_id;
//};
//
//class ExampleLevelLoader : public mad::core::LevelLoader {
//public:
//    std::unique_ptr<mad::core::LevelRunner> load() override {
//
//    }
//};

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    sf::Color bgColor;
    float color[3] = { 0.f, 0.f, 0.f };

    // здесь мы будем использовать массив char. Чтобы использовать
    // std::string нужно сделать действия, описанные во второй части
    char windowTitle[255] = "ImGui + SFML = <3";
    window.setTitle(windowTitle);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Sample window"); // создаём окно

        // Инструмент выбора цвета
        if (ImGui::ColorEdit3("Background color", color)) {
            // код вызывается при изменении значения, поэтому всё
            // обновляется автоматически
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        ImGui::InputText("Window title", windowTitle, 255);

        if (ImGui::Button("Update window title")) {
            // этот код выполняется, когда юзер жмёт на кнопку
            // здесь можно было бы написать
            // if(ImGui::InputText(...))
            window.setTitle(windowTitle);
        }
        ImGui::End(); // end window

        window.clear(bgColor); // заполняем окно заданным цветом
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}