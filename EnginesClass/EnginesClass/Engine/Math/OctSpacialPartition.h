#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#define CHILDREN_NUM 8

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

enum class OctChildren {
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,

	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR
};

class OctNode {
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();

	void OnDestroy();
	void Octify(int depth_); // create the children (minus 1)
	void AddCollisionObject(GameObject* obj_);

	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);

	int GetObjectCount() const;
	int GetChildCount() const;

	bool IsLeaf() const; // node with no children

	BoundingBox* GetBoundingBox() const;
	
private:
	friend class OctSpacialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUM];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;
};

class OctSpacialPartition
{
public:
	OctSpacialPartition(float worldSize_);
	~OctSpacialPartition();

	void OnDestroy();
	void AddObject(GameObject* obj_);

	GameObject* GetCollision(Ray ray_);

private:
	OctNode* root;
	std::vector<OctNode*>rayIntersectionList;

	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};

#endif