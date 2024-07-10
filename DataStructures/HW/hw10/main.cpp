#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <utility>

#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

//Helper function: Find Neighbor
//Take in two int(x and y coor) of a black pixel
//If it is not neighbor of black pixel, return 0
//If it is a direct neighbor(N/S/E/W), return 1
//If it is a diagonal neighbor(NS/NW/SE/SW), return 2
int isNeighbor(int& x, int& y, Image<Color> &input) {
  //Make sure it doesn't go out of bound
  int result = -1;
  while (x>=0 && y >=0) {
    if (input.GetPixel(x-1,y).isBlack()==true) {
      result = 1;
    }
    else if (input.GetPixel(x+1,y).isBlack()==true) {
      result = 1;
    }
    else if (input.GetPixel(x,y-1).isBlack()==true) {
      result = 1;
    }
    else if (input.GetPixel(x,y+1).isBlack()==true) {
      result = 1;
    }
    else if (input.GetPixel(x+1,y+1).isBlack()==true) {
      result = 2;
    }
    else if (input.GetPixel(x-1,y-1).isBlack()==true) {
      result = 2;
    }
    else if (input.GetPixel(x+1,y-1).isBlack()==true) {
      result = 2;
    }
    else if (input.GetPixel(x-1,y+1).isBlack()==true) {
      result = 2;
    }
    else {
      result = 0;
    }
  }
  return result;
}
//See if the distance is a direct neighbor or a diagonal neighbor
int dCalc(int& x, int& y, int& x1, int& y1) {
  int result = 0;
  if (x == x1 && (y+1 == y1 || y-1 == y1)) {
    result = 1;
  }
  else if (y == y1 && (x+1 == x1 || x-1 == x1)) {
    result = 1;
  }
  else {
    result = 2;
  }
  return result;
}

//Checks if all image's distance is initialized and not left to infinity
//If there are still pixels at infinity, return false
bool imageScanner(Image<DistancePixel> &distance_image) {
  int w = distance_image.Width();
  int h = distance_image.Height();
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; w++) {
      DistancePixel& p = distance_image.GetPixel(x,y);
      if (p.getValue()==1000000) {
        return false;
      }
    }
  }
  return true;
}

