#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f rotate(sf::Vector2f v, const float angle);
sf::Vector2f calculateMovement();

int main()
{
        sf::RenderWindow window(sf::VideoMode(600, 600), "App");
        window.setMouseCursorVisible(false);

        sf::Texture texture;
        if (!texture.loadFromFile("texture.jpg"))
        {
                return EXIT_FAILURE;
        }

        sf::Sprite background;
        background.setTexture(texture);

        const sf::Vector2i center(300.0f, 300.0f);
        float rotation = 0.0f;

        const float speed = 200;
        sf::CircleShape circle(20.0f);
        circle.setFillColor(sf::Color::Red);
        circle.setOrigin(20.0f, 20.0f);
        circle.setPosition(0, 0);

        sf::Clock clock;
        sf::Time dt;

        while (window.isOpen())
        {
                dt = clock.restart();

                sf::Event event;
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                        {
                                window.close();
                        }
                }

                // Handle mouse movement, update rotation
                sf::Vector2i delta = center - sf::Mouse::getPosition(window);
                if (delta != sf::Vector2i(0, 0))
                {
                        rotation += delta.x / 10;
                        sf::Mouse::setPosition(center, window);
                }

                // Handle keyboard movement, update position
                sf::Vector2f movement = calculateMovement();

                // Update the circle position
                movement = rotate(movement, rotation);
                circle.move(movement * speed * dt.asSeconds());

                // Update the view
                //sf::View view({ 300, 300 }, { 600, -600 });
                sf::View view;
                view.setSize(600, -600);
                view.setRotation(rotation);
                view.setCenter(circle.getPosition());
                window.setView(view);

                window.clear();
                window.draw(background);
                window.draw(circle);
                window.display();
        }
}

sf::Vector2f rotate(sf::Vector2f v, const float angle)
{
        sf::Vector2f copy = v;
        float cs = std::cos(angle * (3.14159 / 180));
        float sn = std::sin(angle * (3.14159 / 180));

        v.x = copy.x * cs - copy.y * sn;
        v.y = copy.x * sn + copy.y * cs;

        return v;
}

sf::Vector2f calculateMovement()
{
        sf::Vector2f movement;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                movement.y += 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                movement.y -= 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                movement.x -= 1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                movement.x += 1;

        return movement;
}
