#include <SFML/Graphics.hpp>
#include "header.h"
#include "World.h"
#include "Plane.h"
#include "Vector3.h"
#include "Cube.h"
#include <memory>

#define DEBUG false

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "UMotor");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock deltaClock;

    Vector3 v(0.f, 0.f, 0.f);
    // Create graphics world
    World w;
    std::shared_ptr<Plane> plane(new Plane(Vector3(0.f, 0.f, 0.f), 3.0f));
    sf::Texture tex;
    tex.setSmooth(true);
    if(!tex.loadFromFile("Skybox/bluecloud_lf.jpg"))
	std::cout << "Error file" << std::endl;
    plane->setTexture(tex);

    std::shared_ptr<Cube> cube(new Cube(0.2, Vector3(0, 0, 0)));
    std::shared_ptr<Cube> cube2(new Cube(0.5, Vector3(1.2, 0, 0)));
    w.addEntity(cube);
    w.addEntity(plane);
    //w.addEntity(cube2);
    int lastX = 0;
    int lastY = 0;
    bool mousePressed = false;

    while (window.isOpen())
    {
	sf::Time dt = deltaClock.restart();
	float deltaTime = dt.asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

	    if (event.type == sf::Event::MouseButtonPressed)
	    {
	    	mousePressed = true;
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }
	    if (event.type == sf::Event::MouseButtonReleased)
	    {
	    	mousePressed = false;
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }
	    if (event.type == sf::Event::MouseMoved)
	    {
		cube->isSelected(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            }

	    Vector3 tr(0, 0, 0);
	    float speed = 0.1f * 100.0f;

	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    {
		tr = tr + Vector3(-speed * deltaTime, 0, 0);
	    }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	    {
		tr = tr + Vector3(speed * deltaTime, 0, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	    {
		tr = tr + Vector3(0, -speed * deltaTime, 0);
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    {
		tr = tr + Vector3(0, speed * deltaTime, 0);
	    }
	
	    if(tr != Vector3(0, 0, 0))
	    {
		cube->translate(tr);
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	    {
		cube->scale(Vector3(1.1f, 1.1f, 1.1f));
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	    {
		cube->scale(Vector3(0.9f, 0.9f, 0.9f));
	    }
		
	    if (mousePressed)
	    {

		float angleY = (lastX - event.mouseMove.x) / 10.0f;
		float angleX = (lastY - event.mouseMove.y) / 10.0f;

		if(DEBUG)
		{
			std::cout << "angleX : " << angleX << std::endl;
			std::cout << "angleY : " << angleY << std::endl;
		}

		cube->rotate(angleX, angleY);
		//cube2->rotate(angleX, angleY);
		
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }
	    
    	}
	
	cube->rotate(0, 0);
        window.clear(sf::Color::White);
        //window.draw(shape);
	w.draw(window);
        window.display();
	
    }
    //delete &w;    

    return 0;
}
