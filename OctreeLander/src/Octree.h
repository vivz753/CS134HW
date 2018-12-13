#pragma once
#include "ofMain.h"
#include "box.h"
#include "ray.h"
#include "vector3.h"
#include "Particle.h"


class TreeNode {
public:
	Box box;
    //list of vertices
	vector<int> points;
	vector<TreeNode> children;
};

class Octree {
public:
    
	void create(const ofMesh & mesh, int numLevels);
	void subdivide(const ofMesh & mesh, TreeNode & node, int numLevels, int level);
	bool intersect(const Ray &, const TreeNode & node, TreeNode & nodeRtn);
    bool intersect(const Vector3 &v, const TreeNode & node, TreeNode & nodeRtn);
	void draw(TreeNode & node, int numLevels, int level);
	void draw(int numLevels, int level) {
		draw(root, numLevels, level);
	}
	void drawLeafNodes(TreeNode & node);
	static void drawBox(const Box &box, int level);
	static Box meshBounds(const ofMesh &);
	int getMeshPointsInBox(const ofMesh &mesh, const vector<int> & points, Box & box, vector<int> & pointsRtn);
	void subDivideBox8(const Box &b, vector<Box> & boxList);
    
    vector<int> convertVectorIndicesToInts(vector<ofIndexType>);

	ofMesh mesh;
	TreeNode root;
    TreeNode selectedNode;
    
    
    bool collides(Particle & p, float delta, TreeNode & nodeRtn, int & index);
    bool collides(Particle & p, const float delta, TreeNode & node, TreeNode & nodeRtn, int & index);
};
