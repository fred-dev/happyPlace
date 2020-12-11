#pragma once

#include "ofMain.h"

class SandPainter{
    
public:
    
    float p;
    ofColor inColour;
    float g;
    ofMesh sandMesh;
    
    void initSandPainter(ofColor someColor) {
        
        p = ofRandom(1.0);
        inColour = someColor;
        g = ofRandom(0.01,0.1);
        
        sandMesh.setMode(OF_PRIMITIVE_POINTS);
    }
    
    
    void render(float x, float y, float ox, float oy) {
        // draw painting sweeps
        float jumpBack = ofGetElapsedTimeMillis()/-10.0;
        //jumpBack = 0;
        sandMesh.addVertex(glm::vec3(ox+(x-ox)*sin(p),oy+(y-oy)*sin(p),jumpBack));
        sandMesh.addColor(ofColor(inColour.r, inColour.g, inColour.b, 28));
        
        g+=ofRandom(-0.050,0.050);
        float maxg = 0.22;
        if (g<-maxg) g=-maxg;
        if (g>maxg) g=maxg;
        
        float w = g/10.0;
        for (int i=0;i<11;i++) {
            float a = 0.1-i/110.0;
            sandMesh.addVertex(glm::vec3(ox+(x-ox)*sin(p+sin(i*w)) ,oy+(y-oy)* sin(p + sin(i*w)),jumpBack));
            sandMesh.addColor(ofColor(inColour.r, inColour.g, inColour.b, 256*a));
        }
    }
    
    
    
};
