#pragma once

#include "ofMain.h"
#include "Friend.h"
#include "SandPainter.h"


#define num 128
#define maxpal 512
#define dimension 1080

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    
    void takecolor(string fn);

    Friend friends[num];


    int time = 0;
    int numpal = 0;
    ofColor goodcolor[maxpal];
		
    ofColor somecolor();

    void resetAll();
    
    void findHappyPlace();
    void exposeConnections(int friendFinder);
    
    

    
};
