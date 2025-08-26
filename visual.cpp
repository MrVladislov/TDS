#include <SFML/Graphics.hpp>
#include "visual.h"

class Button {
public:
    using Callback = std::function<void()>;

    Button(const sf::Vector2f& position, 
           const std::string& label, 
           const sf::Font& font, 
           Callback callback)
        : m_text(font, label, 18),
          m_callback(callback) 
    {
        m_shape.setSize({140, 40});
        m_shape.setPosition(position);
        m_shape.setFillColor(sf::Color(70, 70, 70));
        m_shape.setOutlineThickness(2);
        m_shape.setOutlineColor(sf::Color::White);

        //const sf::FloatRect textBounds = m_text.getLocalBounds();
        
        m_text.setPosition(
            sf::Vector2f( // Явное создание вектора
                position.x ,
                position.y+10
            )
        );
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(m_shape);
        window.draw(m_text);
    }

    bool checkClick(const sf::Vector2i& mousePos) const {
        return m_shape.getGlobalBounds().contains(sf::Vector2f(mousePos));
    }

    void onClick() const {
        m_callback();
    }

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    Callback m_callback;
};

class GameUI {
public:
    GameUI(sf::RenderWindow& window, const sf::Font& font)
        : m_window(window),
          m_font(font),
          m_goldText(font, "Gold: 100", 24),
          m_healthText(font, "Health: 10", 24)
    {
        m_infoPanel.setSize({200, 600});
        m_infoPanel.setFillColor(sf::Color(50, 50, 50, 200));
        m_infoPanel.setPosition(sf::Vector2f(800, 0));

        m_goldText.setPosition(sf::Vector2f(820, 20));
        m_healthText.setPosition(sf::Vector2f(820, 60));

        m_buttons.emplace_back(
            sf::Vector2f(810, 100),
            "Basic Tower (50)",
            font,
            [this]() { placeTower(50); }
        );
    }

    void update(int gold, int health) {
        m_goldText.setString("Gold: " + std::to_string(gold));
        m_healthText.setString("Health: " + std::to_string(health));
    }

    void handleEvent(const sf::Event& event) {
        if (event.is<sf::Event::MouseButtonReleased>()) {
            const auto mousePos = sf::Mouse::getPosition(m_window);
            for (auto& btn : m_buttons) {
                if (btn.checkClick(mousePos)) {
                    btn.onClick();
                }
            }
        }
    }

    void draw() const {
        m_window.draw(m_infoPanel);
        m_window.draw(m_goldText);
        m_window.draw(m_healthText);
        for (const auto& btn : m_buttons) {
            btn.draw(m_window);
        }
    }

private:
    void placeTower(int cost) const {
        std::cout << "Placing tower for " << cost << " gold\n";
    }

    sf::RenderWindow& m_window;
    const sf::Font& m_font;
    sf::RectangleShape m_infoPanel;
    sf::Text m_goldText;
    sf::Text m_healthText;
    std::vector<Button> m_buttons;
};