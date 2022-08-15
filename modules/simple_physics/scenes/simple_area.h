#ifndef SIMPLE_AREA_H
#define SIMPLE_AREA_H

#include <scene/3d/spatial.h>

class SimpleWorld;

class SimpleArea : public Spatial {
    GDCLASS(SimpleArea, Spatial);

public:
	uint32_t collision_layer;
	uint32_t collision_mask;

    Vector3 extents;
    Vector3 offset;

    bool disabled;

protected:
	static void _bind_methods();
	void _notification(int p_what);

	virtual void add_to_world(SimpleWorld *p_world) const;
	virtual void remove_from_world(SimpleWorld *p_world) const;

public:    
    Array get_overlapping_areas() const;
	Array get_overlapping_bodies() const;

    Vector3 get_extents() const;
	void set_extents(Vector3 p_extents);

    Vector3 get_offset() const;
	void set_offset(Vector3 p_offset);

    bool get_disabled() const;
	void set_disabled(bool disabled);

	uint32_t get_collision_layer() const;
	void set_collision_layer(uint32_t p_collision_layer);

	uint32_t get_collision_mask() const;
	void set_collision_mask(uint32_t p_collision_mask);

	void set_collision_layer_bit(int p_bit, bool p_value);
	bool get_collision_layer_bit(int p_bit) const;

	void set_collision_mask_bit(int p_bit, bool p_value);
	bool get_collision_mask_bit(int p_bit) const;

	SimpleArea();
	~SimpleArea();
};

#endif
