#include "physicsmanager.h"

namespace ice {

	namespace physics {

		/*PhysicsManager::PlayerAABB(float l, float r, float b, float t) {
			left = l;
			right = r;
			bottom = b;
			top = t;
		} //Player AABB constructor

		PhysicsManager::PlayerAABB() {
			left = 0.0f;
			right = 0.0f;
			bottom = 0.0f;
			top = 0.0f;
		} //default constructor

		PhysicsManager::Intersect(const WallAABB& aabb, const Vec2& u, const Vec2& v) {
			return
				(left + u.x) <= (aabb.wRight + v.x) && //left side of player is left to right side of wall
				(right + u.x) >= (aabb.wLeft + v.x) && //right side of player is right to the left side of wall
				(top + u.y) >= (aabb.wBottom + v.y) && //top side of player is above the bottom side of the wall
				(bottom + u.y) <= (aabb.wTop + v.y); //bottom side of player is blow the top side of the wall
		}

		WallAABB::WallAABB(float l, float r, float b, float t)
		{
			wLeft = l;
			wRight = r;
			wBottom = b;
			wTop = t;
		}

		WallAABB::WallAABB() 
		{
			wLeft = 0.0f;
			wRight = 0.0f;
			wBottom = 0.0f;
			wTop = 0.0f;
		}
		*/
	}//namespace physics

}//namespace ice