//Find all 8 neighbors
std::vector<int> neighborFinder(int x, int y, int w, int h) {
  std::vector<int> nhbr;
  while(x-1 >=0 && y-1>=0 && y+1 < h && x+1 < w) {
    //Direct Neighbor
    nhbr.push_back(x-1);
    nhbr.push_back(y);
    nhbr.push_back(x+1);
    nhbr.push_back(y);
    nhbr.push_back(x);
    nhbr.push_back(y-1);
    nhbr.push_back(x);
    nhbr.push_back(y+1);
    //Diagonal Neighbor
    nhbr.push_back(x-1);
    nhbr.push_back(y-1);
    nhbr.push_back(x+1);
    nhbr.push_back(y-1);
    nhbr.push_back(x+1);
    nhbr.push_back(y+1);
    nhbr.push_back(x-1);
    nhbr.push_back(y+1);
  }
  return nhbr;
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
      	for (int j2 = 0; j2 < h; j2++) {
      	  const Color& c = input.GetPixel(i2,j2);      
      	  // skip all pixels that are not black
      	  if (!c.isBlack()) continue;
      	  // calculate the distance between the two pixels
      	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
      	  // store the closest distance to a black pixel
      	  if (closest < 0 || distance < closest) {
      	    closest = distance;
      	  }
      	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  //A vector that store all the index of the black pixels in the picture
  std::vector<std::pair<int, int> >BPIdx;
  //Loop through the input image.
  //Store all the location of each black pixels into 
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      const Color& color = input.GetPixel(x,y);
      if (color.isBlack()) {
        std::pair<int, int> coor;
        coor.first = x;
        coor.second = y;
        BPIdx.push_back(coor);
      }
    }
  }
  //Now go through another picture and calculate distance
  double closest = -1;
  double distance = 0;
  double answer = 0;
  for (int x1 = 0; x1 < w; x1++) {
    for (int y1 = 0; y1 < h; y1++) {
      const Color& pixel = input.GetPixel(x1,y1);
      for (unsigned long int n = 0; n < BPIdx.size(); n++) {
        if (!pixel.isBlack()) {
           distance = sqrt((x1-BPIdx[n].first)*(x1-BPIdx[n].first)+(y1-BPIdx[n].second)*(y1-BPIdx[n].second));
          if (closest < 0 || distance < closest) {
            closest = distance;
          }
        }
      }
      //Finding the max distance value
      answer = std::max(answer, closest);
      //Data is now stored into the distance image
      DistancePixel& p = distance_image.GetPixel(x1,y1);
      p.setValue(closest);
      closest = -1;
    }
  }
  return answer;
}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  std::vector<DistancePixel*> neighbors;
  for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      //Step 1 on the instruction: Initialize all black pixel to 0, others to infinity
      //I also combined with picking out the neighboring pixels
      const Color& pixel = input.GetPixel(x,y);
      DistancePixel& p = distance_image.GetPixel(x,y);
      if (pixel.isBlack()) {
        p.setValue(0);
      }
      else if (isNeighbor(x,y,input)!=0) {
        //Is a neighbor of a black pixel
        if (isNeighbor(x,y,input)==1) {
          //Put the neighbors in the priority queue
          //(x,y) is a direct neighbor
          p.setValue(1);
          neighbors.push_back(&p);
        }
        else {
          //Put the neighbors in the priority queue
          //(x,y) is diagonal to a black pixel
          p.setValue(1.4);
          neighbors.push_back(&p);
        }
      }
      else {
        p.setValue(1000000);    //Initialized to a very big value
      }
    }
  }
  while (imageScanner(distance_image)!=true) {
    for (int f = 0; f < w; f++) {
      for (int g = 0; g < h; g++) {
        DistancePixel& target = distance_image.GetPixel(f,g);
        std::vector<int> nhbr = neighborFinder(x, y, w, h);
        for (unsigned long int n = 0; n < nhbr.size(); n++) {
          std::vector<int> nhbr = neighborFinder(x, y, w, h);
          
        }
      }
    }
  }

  //The portion of code that is commentted is what I would have implimented, but currently it is faulty
  /*
  //Add the neighboring pixels into a priority queue
  //Keep track of distance
 double distance = 0;
 DistancePixel_PriorityQueue PixelPrior(neighbors);
  //This process should go until all pixels' distance is initialized correctly
 while (imageScanner(distance_image)!=true) {
    //Get x and y coor of the root of the tree
    int xcoor = PixelPrior.top()->getX();
    int ycoor = PixelPrior.top()->getY();
    //Find all its neighbor
    std::vector<int> nhbr = neighborFinder(xcoor, ycoor, w,h);
    //Goes through each instance 
    for (unsigned long int n = 0; n < nhbr.size()-1; n++) {
      DistancePixel& pix = distance_image.GetPixel(nhbr[n],nhbr[n+1]);
      if (pix.getValue()==1000000&&dCalc(nhbr[n],nhbr[n+1],xcoor,ycoor)==1) {
        //If it is direct neighbor to the pixel we are checking, add 1 to the distance to the distance of the checking pixel.
        DistancePixel& ref = distance_image.GetPixel(xcoor,ycoor);
        pix.setValue(1+ref.getValue());
        if (distance < 1+ref.getValue()) {
          distance = 1+ref.getValue();
        }
        PixelPrior.push(&pix);
      }
      else if (pix.getValue()==1000000&&dCalc(nhbr[n],nhbr[n+1],xcoor,ycoor)==2) {
        //If it is diagonal neighbor to the pixel we are checking, add 1.4 to the distance to the distance of the checking pixel.
        DistancePixel& ref = distance_image.GetPixel(xcoor,ycoor);
        pix.setValue(1.4+ref.getValue());
        if (distance < 1.4+ref.getValue()) {
          distance = 1.4+ref.getValue();
        }
        PixelPrior.push(&pix);
      }
    }
    //Everything about pixel's neighbor is checked, remove it so the next root pixel can be checked
    PixelPrior.pop();
  }
  //Every value is now initialized, return the maximum distance
  return distance;
  */
  return 0;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
