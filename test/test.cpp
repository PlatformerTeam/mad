#include <gtest/gtest.h>

#include <Core.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include <math.h>

using namespace testing;

TEST(Core, a_plus_b_simple) {
core::Core obj;

EXPECT_EQ("Hello from Core\n", obj.hello());
}

inline float dt;


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    float w = 1500;
    float h = 1000;
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML window");
    sf::Clock clock;
    float lastTime = 0;

    b2Vec2 gravity(0.0f, -9.8f);
    b2World world(gravity);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(1500.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    b2Body* body;
    b2Body* body1;
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(500.0f, 1000.0f);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(300.0f, 50.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 1.0f;

        body->CreateFixture(&fixtureDef);
    }
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(500.0f, 900.0f);
        body1 = world.CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(50.0f, 50.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 0.5f;
        fixtureDef.friction = 0.3f;

        body1->CreateFixture(&fixtureDef);
    }




    float timeStep = 1.0f / 120.0f;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;



    /*ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
        MySaveFunction();
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);*/
    while (window.isOpen()) {
        world.Step(timeStep, velocityIterations, positionIterations);
        {
            b2Vec2 position = body->GetPosition();
            float angle = body->GetAngle();
            printf("b %4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        }
        {
            b2Vec2 position = body1->GetPosition();
            float angle = body1->GetAngle();
            printf("b1 %4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        }



        sf::Event event{};
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();

        //draw

        float velocity_k = 50;
        sf::Vector2<float> velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -1;
        } else {
            velocity.x = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            velocity.y = 1;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            velocity.y = -1;
        } else {
            velocity.y = 0;
        }
        velocity *= velocity_k;
        body1->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));

        sf::RectangleShape rect;
        rect.setOrigin(300, 50);
        rect.setSize(sf::Vector2<float>(600, 100));
        rect.setFillColor(sf::Color(0, 255, 0));
        rect.setPosition(body->GetPosition().x, h - body->GetPosition().y);
        rect.setRotation(-body->GetAngle() * (180/M_PI));
        //rect.setRotation(r++);
        window.draw(rect);
        printf("%4.2f\n", rect.getRotation());

        sf::RectangleShape rect1;
        rect1.setOrigin(50, 50);
        rect1.setSize(sf::Vector2<float>(100, 100));
        rect1.setFillColor(sf::Color(0, 255, 0));
        rect1.setPosition(body1->GetPosition().x, h - body1->GetPosition().y);
        rect1.setRotation(-body1->GetAngle()* (180/M_PI));
        window.draw(rect1);

        window.display();

        //fps
        sf::Time time = clock.getElapsedTime();
        dt = time.asSeconds() - lastTime;
        double fps = 1 / (time.asSeconds() - lastTime);
        lastTime = time.asSeconds();
        window.setTitle(std::to_string(fps));
    }
    return RUN_ALL_TESTS();
}
