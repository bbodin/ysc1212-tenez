#include <cmath>
#include <SFML/Graphics.hpp>

int WIDTH = 600;
int square_x = 0;
int square_y = 0;
int direction = 1;


sf::Texture texture;
void initTextures() {
    if (!texture.loadFromFile("tree.png")) {
        printf("texture not found");
        exit(1);
    }
}

void renderCar(sf::RenderWindow& window ) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(square_x,square_y);
    sprite.setScale(sf::Vector2f(0.1f, 0.1f));
    // sprite.setTextureRect(sf::IntRect(20, 200, 500, 500));
    window.draw(sprite);
}


void processClick(int x, int y) {
    float distance = std::sqrt((square_x - x) * (square_x - x) + (square_y - y)*(square_y - y));; 
    if (distance < 10) {
        if (direction == 0) direction = 1; else direction = 0;
    }
}

void updateSquare() {
    square_x += direction;
    if (square_x > WIDTH) 
        direction = -direction; 
    if (square_x < 0 )        
        direction = -direction;

}
sf::Font font;
void render_direction (sf::RenderWindow& window ) {
    
    sf::Text text;
    // select the font
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString("Hello world");
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::Red);
    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(100,100);
    // inside the main loop, between window.clear() and window.display()
    window.draw(text);
} 

void renderScreen (sf::RenderWindow& window) {
        // clear the window with black color
        window.clear(sf::Color::White);

        sf::CircleShape cercle(10);

        cercle.setFillColor(sf::Color::Yellow);
        cercle.setPosition(0,0);
        window.draw(cercle);


        sf::RectangleShape rectangle(sf::Vector2f(10,10));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setPosition(square_x,square_y);
        window.draw(rectangle);
} 

int main()
{
    initTextures();
    font.loadFromFile("/usr/share/fonts/liberation-mono/LiberationMono-Bold.ttf");
    sf::Clock my_chronometer;
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen()) {

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::KeyPressed)
               printf("An event occured, type is %d %d\n", event.type, event.key.code);

            if (event.type == sf::Event::MouseButtonPressed) {
                processClick(event.mouseButton.x, event.mouseButton.y);
            }

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        // Once all the rendering/drawing is done
        renderScreen(window);
        render_direction(window);
        renderCar(window);

        float elapse_time = my_chronometer.getElapsedTime().asMilliseconds();

        if (elapse_time >= 50) {
            updateSquare();
            my_chronometer.restart();
        }
        
        window.display();

    }


}