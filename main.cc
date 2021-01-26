#define _USE_MATH_DEFINES
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
#include <unistd.h>
#ifdef DISABLE_JPEG
#define IMGFILE(x) #x ".png"
#else
#define IMGFILE(x) #x ".jpg"
#endif
using namespace std;
using namespace pano;
using namespace config;

void init_config() {
#define CFG(x) \
	x = Config.get(#x)
    char path[255];
    getcwd(path,255);
    cout<<"the path is "<<path<< endl;
    // notice the config need to find the
    const char* config_file = "../config.cfg";
    ConfigParser Config(config_file);
    CFG(CYLINDER);
    CFG(TRANS);
    CFG(ESTIMATE_CAMERA);
    if (int(CYLINDER) + int(TRANS) + int(ESTIMATE_CAMERA) >= 2)
        error_exit("You set two many modes...\n");
    if (CYLINDER)
        print_debug("Run with cylinder mode.\n");
    else if (TRANS)
        print_debug("Run with translation mode.\n");
    else if (ESTIMATE_CAMERA)
        print_debug("Run with camera estimation mode.\n");
    else
        print_debug("Run with naive mode.\n");

    CFG(ORDERED_INPUT);
    if (!ORDERED_INPUT && !ESTIMATE_CAMERA)
        error_exit("Require ORDERED_INPUT under this mode!\n");

    CFG(CROP);
    CFG(STRAIGHTEN);
    CFG(FOCAL_LENGTH);
    CFG(MAX_OUTPUT_SIZE);
    CFG(LAZY_READ);	// TODO in cyl mode

    CFG(SIFT_WORKING_SIZE);
    CFG(NUM_OCTAVE);
    CFG(NUM_SCALE);
    CFG(SCALE_FACTOR);
    CFG(GAUSS_SIGMA);
    CFG(GAUSS_WINDOW_FACTOR);
    CFG(JUDGE_EXTREMA_DIFF_THRES);
    CFG(CONTRAST_THRES);
    CFG(PRE_COLOR_THRES);
    CFG(EDGE_RATIO);
    CFG(CALC_OFFSET_DEPTH);
    CFG(OFFSET_THRES);
    CFG(ORI_RADIUS);
    CFG(ORI_HIST_SMOOTH_COUNT);
    CFG(DESC_HIST_SCALE_FACTOR);
    CFG(DESC_INT_FACTOR);
    CFG(MATCH_REJECT_NEXT_RATIO);
    CFG(RANSAC_ITERATIONS);
    CFG(RANSAC_INLIER_THRES);
    CFG(INLIER_IN_MATCH_RATIO);
    CFG(INLIER_IN_POINTS_RATIO);
    CFG(SLOPE_PLAIN);
    CFG(LM_LAMBDA);
    CFG(MULTIPASS_BA);
    CFG(MULTIBAND);
#undef CFG
}

int main() {
    // our test program set config the order input to 1, we use sequence input
    // CYLINDER to 0
    // the config path is ../config because the debug and cmake folder is a subfolder in the project
    TotalTimerGlobalGuard _g;
    srand(time(NULL));
    init_config();

    std::cout << "Hello, World!" << std::endl;
    vector<std::string> imgs = {"/home/baihao/jpg/jpg/1.jpeg",
                                "/home/baihao/jpg/jpg/2.jpeg",
                                "/home/baihao/jpg/jpg/3.jpeg",
                                "/home/baihao/jpg/jpg/4.jpeg"};
    Mat32f res;
    if (CYLINDER) {

        CylinderStitcher p(move(imgs));
        res = p.build();
    } else {
//        cout<< "stitch"<<endl;
        Stitcher p(move(imgs));
        res = p.build();
    }


    CROP = false;
    if (CROP) {
        int oldw = res.width(), oldh = res.height();
        res = crop(res);
        print_debug("Crop from %dx%d to %dx%d\n", oldw, oldh, res.width(), res.height());
    }
    {
        GuardedTimer tm("Writing image");
        cout<<res.cols()<<endl;
        write_rgb("/home/baihao/stitchingfaster/out.jpg", res);
    }


    return 0;
}
