#include <SFML/Graphics.hpp>
#include "header.h"
#include "World.h"
#include "Plane.h"
#include "Vector3.h"
#include "Cube.h"
#include <memory>
#include <string>
#include "Object.h"
#include <ctime>

#define DEBUG false

enum MODE { CREATION, SELECTION };
enum FIGURE { CUBE, CYLINDRE, SPHERE, SWORD};

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "UMotor");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    sf::Clock deltaClock;
    enum MODE mode = SELECTION;
    enum FIGURE figure = CUBE;
    bool isWireFrame = false;
    bool isPerspective = false;

    Vector3 v(0.f, 0.f, 0.f);
    // Create graphics world
    World w;
    // Create camera in position (0, 0, 0) and null rotation
    std::shared_ptr<Entity> cam;
    w.setCamera(cam);
    //std::shared_ptr<Plane> plane(new Plane(Vector3(0.f, 0.f, 0.f), 3.0f));

    std::shared_ptr<Cube> skybox(new Cube(0.2,Vector3(-0.7, 0, -2.0)));
    // Create skybox
    sf::Texture tex;
    tex.setSmooth(true);
    const std::string skyNames[6] = {"Skybox/bluecloud_lf.jpg", 
				     "Skybox/bluecloud_bk.jpg", 
				     "Skybox/bluecloud_rt.jpg",
				     "Skybox/bluecloud_ft.jpg",
				     "Skybox/bluecloud_dn.jpg",
				     "Skybox/bluecloud_up.jpg"};
    for(int i = 0; i < 6; i++)
    {
	    tex.loadFromFile(skyNames[i]);
	    Plane*p = dynamic_cast<Plane*>(skybox->primitives[i]);
	    p->setTexture(tex);
    }

    std::shared_ptr<Cube> cube(new Cube(0.2, Vector3(-0.7, 0, -2.0)));
    std::shared_ptr<Object> sword(new Object("sword.obj", Vector3(0.3, -0.7, -3.0), 0.5f));
    std::shared_ptr<Object> sphere(new Object("sphere.obj", Vector3(0.7, 0, -3.0), 0.2f));
    std::shared_ptr<Object> cylindre(new Object("cylindre.obj", Vector3(0, 0.7, -3.0), 0.2f));

    /*std::shared_ptr<Cube> cube2(new Cube(0.2, Vector3(-0.5, 0, -2.0)));
    std::shared_ptr<Cube> cube3(new Cube(0.2, Vector3(0.5, 0, -3.0)));
    std::shared_ptr<Cube> cube4(new Cube(0.2, Vector3(0, 0.5, -3.0)));*/
    /*std::shared_ptr<Cube> cube2(new Cube(0.2, Vector3(0, 0, 2.0)));
    std::shared_ptr<Cube> cube3(new Cube(0.2, Vector3(2.0, 0, 0.0)));
    std::shared_ptr<Cube> cube4(new Cube(0.2, Vector3(-2.0, 0, 0.0)));*/
    w.addEntity(skybox);
    w.addEntity(sword);
    w.addEntity(sphere);
    w.addEntity(cylindre);
    //w.addEntity(suzanne);
    //w.addEntity(skybox);
    //w.addEntity(cube2);
    //w.addEntity(cube3);
    //w.addEntity(cube4);
    //w.addEntity(plane);
    int lastX = 0;
    int lastY = 0;
    bool mousePressed = false;
    
    std::shared_ptr<Entity> selectedEntity = nullptr;

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
		if (event.mouseButton.button == sf::Mouse::Right)
	    		mousePressed = true;
		if (event.mouseButton.button == sf::Mouse::Left)
	    	{
			lastX = event.mouseMove.x;
			lastY = event.mouseMove.y;

			// Check if an object is selected
			for(int i = 0; i < w.getSize(); i++)
			{
				std::shared_ptr<Entity> e = w.getEntity(i);
				if(e->isSelected(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					selectedEntity = e;
			}

			// Create object if creation mode
			if(mode == CREATION)
			{
				// Screen to world positions
				float mx = (event.mouseButton.x - SCREEN_X/2.0f) / (SCREEN_Y / 2.0f);
				float my = ((2.0f * event.mouseButton.y) / SCREEN_Y) - 1.0f;
				/*srand(time(NULL));
				float mx = rand() / RAND_MAX - 0.5f;
				float my = rand() / RAND_MAX - 0.5f;*/
				if(figure == CUBE)
				{
					std::shared_ptr<Cube> cube(new Cube(0.2, Vector3(mx, my, -3.0)));
					w.addEntity(cube);
				}
				if(figure == CYLINDRE)
				{
					std::shared_ptr<Object> cylindre(new Object("cylindre.obj", Vector3(mx, my, -3.0), 0.2f));
					w.addEntity(cylindre);
				}
				if(figure == SPHERE)
				{
					std::shared_ptr<Object> sphere(new Object("sphere.obj", Vector3(mx, my, -3.0), 0.2f));
					w.addEntity(sphere);
				}
				if(figure == SWORD)
				{
					std::shared_ptr<Object> sword(new Object("sword.obj", Vector3(mx, my, -3.0), 0.5f));
					w.addEntity(sword);
				}
			}
		}
	    }
	    if (event.type == sf::Event::MouseButtonReleased)
	    {
		if (event.mouseButton.button == sf::Mouse::Right)
	    		mousePressed = false;
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }
	    if (event.type == sf::Event::MouseMoved)
	    {
		cube->isSelected(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            }

	    Vector3 tr(0, 0, 0);
	    float speed = 0.1f * 10.0f;
	    float angleX = 1.0f;
	    float angleY = 1.0f;

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
		tr = tr + Vector3(0, 0, -speed * deltaTime);
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	    {
		tr = tr + Vector3(0, 0, speed * deltaTime);
	    }
	
	    if(tr != Vector3(0, 0, 0))
	    {
		//cube->translate(tr);
		if(selectedEntity != nullptr)
			selectedEntity->translate(tr);
		//sword->translate(tr);
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	    {
		//cube->scale(Vector3(1.1f, 1.1f, 1.1f));
		//sword->scale(Vector3(1.1f, 1.1f, 1.1f));
		if(selectedEntity != nullptr)
			selectedEntity->scale(Vector3(1.1f, 1.1f, 1.1f));
	    }
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	    {
		//cube->scale(Vector3(0.9f, 0.9f, 0.9f));
		//sword->scale(Vector3(0.9f, 0.9f, 0.9f));
		if(selectedEntity != nullptr)
			selectedEntity->scale(Vector3(0.9f, 0.9f, 0.9f));
	    }
		
	    if (mousePressed)
	    {

		float _angleY = (lastX - event.mouseMove.x) / 10.0f;
		float _angleX = (lastY - event.mouseMove.y) / 10.0f;

		if(DEBUG)
		{
			std::cout << "angleX : " << angleX << std::endl;
			std::cout << "angleY : " << angleY << std::endl;
		}

		w.rotateCamera(_angleX, -_angleY);
		/*skybox->rotate(_angleX, -_angleY);
		sword->rotate(_angleX,- _angleY);
		//cube->rotate(_angleX,- _angleY);
		cylindre->rotate(_angleX,- _angleY);
		sphere->rotate(_angleX,- _angleY);
		cube2->rotate(_angleX, -_angleY);
		cube3->rotate(_angleX, -_angleY);
		cube4->rotate(_angleX, -_angleY);
		skybox->rotate(_angleX, -_angleY);*/
		
		lastX = event.mouseMove.x;
		lastY = event.mouseMove.y;
	    }

		// Keyboard input
		if (event.type == sf::Event::KeyPressed)
		{
		    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		    {
			mode = CREATION;
		    }
		    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		    {
			mode = SELECTION;
		    }
		    if(mode == CREATION)
		    {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			{
				figure = CUBE;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			{
				figure = CYLINDRE;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
			{
				figure = SPHERE;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			{
				figure = SWORD;
			}
		    }
		    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		    {
			isWireFrame = !isWireFrame;
		    }
		    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		    {
			isPerspective = !isPerspective;
		    }
		}
	
	    
    	}
	w.setWireFrame(isWireFrame);
	w.setPerspective(isPerspective);
	//cube->rotate(0, 0);
        window.clear(sf::Color::Black);
        //window.draw(shape);
	w.draw(window);
        window.display();
	
    }
    //delete &w;    

    return 0;
}
