#pragma once

#include "ofMain.h"
#include "SandPainter.h"

class Friend{
    
public:
    
    float x, y;
    float dx, dy;
    float vx, vy;
    int iD;
    
    int numcon;
    int maxcon = 10;
    int lencon = 10+int(ofRandom(50.0));
    int connections[10];
    
    // sand painters
    int numsands = 3;
    SandPainter sands[3];
    ofMesh friendMesh;
    
        
    void initFriend(float X, float Y ,int Id, ofColor someColor) {
        // position
        dx = x = X;
        dy = y = Y;
        iD = Id;
        
        numcon = 0;
        friendMesh.clear();
        friendMesh.setMode(OF_PRIMITIVE_POINTS);
        
        for (int n=0;n<numsands;n++) {
            sands[n].initSandPainter(someColor);
        }
    }
    
    void expose() {
        
        for (int dx=-2;dx<3;dx++) {
            float a = 0.5-abs(dx)/5.0;
            
            friendMesh.addVertex(glm::vec3(x+dx,y, 0));
            friendMesh.addColor(ofColor(0,0,0,256*a));
            
            friendMesh.addVertex(glm::vec3(x+dx,y,0));
            friendMesh.addColor(ofColor(255,255,255,255));
        }
        
        for (int dy=-2;dy<3;dy++) {
            float a = 0.5-abs(dy)/5.0;
            
            friendMesh.addVertex(glm::vec3(x,y+dy, 0));
            friendMesh.addColor(ofColor(0,0,0,256*a));
            
            friendMesh.addVertex(glm::vec3(x-1,y+dy-1, 0));
            friendMesh.addColor(ofColor(0,0,0,256*a));
        }
    }
    
    
    void render( ofColor somecolor) {
        for(int xx=int(x-numcon);xx<int(x+numcon);xx++) {
            for(int yy=int(y-numcon);yy<int(y+numcon);yy++) {
                friendMesh.addVertex(glm::vec3(xx,yy,0));
                friendMesh.addColor(somecolor);
               
            }
        }
    }
    
    void renderConnections(Friend friends[128]) {
        for (int n=0;n<numcon;n++) {
            float ddx = friends[connections[n]].x-x;
            float ddy = friends[connections[n]].y-y;
            int m = int(1 + sqrt(ddx*ddx+ddy*ddy)/6);
            for (int k=0;k<m;k++) {
                float t = (1 + cos(k*PI/m))/2;
                int px = int(x + t*ddx);
                int py = int(y + t*ddy);
                friendMesh.addVertex(glm::vec3(px, py, 0));
                friendMesh.addColor(ofColor(51,51,51));
                
            }
        }
    }
    
    
    void move() {
        // add velocity to position
        x+=vx;
        y+=vy;
        
        //friction
        vx*=0.92;
        vy*=0.92;
        
    }
    
    void connectTo(int f) {
        // connect to friend f
        
        // is there room for more friends?
        if (numcon<maxcon) {
            // already connected to friend?
            if (!friendOf(f)) {
                connections[numcon] = f;
                numcon++;
            }
        }
    }
    
    bool friendOf(int x) {
        bool isFriend = false;
        for (int n=0;n<numcon;n++) {
            if (connections[n]==x) isFriend=true;
        }
        return isFriend;
    }
    
};
