//  Kevin M. Smith - Basic Octree Class - CS134/235 4/18/18
//


#include "Octree.h"
#include "vector3.h"
#include "box.h"

// draw Octree (recursively)
//
void Octree::draw(TreeNode & node, int numLevels, int level) {
	
    if (level > numLevels) return;
	level++;
    drawBox(node.box, level);
    
	for (int i = 0; i < node.children.size(); i++) {
		draw(node.children[i], numLevels, level);
	}
}

// draw only leaf Nodes
//
void Octree::drawLeafNodes(TreeNode & node) {
    if (node.children.size()>0){
        for (int i=0; i<node.children.size(); i++){
            drawLeafNodes(node.children[i]);
        }
    }
    else{
        if(node.points.size()>0){
            drawBox(node.box, 0);
        }
    }
}


//draw a box from a "Box" class  
//
void Octree::drawBox(const Box &box, int level) {
	Vector3 min = box.parameters[0];
	Vector3 max = box.parameters[1];
	Vector3 size = max - min;
	Vector3 center = size / 2 + min;
	ofVec3f p = ofVec3f(center.x(), center.y(), center.z());
	float w = size.x();
	float h = size.y();
	float d = size.z();
    if(level%4==0){
        ofSetColor(255, 0, 0);
    }
    else if(level%6==1){
        ofSetColor(255, 255, 0);
    }
    else if(level%6==2){
        ofSetColor(255, 0, 255);
    }
    else if(level%6==3){
        ofSetColor(0, 255, 255);
    }
    else if(level%6==4){
        ofSetColor(0, 255, 0);
    }
    else if(level%6==5){
        ofSetColor(0, 0, 255);
    }
	ofDrawBox(p, w, h, d);
}

// return a Mesh Bounding Box for the entire Mesh
//
Box Octree::meshBounds(const ofMesh & mesh) {
	int n = mesh.getNumVertices();
	ofVec3f v = mesh.getVertex(0);
	ofVec3f max = v;
	ofVec3f min = v;
	for (int i = 1; i < n; i++) {
		ofVec3f v = mesh.getVertex(i);

		if (v.x > max.x) max.x = v.x;
		else if (v.x < min.x) min.x = v.x;

		if (v.y > max.y) max.y = v.y;
		else if (v.y < min.y) min.y = v.y;

		if (v.z > max.z) max.z = v.z;
		else if (v.z < min.z) min.z = v.z;
	}
	return Box(Vector3(min.x, min.y, min.z), Vector3(max.x, max.y, max.z));
}

// getMeshPointsInBox:  return an array of indices to points in mesh that are contained 
//                      inside the Box.  Return count of points found;
//
int Octree::getMeshPointsInBox(
                               const ofMesh & mesh,
                               const vector<int>& points,
                               Box & box,
                               vector<int> & pointsRtn
                               )
{
    int count = 0;
    for (int i = 0; i < points.size(); i++) {
        ofVec3f v = mesh.getVertex(points[i]);
        if (box.inside(Vector3(v.x, v.y, v.z))) {
            count++;
            pointsRtn.push_back(points[i]);
            //cout << "points[" << i << "] : " << points[i];
        }
    }
    return count;
}



//  Subdivide a Box into eight(8) equal size boxes, return them in boxList;
//
void Octree::subDivideBox8(const Box &box, vector<Box> & boxList) {
	Vector3 min = box.parameters[0];
	Vector3 max = box.parameters[1];
	Vector3 size = max - min;
	Vector3 center = size / 2 + min;
	float xdist = (max.x() - min.x()) / 2;
	float ydist = (max.y() - min.y()) / 2;
	float zdist = (max.z() - min.z()) / 2;
	Vector3 h = Vector3(0, ydist, 0);

	//  generate ground floor
	//
	Box b[8];
	b[0] = Box(min, center);
	b[1] = Box(b[0].min() + Vector3(xdist, 0, 0), b[0].max() + Vector3(xdist, 0, 0));
	b[2] = Box(b[1].min() + Vector3(0, 0, zdist), b[1].max() + Vector3(0, 0, zdist));
	b[3] = Box(b[2].min() + Vector3(-xdist, 0, 0), b[2].max() + Vector3(-xdist, 0, 0));

	boxList.clear();
	for (int i = 0; i < 4; i++)
		boxList.push_back(b[i]);

	// generate second story
	//
	for (int i = 4; i < 8; i++) {
		b[i] = Box(b[i - 4].min() + h, b[i - 4].max() + h);
		boxList.push_back(b[i]);
	}
}

vector<int> Octree::convertVectorIndicesToInts (vector<ofIndexType> indexVector){
    vector<int> intVector(indexVector.size());
    
    for(int i=0; i < indexVector.size(); i++){
        intVector[i] = indexVector[i];
    }
//    for(ofIndexType i : indexVector){
//        intVector.push_back(ofToInt(indexVector[i]));
//    }
    return intVector;
}

