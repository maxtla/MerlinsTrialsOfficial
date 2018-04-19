Notes on CollisionBox Methods:	
*getClosestFace() - gives the face of the (about to be colliding) objects closest face from the boundingbox's center
*getFaceIndex(Faces) - return the index for the coresponding Face
*getFace(index) - returns the face placed at index

Notes on Collision Methods:
*updateCollision() - checks if two objects are intersecting each other and returns the direction from one objects center to the others (return value mainly unused)
*checkCollision() - checks if two objects are intersecting each other (Boolean)
updateTerrainCollision() - empty(unused)
checkPreTerrainCollision() - empty(unused)
checkPreCollision() - checks if two objects are going to, with their current velocity intersect on the next frame
wallCollisionRespone - a general response to when the player collides into walls
