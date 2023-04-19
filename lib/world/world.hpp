#include <memory>
#include <vector>

namespace pong {
    namespace world {

        class Component { 
        public:
            virtual ~Component() {}
        };

        class Entity {
        private:
            long id;
            std::vector<std::shared_ptr<Component>> components;
        public: 
            Entity(long id, std::vector<std::shared_ptr<Component>> components);
            long getId();
        };

        class World {
        private:
            long idCounter = 0;
            std::vector<std::shared_ptr<Entity>> entities;
        public: 
            std::shared_ptr<Entity> registerEntity(std::vector<std::shared_ptr<Component>> components);
        };

    }
}