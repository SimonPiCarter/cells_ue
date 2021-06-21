#pragma once

#include <array>
#include <iostream>

struct BoundingBox
{
	std::array<double, 2> position;
	std::array<double, 2> size;
};

/// @brief compute intersection of boxes
BoundingBox intersection(BoundingBox const& box1_p, BoundingBox const& box2_p);

/// @brief check if bounding box is empty (any size <= 0)
bool empty(BoundingBox const& box_p);

/// @brief check if other_p was oversizing ref on the left (pos)
bool oversizeLeft(BoundingBox const& ref_p, BoundingBox const& other_p);

/// @brief check if other_p was oversizing ref on the left (pos + size)
bool oversizeRight(BoundingBox const& ref_p, BoundingBox const& other_p);

/// @brief check if other_p was oversizing ref on the left (pos)
bool oversizeTop(BoundingBox const& ref_p, BoundingBox const& other_p);

/// @brief check if other_p was oversizing ref on the left (pos + size)
bool oversizeBottom(BoundingBox const& ref_p, BoundingBox const& other_p);

std::ostream& operator<<(std::ostream& os_p, BoundingBox const& box_p);

struct Hitbox
{
	Hitbox()
		: offset({ 0,0,0 }), size({ 1,1,1 })
	{}
	Hitbox(std::array<double, 3> offset_p, std::array<double, 3> size_p)
		: offset(offset_p), size(size_p)
	{}

	std::array<double, 3> offset;
	std::array<double, 3> size;
};

struct PositionalHitbox
{
	Hitbox hitbox;
	std::array<double, 3> pos;
};

/// @brief check if a ray (orig_p -dir_p-> ) collide with the positioned hitbox
/// @param orig_p the origin of the ray
/// @param dir_p the direction of the ray
/// @param hitbox_p the hitbox to be tested
/// @return return the distance (in norm of dir_p!), negative if no contact
double collide(std::array<double, 3> const& orig_p, std::array<double, 3> const& dir_p, PositionalHitbox const& hitbox_p);
