#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    takecolor("rainbow.png");
    ofSetBackgroundColor(0, 0, 0);     //framerate(30);
    
    ofSetFrameRate(50);

    resetAll();
    

}

//--------------------------------------------------------------
void ofApp::update(){
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofTranslate((ofGetWidth() - dimension)/2, (ofGetHeight()-dimension)/2,0);
    for (int c=0;c<num;c++) {
        friends[c].move();
    }
    for (int f=0;f<num;f++) {
        friends[f].expose();
        exposeConnections(f);
    }
    if (time%2==0){
        findHappyPlace();
    }
    time++;
    
    for (int c=0;c<num;c++) {

        for (int i =0; i<3; i++) {
            friends[c].sands[i].sandMesh.draw();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    

    if (key == 'r') {
        resetAll();
    }
   
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::resetAll() {
    // make some friend entities
    for (int x=0;x<num;x++) {
        float fx = dimension/2 + 0.4*dimension*cos(TWO_PI*x/num);
        float fy = dimension/2 + 0.4* dimension*sin(TWO_PI*x/num);
        friends[x].initFriend(fx,fy,x,somecolor());
        for(int i = 0; i < 3;  i++){
            friends[x].sands[i].sandMesh.clear();
        }
    }
    
    // make some random friend connections
    for (int k=0;k<num*2.2;k++) {
        
        int a = int(floor(ofRandom(num)));
        int b = int(floor(a+ int(ofRandom(22) ) % num));
        if (b>=num) {
            b=0;
        } else if (b<0) {
            b=0;
        }
        if (a!=b) {
            friends[a].connectTo(b);
            friends[b].connectTo(a);
        }
    }
    
}



ofColor ofApp::somecolor() {
    // pick some random good color
    return goodcolor[int(ofRandom(0, numpal))];
}

void ofApp::takecolor(string fn) {
    ofImage b;
    b.load(fn);
    
    
    for (int x=0;x<b.getWidth();x++){
        for (int y=0;y<b.getHeight();y++) {
            ofColor c = b.getColor(x, y);
            bool exists = false;
            
            for (int n=0;n<numpal;n++) {
                if (c==goodcolor[n]) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                // add color to pal
                if (numpal<maxpal) {
                    goodcolor[numpal] = c;
                    numpal++;
                }
            }
        }
    }
    // pump black and white in
    for (int x=0;x<22;x++) {
        goodcolor[numpal]=ofColor(0);
        numpal++;
        goodcolor[numpal]=ofColor(255);
        numpal++;
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

void ofApp::findHappyPlace(){
    // set destination to a happier place
    // (closer to friends, further from others)
    
    for (int jumpCounter =0; jumpCounter < num; jumpCounter++) {
        float ax = 0.0;
        float ay = 0.0;
        
        for (int n=0;n<num;n++) {
           
            if (n != jumpCounter) {
     
                
                float ddx = friends[n].x-friends[jumpCounter].x;
                float ddy = friends[n].y-friends[jumpCounter].y;
                
                float d = sqrt(ddx*ddx + ddy*ddy);
                float t = atan2(ddy,ddx);
                
                bool isFriend = false;
                for (int j=0;j<friends[jumpCounter].numcon;j++){
                    if (friends[jumpCounter].connections[j]==n){
                        isFriend=true;
                        
                    }
                    if (isFriend) {
                        // attract
                        if (d>friends[jumpCounter].lencon) {
                            ax += 4.0*cos(t);
                            ay += 4.0*sin(t);
                        }
                    } else {
                        // repulse
                        if (d<friends[jumpCounter].lencon) {
                            ax += (friends[jumpCounter].lencon-d)*cos(t+PI);
                            ay += (friends[jumpCounter].lencon-d)*sin(t+PI);
                        }
                    }
                }
                
                
            }
        }
        friends[jumpCounter].vx+=ax/42.22;
        friends[jumpCounter].vy+=ay/42.22;
    }
    // find mean average of all friends and non-friends
    
}

void ofApp::exposeConnections(int friendFinder) {
    // draw connection lines to all friends
    for (int n=0;n<friends[friendFinder].numcon;n++) {
        // find axis distances
        float ox = friends[friends[friendFinder].connections[n]].x;
        float oy = friends[friends[friendFinder].connections[n]].y;
        
        for (int s=0;s<friends[friendFinder].numsands;s++) {
            friends[friendFinder].sands[s].render(friends[friendFinder].x,friends[friendFinder].y,ox,oy);
        }
    }
}
