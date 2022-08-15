/* register_types.cpp */

#include <core/engine.h>

#include "register_types.h"
#include "core/class_db.h"

#include "./scenes/simple_area.h"
#include "./scenes/simple_body.h"
#include "./scenes/simple_world.h"


static SimpleWorld *simple_world;

void register_simple_physics_types() {
    ClassDB::register_class<SimpleArea>();
    ClassDB::register_class<SimpleBody>();
    
    simple_world = memnew(SimpleWorld);
	Engine::get_singleton()->add_singleton(Engine::Singleton("SimpleWorld", simple_world));
}

void unregister_simple_physics_types() {
   memdelete(simple_world);
}