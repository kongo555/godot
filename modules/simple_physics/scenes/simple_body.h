#ifndef SIMPLE_BODY_H
#define SIMPLE_BODY_H

#include "simple_area.h"

class SimpleBody : public SimpleArea {
    GDCLASS(SimpleBody, SimpleArea);

public:
    Vector3 remainder;
    Vector3 collision_normal;
    bool on_wall;
	bool on_floor;
    bool on_ceiling;

protected:
	static void _bind_methods();

	void add_to_world(SimpleWorld *p_world) const;
	void remove_from_world(SimpleWorld *p_world) const;

public:
    void move_and_slide(real_t p_delta, Vector3 p_linear_velocity);
    
    Vector3 get_remainder() const;
    void set_remainder(Vector3 p_remainder);
    Vector3 get_collision_normal() const;
    void set_collision_normal(Vector3 p_collision_normal);

    bool get_on_wall() const;
	void set_on_wall(bool p_on_wall);
    bool get_on_floor() const;
	void set_on_floor(bool p_on_floor);
    bool get_on_ceiling() const;
	void set_on_ceiling(bool on_ceiling);

	SimpleBody();
	~SimpleBody();
};

#endif
