#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "ofApp.h"

using std::cout;
using std::endl;
using std::min;
using std::vector;

using glm::determinant;
using glm::mat4;

int window_width;
int window_height;

struct Line
{
  int from_x;
  int from_y;
  int to_x;
  int to_y;
};

struct NormalizedLine
{
  double from_x;
  double from_y;
  double to_x;
  double to_y;
};

struct Point
{
  double x;
  double y;
};

vector<Line> lines;
vector<NormalizedLine> normalized_lines;

Line translateLine(NormalizedLine line)
{
  int center_x = window_width / 2;
  int center_y = window_height / 2;
  int square_size = min(window_width, window_height);
  int origin_x = center_x - 0.5*((double)square_size);
  int origin_y = center_y - 0.5*((double)square_size);

  int mapped_from_x = origin_x + line.from_x*((double)square_size);
  int mapped_from_y = origin_y + line.from_y*((double)square_size);
  int mapped_to_x = origin_x + line.to_x*((double)square_size);
  int mapped_to_y = origin_y + line.to_y*((double)square_size);

  return Line{mapped_from_x, mapped_from_y, mapped_to_x, mapped_to_y};
}

void addLine(double from_x, double from_y, double to_x, double to_y)
{
  NormalizedLine line{from_x, from_y, to_x, to_y};
  normalized_lines.push_back(line);
  lines.push_back(translateLine(line));
}

double get_random()
{
  return rand() / double(RAND_MAX);
}

//--------------------------------------------------------------
void ofApp::setup()
{
  ofBackground(0, 0, 0);

  vector<Point> points;
  
  for(int i = 0; i < 4; i++)
  {
    points.push_back(Point{get_random(), get_random()});
  }

  for(Point point : points)
  {
    addLine(point.x - .005, point.y - .005, point.x + .005, point.y + .005);
    addLine(point.x - .005, point.y + .005, point.x + .005, point.y - .005);
  }

  for(Point point1 : points)
  {
    for(Point point2 : points)
    {
      if(point1.x != point2.x && point1.y != point2.y)
      {
        Point midpoint{(point1.x + point2.x)/2, (point1.y + point2.y)/2};
        double slope = (point1.x - point2.x) / (point2.y - point1.y);
        addLine(midpoint.x - 1, midpoint.y - slope, midpoint.x + 1, midpoint.y + slope);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
  for(Line line : lines)
  {
    ofDrawLine(line.from_x, line.from_y, line.to_x, line.to_y);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
  window_width = w;
  window_height = h;
  for(int i = 0; i < normalized_lines.size(); i++)
  {
    lines[i] = translateLine(normalized_lines[i]);
  }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
