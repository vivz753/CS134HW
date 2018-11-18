Octree Reference Document   - by  Kevin M. Smith - 4/20/2018
------------------------------------------------------------

I have put together this short document based on questions/discussions with students on our implementation of an octree which we are using for 3D selection and other applications in our class projects.  If you have any additional comments or input, please let me know.

1) Node and Memory Allocation

In my version, I use this this class for each node of the Octree:

class TreeNode {
public:
	Box box;
	vector<int> points;
	vector<TreeNode> children;
};

The points list are the subset of points in mesh that are contained in the box.  Note that the points are represented by integers.  The integer is used as an index into the 3D point array of the Mesh.   Each 3D point in the mesh is represented by an ofVec3f object which stores 3 floating point numbers.

On a 64-bit Windows Machine, when I execute the following code:

cout << "int: " << sizeof(int) << " " << "pointer: " << sizeof(ofVec3f *) << "float: " << sizeof(float) << endl;

int: 4 pointer: 4 float: 4

You see that an int, pointer and float are each 4 bytes long, but if we stored the actual 3D points rather than the indices to the points, that would require 12 bytes or 3X the storage.

I also could have stored the points using pointers such as:

vector<ofVec3f *> points;

and avoid having to lookup the actual 3D point in the mesh using the index (and a function call). I may try that eventually but for this first implementation my goal was to try and code it without any pointers.

Leaf Nodes and Point Search Trade-Offs
-------------------------------------
In the class example, I built an Octree that used 10 levels to represent our data (the mars terrain data set which I generated from photographic satallite date and is about 210K vertices).  At 10 levels, you will end up with one point in each leaf node.  You can choice to build a smaller tree and end up with more points in each leaf node. If you do this and you will require another search method to find the point you want out of the points in the leaf node.  For an example of a screen space search method, see my example ofApp::doPointSelection() in the example source code files.  It is extremely slow if you want to find a 3D point in the entire mesh, but it is relatively fast if you want to search for just say < 20 points.  There are advantages/disadvantages to each method. Mileage will vary.

Storage
-------
If you are using an Octree to find only leaf node points, it is not required to save the points list in all the parent nodes. You can save a lot of memory by not keeping the points.  You will need to at least have a temporary copy of the parent point list (either on the stack as a local variable or temporarily saved in the node) when dividing up the points amoung the child boxes, while testing to see if a parent point is in a child box, otherwise the algorithm will take too much time to build the tree.  In my implementation, I kept the parent data in the tree as I may want access to the hierachcy of points at run-time but I may later add an option to not store it as it does take up lots of memory (exponential with the data).


2) Helper Functions

Determine if a point is in a Box
---------------------------------

Although we went over how to determine if a point is in a rectangle (2D), you will need to add a method (either in your App class or in the Box class ) to determine if a 3D point is in a Box.  Here is an example of some methods I added to box.h:

    Vector3 min() { return parameters[0]; }
	Vector3 max() { return parameters[1]; }

	const bool inside(const Vector3 &p) {
		return ((p.x() >= parameters[0].x() && p.x() <= parameters[1].x()) &&
		     	(p.y() >= parameters[0].y() && p.y() <= parameters[1].y()) &&
			    (p.z() >= parameters[0].z() && p.z() <= parameters[1].z()));
	}

	Vector3 center() {
		return ((max() - min()) / 2 + min());
	}


The Box::inside method will determine if a point is inside the box.

Determine if point list is in Box
---------------------------------

If you want to make your Octree creation code really short  ( < 10 lines), I like to have a few small functions that elimate code blocks that contain busy loops in my code.  As an example:

// getMeshPointsInBox:  return an array of indices to points in mesh that are contained 
//                      inside the Box.  Return count of points found;
//
int Octree::getMeshPointsInBox(const ofMesh & mesh, const vector<int>& points,
	Box & box, vector<int> & pointsRtn)
{
	int count = 0;
	for (int i = 0; i < points.size(); i++) {
		ofVec3f v = mesh.getVertex(points[i]);
		if (box.inside(Vector3(v.x, v.y, v.z))) {
			count++;
			pointsRtn.push_back(points[i]);
		}
	}
	return count;
}


This method takes a list of points (described by input parameter "points") and determines if they are in the box ( "box").  If they are, they are added to the list,  "pointsRtn".  Notice that the input parameters are "const" but the modifiable output parameter is not. If there are points contained in the box, the count is returned.


The "Box" class and Vector3
---------------------------

For testing ray-box intersection we are using an efficent implementation which came from:  

Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
 *      "An Efficient and Robust Ray-Box Intersection Algorithm"
 *      Journal of graphics tools, 10(1):49-54, 2005

 Their website contains the paper (PDF) and public domain source code. I have also put a copy in Canvas.

 This Box class uses it's own vector class, Vector3, which is slightly differnt from the OpenFrameworks ofVec3f class. I may choose to convert it in the future to use ofVec3f but for now we have to live with fact that it is different. 

 So to convert from an ofVec3f to a Vector3:

 ofVec3f p = ofVec3f(1,2,3);
 Vector3 point = Vector3(p.x, p.y. pz);

 To convert from a Vector3 to an ofVec3f:

 Vector3 p = Vector3(1,2,3);
 ofVec3f point = ofVec3f(p.x(), p.y(). p.z());


Recursion Example
------------------

One way to test your octree build is to try and draw it recursively.  Here is my function to do that:

// draw Octree (recursively)
//
void Octree::draw(TreeNode & node, int numLevels, int level) {
	if (level >= numLevels) return;
	drawBox(node.box);
	level++;
	for (int i = 0; i < node.children.size(); i++) {
		draw(node.children[i], numLevels, level);
	}
}

This method basically draws "numLevels" of the octree.   The "level" parameter is a value parameter that increments the current level (in the recursion) and checks when we have reached the numLevels.

Note, it is very important to pass a refererence to your octree root node ( TreeNode & node ) and not the node itself (TreeNode node ). If you do that, lots of copying will be incurred when the value of node gets put on the call stack.