void Octree::create(const ofMesh & geo, int numLevels) {
    float startTime = ofGetElapsedTimeMillis();
	
    root = TreeNode();    
    //intialize root.box
    Box boundingBox = meshBounds(geo);
    root.box = boundingBox;
    
    vector<ofIndexType> marsIndices = geo.getIndices();
    
    //intialize root.points
    vector <int> pointsInsideMesh(marsIndices.size());
    vector <int> pointsInsideBox;
    //convert ofIndexType vector to int vector
    pointsInsideMesh = convertVectorIndicesToInts(marsIndices);
    int totalPointsInBox = getMeshPointsInBox(geo, pointsInsideMesh, boundingBox, pointsInsideBox);
    
    //debug test to check if total points add up to ~210k
    //    for(int i: pointsInsideBox){
    //        cout << "points inside 1st bounding box" << i << endl; ;
    //    }
    root.points = pointsInsideBox;
    
    //call recursive function for numLevels
    subdivide(geo, root, numLevels, 0);
    
    float endTime = ofGetElapsedTimeMillis();
    cout << endTime - startTime << " milliseconds to build octree." << endl << endl;

}

void Octree::subdivide(const ofMesh & mesh, TreeNode & node, int numLevels, int level) {
    level++;
    
    
    if (level > numLevels){
        return;
    }
    
    //divide the node.box by 8 and put each box into a boxList
    vector<Box> boxList;
    subDivideBox8(node.box, boxList);
    
    //create 8 nodes and attach it to that root.children
    for (int i = 0; i < 8; i++){
        
        //create child node & initialize values
        TreeNode child = TreeNode();
        
        //attach subdivided8 box to child.box
        child.box = boxList[i];
        
        //cout << "intializing child " << i << endl;
        
        //check if points in node.points are inside child.box
        getMeshPointsInBox(mesh, node.points, child.box, child.points);
        
        if(child.points.size()>0){
            //cout << child.points.size() << " points added to child " << i << " at level " << level << endl;
        }
        
        subdivide(mesh, child, numLevels, level);
        
        //add child to node.children if it has points w/in mesh
        if(child.points.size()>0){
            node.children.push_back(child);
        }
    }
}

bool Octree::intersect(const Ray &ray, const TreeNode & node, TreeNode & nodeRtn) {
    
    //if box is intersected, recurse on method with node.children[i] as node
    if(node.box.intersect(ray, -50000, 50000)){
        if(node.children.size()>0){
            for(int i = 0; i<node.children.size(); i++){
                //if leaf node is found, break out of loop and return true
                if (intersect(ray, node.children[i], nodeRtn)){
                    return true;
                    break;
                };
            }
        }
        //base case if leaf node is found
        else{
            nodeRtn = node;
            selectedNode = nodeRtn;
            //cout << "INTERSECTED: leaf node @ point w/ index " << selectedNode.points[0] << endl;
            return true;
        }
    }
    //base case if node.box isn't intersected by ray
    else{
        return false;
    }
    return false;

}

//bool Octree::intersect(const Vector3 & v, const TreeNode & node, TreeNode & nodeRtn) {
//
//    //if box is intersected, recurse on method with node.children[i] as node
//    if(node.box.inside(v)){
//        if(node.children.size()>0){
//            for(int i = 0; i<node.children.size(); i++){
//                //if leaf node is found, break out of loop and return true
//                if (intersect(v, node.children[i], nodeRtn)){
//                    return true;
//                    break;
//                };
//            }
//        }
//        //base case if leaf node is found
//        else{
//            nodeRtn = node;
//            selectedNode = nodeRtn;
//            //cout << "INTERSECTED: leaf node @ point w/ index " << selectedNode.points[0] << endl;
//            return true;
//        }
//    }
//    //base case if node.box isn't intersected by point
//    else{
//        return false;
//    }
//    return false;
//
//}

// Checks if the particle is within delta distance to any of the vertices in the
// octree
bool Octree::collides(Particle & p, float delta, TreeNode & nodeRtn,int & index){
    return collides(p, delta, root, nodeRtn, index);
}

bool Octree::collides(Particle & p, const float delta, TreeNode & node, TreeNode & nodeRtn, int& index){
    // At a leaf node and we are in that node
    // check if the average distance to the points is less than delta
    // Base case
    if (node.children.size() == 0){
        float min = 10000000;
        for (int i = 0; i < node.points.size(); i++){
            ofVec3f vert = mesh.getVertex(node.points[i]);
            vert = ofVec3f(-vert.x, -vert.y, vert.z);
            float d = vert.distance(ofVec3f(-p.position.x,-p.position.y,p.position.z));
            if (d < min){
                min = d;
                nodeRtn = node;
                index = i;
            }
        }
        if(min < delta){
            cout << ofGetElapsedTimeMillis()<< " Octree:: Collided!" << endl;
            return true;
        }
        return false;
    }
    // Regular Case
    // Check if the particles collides with any of the children
    bool collided = false;
    for (TreeNode& child : node.children){
        if (child.box.inside(Vector3(-p.position.x,-p.position.y,p.position.z))){
            if (collides(p,delta,child,nodeRtn,index)){
                collided = true;
                break;
            }
        }
    }
    return collided;
}



