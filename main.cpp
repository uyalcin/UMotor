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

    Vector3 v(0.f, 0.f, 0.f);
    // Create graphics world
    World w;
    std::shared_ptr<Plane> plane(new Plane(Vector3(0.f, 0.f, 0.f), 1.0f));
    std::shared_ptr<Cube> cube(new Cube());
    std::shared_ptr<Cube> cube2(new Cube(0.5, Vector3(1.2, 0, 0)));
    //w.addEntity(plane);
    w.addEntity(cube);
    //w.addEntity(cube2);
    int lastX = 0;
    int lastY = 0;
    bool mousePressed = false;

    while (window.isOpen())
    {
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

		
	    if (mousePressed)
	    {

		float angleY = (lastX - event.mouseMove.x) / 10.0f;
		float angleZ = (lastY - event.mouseMove.y) / 10.0f;

		if(DEBUG)
		{
			std::cout << "angleY : " << angleY << std::endl;
			std::cout << "angleZ : " << angleZ << std::endl;
		}

		cube->rotate(angleZ, angleY);
		//cube2->rotate(angleZ, angleY);

		
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
