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
#include <Eigen/Dense>
//#include <opencv2/core.hpp>
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


struct StitchResult{
    std::string img_path;
    Eigen::Matrix3f homo_inv;
    double proj_range_min_x;
    double proj_range_min_y;
    double resolution_x;
    double resolution_y;
    double shape_center_x;
    double shape_center_y;
};

vector<StitchResult> littile_pussy_stitching(vector<std::string> img_names, std::string output){
    TotalTimerGlobalGuard _g;
    srand(time(NULL));
    init_config();

    vector<StitchResult> stitch_result(img_names.size());
    Mat32f res;
    Stitcher p(move(img_names));
    res = p.build();


    for(int i = 0;i<p.homo_inv_pointspace2image.size();i++) {
        Eigen::Matrix3f homo_inv;
        stitch_result[i].homo_inv
                << p.homo_inv_pointspace2image[i][0], p.homo_inv_pointspace2image[i][1], p.homo_inv_pointspace2image[i][2],
                p.homo_inv_pointspace2image[i][3], p.homo_inv_pointspace2image[i][4], p.homo_inv_pointspace2image[i][5],
                p.homo_inv_pointspace2image[i][6], p.homo_inv_pointspace2image[i][7], p.homo_inv_pointspace2image[i][8];
        stitch_result[i].img_path = img_names.at(i);

        stitch_result[i].proj_range_min_x = p.proj_range_min_x;
        stitch_result[i].proj_range_min_y = p.proj_range_min_y;
        stitch_result[i].resolution_x = p.resolution_x;
        stitch_result[i].resolution_y = p.resolution_y;
        stitch_result[i].shape_center_x = p.shape_center_x;
        stitch_result[i].shape_center_y = p.shape_center_y;
//        cout<< "proj_range_min_x  is " << p.proj_range_min_x <<endl;
//        cout<< "proj_range_min_y  is " << p.proj_range_min_y <<endl;
//        cout<< "resolution_x  is " << p.resolution_x <<endl;
//        cout<< "resolution_y  is " << p.resolution_y <<endl;
//        cout<< "shape_center_x  is " << p.shape_center_x <<endl;
//        cout<< "shape_center_y  is " << p.shape_center_y <<endl;
    }
    write_rgb(output, res);
    return stitch_result;
}



int main() {
    vector<std::string> imgs = {"/home/baihao/jpg/jpg/1.jpeg",
                                "/home/baihao/jpg/jpg/2.jpeg",
                                "/home/baihao/jpg/jpg/3.jpeg",
                                "/home/baihao/jpg/jpg/4.jpeg",
                                "/home/baihao/jpg/jpg/5.jpeg",
                                "/home/baihao/jpg/jpg/6.jpeg",
                                "/home/baihao/jpg/jpg/7.jpeg",
                                "/home/baihao/jpg/jpg/8.jpeg"};
    std::string output = "/home/baihao/stitchingfaster/out.jpg";
    std::vector<StitchResult> stitch_result = littile_pussy_stitching(imgs, output);

}

int main_() {
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
//        cout<<<<endl;

        vector<Eigen::Matrix3f> homo_inv_list;
        vector<Eigen::Matrix3f> homo_list;
        for(int i = 0;i<p.homo_inv_pointspace2image.size();i++){
            Eigen::Matrix3f homo_inv;
            homo_inv << p.homo_inv_pointspace2image[i][0],p.homo_inv_pointspace2image[i][1],p.homo_inv_pointspace2image[i][2],
                    p.homo_inv_pointspace2image[i][3],p.homo_inv_pointspace2image[i][4],p.homo_inv_pointspace2image[i][5],
                    p.homo_inv_pointspace2image[i][6],p.homo_inv_pointspace2image[i][7],p.homo_inv_pointspace2image[i][8];
            cout<< "homo inv is " << homo_inv <<endl;
            homo_inv_list.push_back(homo_inv);
//            delete homo_inv;
            Eigen::Matrix3f homo;
            homo << p.homo_image2pointspace[i][0],p.homo_image2pointspace[i][1],p.homo_image2pointspace[i][2],
                    p.homo_image2pointspace[i][3],p.homo_image2pointspace[i][4],p.homo_image2pointspace[i][5],
                    p.homo_image2pointspace[i][6],p.homo_image2pointspace[i][7],p.homo_image2pointspace[i][8];
            cout<< "homo  is " << homo <<endl;
            homo_list.push_back(homo);

            cout<< "proj_range_min_x  is " << p.proj_range_min_x <<endl;
            cout<< "proj_range_min_y  is " << p.proj_range_min_y <<endl;
            cout<< "resolution_x  is " << p.resolution_x <<endl;
            cout<< "resolution_y  is " << p.resolution_y <<endl;
            cout<< "shape_center_x  is " << p.shape_center_x <<endl;
            cout<< "shape_center_y  is " << p.shape_center_y <<endl;

        }


//        cout<< "homo  is " << p.homo_image2pointspace[0][0]<<endl;
    }


    CROP = false;
    if (CROP) {
        int oldw = res.width(), oldh = res.height();
        res = crop(res);
        print_debug("Crop from %dx%d to %dx%d\n", oldw, oldh, res.width(), res.height());
    }
    {
        GuardedTimer tm("Writing image");

        write_rgb("/home/baihao/stitchingfaster/out.jpg", res);
    }


    return 0;
}
