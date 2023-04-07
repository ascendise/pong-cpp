#include <memory>
#include <vector>

namespace pong {
    namespace world {

        class Component { 
            public:
                virtual ~Component();
        };

        class Entity {
            public: 
                Entity(long id, std::unique_ptr<Component> components[]);
                long getId();
                Component&[] getComponents();
        };

        class System {
            public:
                virtual ~System();
                virtual void run(Entity& entity);    
        };

        class World {
            public: 
                Entity& registerEntity(std::unique_ptr<Component> components[]);
                void removeEntity(long id);
                Entity&[] getEntities();
                void registerSystem(std::unique_ptr<System> system);
                void removeSystem(System& system);
                void run();
        };

    }
}