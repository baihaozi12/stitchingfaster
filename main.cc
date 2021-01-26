#include <iostream>
#include <cmath>

#include "feature/extrema.hh"
#include "feature/matcher.hh"
#include "feature/orientation.hh"
#include "lib/mat.h"
#include "lib/config.hh"
#include "lib/geometry.hh"
#include "lib/imgproc.hh"
#include "lib/planedrawer.hh"
#include "lib/polygon.hh"
#include "lib/timer.hh"
#include "stitch/cylstitcher.hh"
#include "stitch/match_info.hh"
#include "stitch/stitcher.hh"
#include "stitch/transform_estimate.hh"
#include "stitch/warp.hh"
#include "common/common.hh"
#include <ctime>
#include <cassert>

using namespace std;
using namespace pano;
using namespace config;
int main() {
    std::cout << "Hello, World!" << std::endl;
    vector<string> imgs = {"/home/baihao/jpg/1111111/ppt/1.jpg", "/home/baihao/jpg/1111111/ppt/2.jpg"};
    Mat32f res;

    if (CYLINDER) {
//		CylinderStitcher p(move(imgs));
        Stitcher p(move(imgs));
        res = p.build();
    } else {
        Stitcher p(move(imgs));
        res = p.build();
    }



    return 0;
}
