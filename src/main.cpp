#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

#define SHADER_GAME_FILENAME "../shaders/game.frag"
#define SHADER_NOISE_FILENAME "../shaders/noise.frag"
#define SHADER_GUI_FILENAME "../shaders/gui.frag"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

int main() {
    if (!sf::Shader::isAvailable()) {
        std::cout << "The Shader is not available!" << std::endl;
        return -1;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Shader Example", sf::Style::Titlebar | sf::Style::Close);
    //window.setFramerateLimit(5);
    sf::ContextSettings settings = window.getSettings();
    std::cout << "OpenGL version:"<< settings.majorVersion << "." << settings.minorVersion << std::endl;

    // setup game layer
    sf::RenderTexture gameTexture;
    gameTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Sprite gameSprite(gameTexture.getTexture());

    // setup gui layer
    sf::Texture guiTexture;
    guiTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::Sprite guiSprite(guiTexture);

    // create/load shaders
    sf::Shader gameShader;
    gameShader.loadFromFile(SHADER_GAME_FILENAME, sf::Shader::Fragment);
    sf::Shader noiseShader;
    noiseShader.loadFromFile(SHADER_NOISE_FILENAME, sf::Shader::Fragment);
    sf::Shader guiShader;
    guiShader.loadFromFile(SHADER_GUI_FILENAME, sf::Shader::Fragment);

    // loop setup

    float scrollSize = 5;

    static std::default_random_engine e(time(0));
    static std::uniform_real_distribution<> dis(0, 100000); // rage 0 - 1

    noiseShader.setUniform("random", (int)dis(e));
    gameShader.setUniform("resolution", sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    gameShader.setUniform("tex", gameTexture.getTexture());

    sf::Clock clk;

    gameTexture.clear(sf::Color::Red);
    gameTexture.draw(gameSprite, &noiseShader);
    gameTexture.display();

    window.clear();
    window.draw(gameSprite);
    window.display();
    // loop
    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type){
                case sf::Event::Closed:
                    window.close();
                case sf::Event::MouseWheelScrolled:
                    scrollSize = fmax(floor(scrollSize + event.mouseWheelScroll.delta), 0.5);
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        gameShader.setUniform("scrollSize", scrollSize);
        gameShader.setUniform("mousePos", sf::Vector2f(mousePos.x, WINDOW_HEIGHT - mousePos.y));
        gameShader.setUniform("mouseLeftDown", sf::Mouse::isButtonPressed(sf::Mouse::Left));
        gameShader.setUniform("mouseRightDown", sf::Mouse::isButtonPressed(sf::Mouse::Right));

        guiShader.setUniform("scrollSize", scrollSize);
        guiShader.setUniform("mousePos", sf::Vector2f(mousePos.x, WINDOW_HEIGHT - mousePos.y));

        //gameTexture.clear();
        gameTexture.draw(gameSprite, &gameShader);
        gameTexture.display();

        window.clear();
        window.draw(gameSprite);
        window.draw(guiSprite, &guiShader);
        window.display();
    }

    return 0;
}